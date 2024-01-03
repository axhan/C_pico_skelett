//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "input.h"


//@@@ Private type definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

typedef struct {
	uint16_t	held_ticks;
	uint64_t	shift_reg;
	bool		is_held;
} ButtonState_t;


//@@@ Public global variables (that have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const uint8_t		in_gpios[] = cfBUTT_GPIOS;


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ButtonState_t		b_states[cfNUM_BUTT];
uint64_t			elapsed_ticks;
queue_t				event_queue;
repeating_timer_t	rep_timer;


//@@@ Forward declarations of private functions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bool timer_callback(repeating_timer_t *rt);


//@@@ Public functions (that have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void in_init(void)
{
	alarm_pool_t* al_pool = alarm_pool_get_default();

	queue_init(&event_queue, sizeof(in_Event_t), cfINPUT_QUEUE_LEN);

	for (uint8_t i = 0; i < cfNUM_BUTT; i++)
	{
		b_states[i].is_held = false;
		b_states[i].held_ticks = 0;
		b_states[i].shift_reg = 0b10;
	}

	if (!alarm_pool_add_repeating_timer_us(al_pool, (-1000000 / cfINPUT_POLL_HZ), \
											timer_callback, NULL, &rep_timer)) {
		panic("input.c: Failed to add input timer\n");
	}

	return;
}


bool in_get_pending(in_Event_t* event)
{
	return queue_try_remove(&event_queue, event);
}


void in_dump(in_Event_t* event)
{
	if (event->type == evtRELEASE) {
		printf("Button id %d up\n", (int)event->id);
	} else if (event->type == evtPRESS) {
		printf("Button id %d down\n", (int)event->id);
	} else if (event->type == evtREPEAT) {
		printf("Button id %d rept\n", (int)event->id);
	} else {
		;	// Never reached
	}
}


//@@@ Private functions (that don't have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bool timer_callback(repeating_timer_t *rt)
{
	static const uint64_t	deb_mask = (ULLONG_MAX >> (64-cfBUTT_DBOUNCE_MIN));

	// Number of times the callback must run between repetitions of repeating buttons.
	static const uint16_t	butt_rept_intval = (cfINPUT_POLL_HZ / cfBUTT_REPT_HZ);
	static_assert(butt_rept_intval);

	// Number of callback runs required before held buttons start repeating.
	static const uint16_t	butt_rept_thres = ((1000*cfBUTT_REPT_DELAY)/(1000000/cfINPUT_POLL_HZ));
	static_assert(butt_rept_thres);

	in_Event_t				tmp_event;	// To be copied to queue, so needs only in-function scope.

	for (uint8_t i = 0; i < cfNUM_BUTT; i++) {
		b_states[i].shift_reg <<= 1;
		b_states[i].shift_reg |= (uint64_t)(!gpio_get(in_gpios[i]));

		if ((b_states[i].shift_reg & deb_mask) == 0) {	// Debounced as RELEASED.
			if (b_states[i].is_held) {	// Known stored state is HELD.
				b_states[i].is_held = false;	// Store state as RELEASED.
				tmp_event.id = in_gpios[i];
				tmp_event.type = evtRELEASE;
				queue_try_add(&event_queue, &tmp_event);	// Enqueue RELEASE event.
			} else {	// Known stored state is already RELEASED,
				;		// hence has already been enqueued once, do nothing.
			}
		} else if ((b_states[i].shift_reg & deb_mask) == deb_mask) {	// Debounced as HELD.
			if (b_states[i].is_held) {	// Known stored state is already HELD. Calc repeat:
				b_states[i].held_ticks += 1;	// Increase "button-down duration" counter.
				if (b_states[i].held_ticks >= butt_rept_thres) {
					b_states[i].held_ticks = (butt_rept_thres - butt_rept_intval);
					tmp_event.id = in_gpios[i];
					tmp_event.type = evtREPEAT;
					queue_try_add(&event_queue, &tmp_event);	// Enqueue REPEAT event.
				}
			} else {	// Known stored state is RELEASED.
				b_states[i].is_held = true;	// Store state as HELD.
				b_states[i].held_ticks = 0;
				tmp_event.id = in_gpios[i];
				tmp_event.type = evtPRESS;
				queue_try_add(&event_queue, &tmp_event);	// Enqueue PRESS event.
			}
		} else {
			;	// Not debounced, lowest CF_BUTTONS_DEBOUNCE_THRES of shift-reg stream
				// not all identical.
		}
	}
	++elapsed_ticks;
	return true;
}
