//██████████████████████████████████████████████████████████████████████████████████████████████████
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import project headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "debug.h"
#include "globals.h"
#include "input.h"
#include "module1.h"
#include "module2.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "st7735.h"
#include "gfx.h"
#include "gfxfont.h"
#include "font.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import system headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//#include "pico/assert.h"
#include <stdint.h>
#include <stdio.h>
#include <pico/multicore.h>
#include <pico/types.h>
//#include <time.h>

#include "pico/stdlib.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

char* uint64_to_str0b(uint64_t lld);
char* uint16_to_str0b(uint16_t u);
void setup_gpios(void);
void grad565(uint16_t from, uint16_t to, int16_t start_y, uint16_t steps);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

uint32_t	butt_count;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Macros & defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ 2nd core main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void core1_main(void)
{
	uint16_t c = 0;
	uint64_t t_total = 0;
	uint32_t t_iter = 0;
	uint64_t t_now;

	// CS=16 A0/DC=20 RST=21 SCK=18 MOSI=19
	LCD_setSPIperiph(spi0);
	LCD_setPins(20, 17, 21, 18, 19);
	LCD_initDisplay(INITR_18BLACKTAB);

	LCD_setRotation(3);

	GFX_createFramebuf();
	GFX_clearScreen();

	grad565(0b11111<<11, 0b11111, 0, 128);
	GFX_flush();


	do {
//		GFX_clearScreen();
		t_now = time_us_64();
		GFX_setTextColor(0b1111111111100000);
		GFX_setTextBack(0b11111);

		GFX_setCursor(0, 0);
		if (t_iter) {
			GFX_printf("gfx: %lums avg\n", (uint32_t)(t_total/(1000*t_iter)));
		}
		GFX_printf("inp: %uns avg\n", (uint32_t)(in_bench));
		GFX_printf("but: %u\n", (uint32_t)(butt_count));

//		GFX_setCursor(0, 2*8);
//		GFX_printf("11111111112222222222333333");
		GFX_setCursor(80-6*8, 60-8);
		GFX_printf("%s", uint16_to_str0b(c++));
		GFX_flush();
//		sleep_ms(50);

		++t_iter;
		t_total += (time_us_64() - t_now);

	} while (true);


}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int main(void)
{

	in_Event_t		event;

	setup_gpios();
	stdio_usb_init();
	stdio_init_all();
	gl_init();
	in_init();
	multicore_launch_core1(core1_main);
	sleep_ms(1000);

	butt_count	= 0;

	// Main event handling loop.
	do {
		while (in_get_pending(&event)) {
			if ((event.type == evtPRESS) || (event.type == evtREPEAT)) {
				++butt_count;
			}
			in_dump(&event);
		}
	} while (true);

	return 0;	// Never reached.
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void grad565(uint16_t from, uint16_t to, int16_t start_y, uint16_t steps)
{
	constexpr int16_t width = 160;
	constexpr int16_t height = 128;

	int8_t from_R = (from >> 11);					// & 0b11111;
	int8_t from_G = (from >> 5) & 0b111111;
	int8_t from_B = from & 0b11111;
	int8_t to_R = (to >> 11);						// & 0b11111;
	int8_t to_G = (to >> 5) & 0b111111;
	int8_t to_B = to & 0b11111;
	int32_t diff_R, diff_G, diff_B;

	if (steps == height) {
		diff_R = ((to_R - from_R) << (24-7));	// /128 equiv >>7
		diff_G = ((to_G - from_G) << (24-7));
		diff_B = ((to_B - from_B) << (24-7));
	} else {
		diff_R = ((to_R - from_R) << 24) / steps;
		diff_G = ((to_G - from_G) << 24) / steps;
		diff_B = ((to_B - from_B) << 24) / steps;
	}
	int32_t scR = from_R << 24;
	int32_t scG = from_G << 24;
	int32_t scB = from_B << 24;
	uint16_t R, G, B;

	for (int16_t i = 0; i < (int16_t)steps; i++) {
		R = ((scR >> 13) & 0b1111100000000000);
		G = ((scG >> 19) & 0b0000011111100000);
		B = ((scB >> 24));							// & 0b0000000000011111);

//		printf("(%d,%d,%d) ", scR>>24, scG>>24, scB>>24);
		GFX_drawFastHLine(0, i+start_y, width, (R|G|B));

		scR += diff_R;
		scG += diff_G;
		scB += diff_B;
	}
}


// Return string representation in binary of a uint64_t
char* uint64_to_str0b(uint64_t lld)
{
	static char buf[65];
	uint64_t mask = 0x8000000000000000;
	for (uint8_t i = 0; i < 64; i++) {
		buf[i] = (lld & mask) ? '1' : '0';
		mask >>= 1;
	}
	return buf;
}


// Return string representation in binary of a uint16_t
char* uint16_to_str0b(uint16_t u)
{
	static char buf[17];
	uint16_t mask = 0x8000;
	for (uint8_t i = 0; i < 16; i++) {
		buf[i] = (u & mask) ? '1' : '0';
		mask >>= 1;
	}
	return buf;
}


void setup_gpios(void)
{
// CS=17 A0/DC=20 RST=21 SCK=18 MOSI=19
	gpio_init(16);	// Display backlight
//	gpio_init(17);	// Display CS
//	gpio_init(20);	// Display A0/DC
//	gpio_init(21);	// Display RST
	gpio_init(25);	// Onboard LED

	gpio_set_dir(16, true); gpio_put(16, 1);
//	gpio_set_dir(17, true); gpio_put(17, 0);
//	gpio_set_dir(20, true); gpio_put(20, 0);
//	gpio_set_dir(21, true); gpio_put(21, 1);
	gpio_set_dir(25, true);

	for (uint8_t i = 0; i < cfNUM_BUTT; i++) {
		gpio_init(in_gpios[i]);
		gpio_set_function(in_gpios[i], GPIO_FUNC_SIO);
		gpio_set_dir(in_gpios[i], false);
		gpio_disable_pulls(in_gpios[i]);
	}

	gpio_set_function(4, GPIO_FUNC_SPI);	// SPI0 RX, unconnected
//	gpio_set_function(18, GPIO_FUNC_SPI);	// Display SCK
//	gpio_set_function(19, GPIO_FUNC_SPI);	// Display MOSI
	return;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//██████████████████████████████████████████████████████████████████████████████████████████████████
