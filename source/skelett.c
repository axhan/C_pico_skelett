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
//#include "FreeMonoOblique12pt_sub.h"
//#include "hw.h"
//#include "ST7735_TFT.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "gfx.h"
#include "gfxfont.h"
#include "font.h"
#include "st7735.h"


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
void setup_gpios(void);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Macros & defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ 2nd core main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void core1_main(void)
{
	int c = 1;

	// CS=16 A0/DC=20 RST=21 SCK=18 MOSI=19

	LCD_setSPIperiph(spi0);
	LCD_setPins(20, 17, 21, 18, 19);
	LCD_initDisplay(INITR_18BLACKTAB);

	LCD_setRotation(3);

	GFX_createFramebuf();

	while (true) {
		GFX_clearScreen();
		GFX_setCursor(0, 0);
		GFX_printf("Hello GFX!\n%d", c++);
		GFX_flush();
		sleep_ms(50);

	}

/*	spi_init(spi0, 1000000);
	tft_spi_init();
	sleep_ms(1000);
	TFT_BlackTab_Initialize();

	sleep_ms(1000);

	setRotation(0);
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
*/
	do {
		;
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
