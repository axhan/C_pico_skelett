//██████████████████████████████████████████████████████████████████████████████████████████████████
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import project headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "debug.h"
#include "globals.h"
#include "input.h"
#include "module1.h"
#include "module2.h"

//#include "FreeMonoOblique12pt7b.h"
#include "hw.h"
#include "ST7735_TFT.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import system headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//#include "pico/assert.h"
#include <stdint.h>
#include <stdio.h>
#include <pico/types.h>
//#include <time.h>

#include "pico/stdlib.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

char* uint64_to_str0b(uint64_t lld);
void setup_gpios(void);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Macros & defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int main(void)
{

	extern uint64_t elapsed_ticks;
	in_Event_t event;

	setup_gpios();
	stdio_usb_init();
	gl_init();
	in_init();

	sleep_ms(1000);
	spi_init(spi0, 1000000);
	tft_spi_init();
	sleep_ms(1000);
	// TFT_ST7735B_Initialize();
	TFT_BlackTab_Initialize();

	sleep_ms(1000);



	setRotation(0);
	// tft_width=160; tft_height=128;
	setTextWrap(true);


	fillScreen(ST7735_BLACK);
	drawText(0, 5, " !#$%&'()*+,-.", ST7735_WHITE, ST7735_BLACK, 1);
	drawText(0, 15, "0123456789",  ST7735_BLUE, ST7735_BLACK, 1);
	drawText(0, 25, "abcdefghijklmn", ST7735_RED, ST7735_BLACK, 1);
	drawText(0, 35, "ABCDEGHIJKLMN", ST7735_GREEN, ST7735_BLACK, 1);
	drawText(0, 45, "opqrstuvwxyz", ST7735_CYAN, ST7735_BLACK, 1);
	drawText(0, 55, "OPQRSTUVWYXZ", ST7735_MAGENTA, ST7735_BLACK, 1);
	drawText(0, 65, ";:=,.?@", ST7735_YELLOW, ST7735_BLACK, 1);
	drawText(0, 75, "[]/", ST7735_BLACK, ST7735_WHITE, 1);

	// Main event handling loop.
	do {
		while (in_get_pending(&event)) {
			in_dump(&event);
		}
	} while (true);

	return 0;	// Never reached.
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Private function definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


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


void setup_gpios(void)
{
	gpio_init(16);	// Display backlight
	gpio_init(17);	// Display CS
	gpio_init(20);	// Display A0/DC
	gpio_init(21);	// Display RST
	gpio_init(25);	// Onboard LED

	gpio_set_dir(16, true); gpio_put(16, 1);
	gpio_set_dir(17, true); gpio_put(17, 0);
	gpio_set_dir(20, true); gpio_put(20, 0);
	gpio_set_dir(21, true); gpio_put(21, 1);
	gpio_set_dir(25, true);

	for (uint8_t i = 0; i < cfNUM_BUTT; i++) {
		gpio_init(in_gpios[i]);
		gpio_set_function(in_gpios[i], GPIO_FUNC_SIO);
		gpio_set_dir(in_gpios[i], false);
		gpio_disable_pulls(in_gpios[i]);
	}

	gpio_set_function(4, GPIO_FUNC_SPI);	// SPI0 RX, unconnected
	gpio_set_function(18, GPIO_FUNC_SPI);	// Display SCK
	gpio_set_function(19, GPIO_FUNC_SPI);	// Display MOSI
	return;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//██████████████████████████████████████████████████████████████████████████████████████████████████
