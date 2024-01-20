//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import project headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "config.h"
#include "debug.h"
#include "globals.h"
#include "input.h"
#include "module1.h"
#include "module2.h"

// TFT library headers
#include "st7735.h"
#include "gfx.h"
#include "gfxfont.h"
#include "font.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import system headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include <pico/multicore.h>
#include "pico/stdlib.h"
#include <pico/types.h>
#include <stdint.h>
#include <stdio.h>


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void	vertical_gradient(uint16_t from_color, uint16_t to_color, int16_t x, int16_t y, int16_t dx, int16_t dy);
void	setup_gpios(void);
char*	uint16_to_str0b(uint16_t u);
char*	uint64_to_str0b(uint64_t lld);


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

uint32_t	butt_count;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Macros & defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define	RGB565(R, G, B)	(uint16_t)(((R & 31)<<11) | ((G & 63)<<5) | (B & 31))

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ 2nd core main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

[[noreturn]] void core1_main(void)
{
	uint16_t c = 0;
	uint32_t t_iter = 0;
	uint64_t t_total = 0;
	uint64_t t_now;

	// CS=16 A0/DC=20 RST=21 SCK=18 MOSI=19
	LCD_setSPIperiph(spi0);
	LCD_setPins(20, 17, 21, 18, 19);
	LCD_initDisplay(INITR_18BLACKTAB);

	LCD_setRotation(3);

	GFX_createFramebuf();
	GFX_clearScreen();

	vertical_gradient(RGB565(31, 0, 0), RGB565(0, 0, 31), 0, 0, 160, 128);
	vertical_gradient(RGB565(0, 0, 31), RGB565(31, 0, 0), 80, 80, 40, 40);
	GFX_flush();


	do {
//		GFX_clearScreen();
		t_now = time_us_64();
		GFX_setTextColor(RGB565(31, 63, 0));
		GFX_setTextBack(RGB565(0, 0, 15));

		GFX_setCursor(0, 0);
		if (t_iter) {	// Avoid /0
			GFX_printf("gfx: %4lums avg\n", (uint32_t)(t_total/(1000*t_iter)));
		}
		GFX_printf("inp: %4luns avg\n", in_bench);
		GFX_printf("but: %4lu\n", butt_count);

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

[[noreturn]] int main(void)
{
	in_Event_t event;

	setup_gpios();
	stdio_usb_init();
	stdio_init_all();
	gl_init();
	in_init();
	multicore_launch_core1(core1_main);
	sleep_ms(1000);

	butt_count = 0;

	// Main event handling loop.
	do {
		while (in_get_pending(&event)) {
			if ((event.type == evtPRESS) || (event.type == evtREPEAT)) {
				++butt_count;
			}
			in_dump(&event);
		}
	} while (true);
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void vertical_gradient(uint16_t from_color, uint16_t to_color, int16_t x, int16_t y, int16_t dx, int16_t dy)
{
	static constexpr int16_t display_width = 160;
	static constexpr int16_t display_height = 128;

	int8_t from_R = (from_color >> 11);				// & 0b11111;
	int8_t from_G = (from_color >> 5) & 0b111111;
	int8_t from_B = from_color & 0b11111;
	int8_t to_R = (to_color >> 11);					// & 0b11111;
	int8_t to_G = (to_color >> 5) & 0b111111;
	int8_t to_B = to_color & 0b11111;
	uint32_t diff_R, diff_G, diff_B;				// Colour component change per step,
													// scaled up by 2^24.

	if (dy == display_height) {
		diff_R = ((to_R - from_R) << (24-7));		// (n/128) ≍ (n>>7),
		diff_G = ((to_G - from_G) << (24-7));		//		 1 clock cycle
		diff_B = ((to_B - from_B) << (24-7));
	} else {
		diff_R = ((to_R - from_R) << 24) / dy;		// 8 clock cycles
		diff_G = ((to_G - from_G) << 24) / dy;
		diff_B = ((to_B - from_B) << 24) / dy;
	}
	uint32_t scR = from_R << 24;
	uint32_t scG = from_G << 24;
	uint32_t scB = from_B << 24;
	uint16_t R, G, B;

	for (int16_t i = 0; i < dy; i++) {
		R = ((scR >> 13) & 0b1111100000000000);
		G = ((scG >> 19) & 0b0000011111100000);
		B = ((scB >> 24));

		GFX_drawFastHLine(x, i+y, dx, (R|G|B));

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
