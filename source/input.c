//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "input.h"


//@@@ Private type definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

typedef struct {
	uint16_t				time_held;
	uint64_t				bitstream;
	enum { NONHELD, HELD }	actuation;
} ButtonState_t;


//@@@ Public global variables (that have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const uint8_t				in_gpios[] = cfBUTT_GPIOS;


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ButtonState_t				b_states[cfNUM_BUTT];
uint64_t					in_total_callbacks = 0;
queue_t						event_queue;
repeating_timer_t			rep_timer;
uint32_t					in_bench;


//@@@ Forward declarations of private functions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bool timer_callback(repeating_timer_t *rt);


//@@@ Public functions (that have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void in_init(void)
{
	alarm_pool_t* al_pool = alarm_pool_get_default();

	queue_init(&event_queue, sizeof(in_Event_t), cfINPUT_QUEUE_LEN);

	for (uint8_t i = 0; i < cfNUM_BUTT; i++)
	{
		b_states[i].actuation = NONHELD;
		b_states[i].time_held = 0;
		b_states[i].bitstream = 0b10;
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
		printf("b%du ", (int)event->id);
	} else if (event->type == evtPRESS) {
		printf("b%dd ", (int)event->id);
	} else if (event->type == evtREPEAT) {
		printf("b%dr ", (int)event->id);
	} else {
		;	// Never reached
	}
	return;
}


//@@@ Private functions (that don't have declarations in input.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bool timer_callback(repeating_timer_t *rt)
{
	static uint64_t t_total = 0;
	static uint32_t t_iter = 0;
	uint64_t t_now = time_us_64();

	// Bit-mask for the debouncing check. Set lower cfBUTT_CONSEC_MIN bits.
	static constexpr uint64_t	deb_mask = (ULLONG_MAX >> (64-cfBUTT_CONSEC_MIN));

	// Button repeat interval in unit "number of calls of this callback".
	static constexpr uint16_t	b_rept_intval = (cfINPUT_POLL_HZ / cfBUTT_REPT_HZ);

	// Button repeat delay in unit "number of calls of this callback".
	static constexpr uint16_t b_rept_thres = ((1000*cfBUTT_REPT_DELAY)/(1000000/cfINPUT_POLL_HZ));

	static_assert(b_rept_intval);	// Prevent nasty fuck-ups during testing.
	static_assert(b_rept_thres);	// Prevent nasty fuck-ups during testing.

	in_Event_t tmp_event;	// To be copied to queue, so needs only in-function scope.

	for (uint8_t i = 0; i < cfNUM_BUTT; i++) {
		// Shift in inverted (make active-high from active-low) GPIO read from the right.
		b_states[i].bitstream = (b_states[i].bitstream << 1) | (uint64_t)(!gpio_get(in_gpios[i]));

		if ((b_states[i].bitstream & deb_mask) == 0) {	// Debounced as RELEASED.
			if (b_states[i].actuation == HELD) {	// Known stored state is HELD.
				b_states[i].actuation = NONHELD;	// Store state as RELEASED.
				tmp_event.id = in_gpios[i];
				tmp_event.type = evtRELEASE;
				queue_try_add(&event_queue, &tmp_event);	// Enqueue RELEASE event.
			} else {	// Known stored state is already RELEASED,
				;	// hence has already been enqueued once, do nothing.
			}
		} else if ((b_states[i].bitstream & deb_mask) == deb_mask) {	// Debounced as HELD.
			if (b_states[i].actuation == HELD) {	// Known stored state is already HELD,
				b_states[i].time_held += 1;	// increase "button-down duration" counter.
				if (b_states[i].time_held >= b_rept_thres) {
					b_states[i].time_held = (b_rept_thres - b_rept_intval);
					tmp_event.id = in_gpios[i];
					tmp_event.type = evtREPEAT;
					queue_try_add(&event_queue, &tmp_event);	// Enqueue REPEAT event.
				}
			} else if (b_states[i].actuation == NONHELD) {	// Known stored state is RELEASED.
				b_states[i].actuation = HELD;	// Store state as HELD.
				b_states[i].time_held = 0;
				tmp_event.id = in_gpios[i];
				tmp_event.type = evtPRESS;
				queue_try_add(&event_queue, &tmp_event);	// Enqueue PRESS event.
			} else {
				;	// Never reached.
			}
		} else {	// Not debounced, lowest (i.e. latest) CF_BUTTONS_DEBOUNCE_THRES number of
			;	// bits of stored GPIO reads in bitstream not all identical.
		}
	}
	++in_total_callbacks;	// Stat not used for anything yet.
	t_total += (time_us_64() - t_now);
	t_iter += 1;
	if (t_iter) {		// When wraps around to 0, avoid division by it.
		in_bench = (uint32_t)((t_total * 1000) / t_iter);
	}
	return true;
}
