#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "inc/display.h"
#include "tests/display_test.h"

int main()
{

	display_init();

	all_test_run();

	// Parte do código para exibir a mensagem no display (opcional: mudar ssd1306_height para 32 em ssd1306_i2c.h)

restart:

	uint8_t bitmap_128x64[] = {
		0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x80, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x7f, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x3f, 0x80, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x1f, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x80, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x07, 0x80, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0x07, 0x80, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x03, 0x80, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x80, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0x80, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0x00, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0x7f, 0x00, 0x00, 0x80, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x90, 0x00, 0x00,
		0xff, 0xff, 0x7f, 0x00, 0x00, 0x08, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0x7f, 0x00, 0x00, 0x04, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x06, 0x00, 0x00,
		0xff, 0xff, 0x7f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x20, 0x1f, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x30, 0x1e, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x1c, 0x1e, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x0c, 0x1e, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x0e, 0x1c, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0xce, 0x19, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xce, 0x1b, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0xce, 0x0b, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x4f, 0x08, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0xcf, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0xcf, 0x02, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x01, 0x8f, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x0f, 0x02, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x03, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x0f, 0x02, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x03, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x0f, 0x08, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x03, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 0x1e, 0x04, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x03, 0x1e, 0x06, 0x00, 0x00, 0xff, 0xff, 0xf7, 0x00, 0x1e, 0x07, 0x00, 0x00,
		0xff, 0xff, 0x67, 0x00, 0x1e, 0x07, 0x00, 0x00, 0xff, 0xff, 0x37, 0x00, 0x3e, 0x06, 0x00, 0x00,
		0xff, 0xff, 0x1b, 0x00, 0x1e, 0x04, 0x00, 0x00, 0xff, 0xff, 0x43, 0x00, 0x1e, 0x00, 0x00, 0x00,
		0xff, 0xff, 0x71, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xff, 0xff, 0x79, 0x00, 0x1c, 0x00, 0x00, 0x00,
		0xff, 0xff, 0x79, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7d, 0x00, 0x18, 0x00, 0x08, 0x00,
		0xff, 0xff, 0x21, 0x00, 0x18, 0x00, 0x08, 0x00, 0xff, 0xff, 0x01, 0x02, 0x10, 0x00, 0x08, 0x00,
		0xff, 0xff, 0x01, 0x86, 0x10, 0x04, 0x00, 0x00, 0xff, 0xff, 0x01, 0x84, 0x01, 0x00, 0x00, 0x00,
		0xff, 0xff, 0x01, 0xc4, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0x01, 0xc0, 0x03, 0x00, 0x10, 0x00,
		0xff, 0xff, 0x01, 0xc0, 0x03, 0x00, 0x10, 0x00, 0xff, 0xff, 0x01, 0xe0, 0x03, 0x00, 0x30, 0x00,
		0xff, 0xff, 0x01, 0xe0, 0x03, 0x00, 0x30, 0x00, 0xff, 0xff, 0x01, 0xf0, 0x03, 0x01, 0x20, 0x00,
		0xff, 0xff, 0x01, 0xf8, 0x01, 0x00, 0x20, 0x00, 0xff, 0xff, 0x01, 0xfc, 0x00, 0x00, 0x20, 0x00,
		0xff, 0xff, 0x01, 0x7e, 0x00, 0x00, 0x60, 0x00, 0xff, 0xff, 0x01, 0x3f, 0x00, 0x00, 0x60, 0x00,
		0xff, 0xff, 0x81, 0x3f, 0x04, 0x00, 0x60, 0x00, 0xff, 0xff, 0x83, 0x3f, 0x04, 0x00, 0x40, 0x00,
		0xff, 0xff, 0x83, 0x1f, 0x04, 0x00, 0x62, 0x00, 0xff, 0xff, 0x83, 0x9f, 0x0c, 0x00, 0x43, 0x00,
		0xff, 0xff, 0x87, 0x9f, 0x08, 0x00, 0x02, 0x00, 0xff, 0xff, 0x87, 0xdf, 0x00, 0x80, 0x00, 0x00,
		0xff, 0xff, 0xcf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xdf, 0x00, 0x00, 0x08, 0x00,
		0xff, 0xff, 0xff, 0x9f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x9f, 0x00, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xbf, 0x01, 0x00, 0x20, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0xe0, 0x01,
		0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0xe0, 0x01,
		0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xc0, 0x01, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x04, 0xc0, 0x01,
		0xff, 0xff, 0xff, 0x7f, 0x02, 0x02, 0xc0, 0x01, 0xff, 0xff, 0xff, 0x7f, 0x02, 0x00, 0xc0, 0x13,
		0xff, 0xff, 0xff, 0x7f, 0x03, 0x00, 0xc0, 0x07, 0xff, 0xff, 0xff, 0x7f, 0x03, 0x00, 0xc0, 0x07,
		0xff, 0xff, 0xff, 0x7f, 0x02, 0x04, 0x80, 0x07, 0xff, 0xff, 0xff, 0x7f, 0x02, 0x0c, 0x80, 0x03,
		0xff, 0xff, 0xff, 0x7f, 0x82, 0x1c, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x40, 0x1c, 0x00, 0x02,
		0xff, 0xff, 0xff, 0xff, 0x60, 0x18, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7b, 0x18, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x7f, 0x10, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0xcf, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0xcf, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xef, 0x01, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x8f, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x87, 0x07, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x87, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x0f,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xfc, 0x9f,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xfe, 0xfe};
	ssd1306_t ssd_bm;
	ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
	ssd1306_config(&ssd_bm);
	ssd1306_draw_bitmap(&ssd_bm, bitmap_128x64);

	while (true)
	{
		sleep_ms(1000);
	}

	return 0;
}