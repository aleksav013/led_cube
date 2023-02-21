#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "init.h"
#include "draw.h"
#include "tests.h"
#include "font.h"

void draw_letter(char c)
{
	uint8_t data[9];
	data[0] = 1;
	memcpy(&data[1], &font8x8_basic[c], 8);
	send_raw_data(data);
	sleep_ms(1000);
}

void draw_letter2(char c)
{
	uint64_t data[8];
	for(int i = 0; i<8; i++) {
		data[i] = 0LL;
		for(int j = 0; j<8; j++) {
			cube_set_led(data, 0, j, i, (font8x8_basic[c][i] >> j) & 1);
		}
	}
	draw(data, 1000);
}

int main()
{
	stdio_init_all();
	init_pins();
	init_map();
	//test_every_pin();

	uint64_t data[8];
	while(1) {
		//test_every_floor();
		//test_sphere();
		/*for (int i = 0; i < 8; i++)
			data[i] = 0LL;
		draw_letter2('x');
		for (int x = 0; x < 8; x++) {
			cube_set_led(data, x, 0, 0, 1);
			draw(data, 100);
		}
		draw_letter2('y');
		for (int y = 0; y < 8; y++) {
			cube_set_led(data, 0, y, 0, 1);
			draw(data, 100);
		}
		draw_letter2('z');
		for (int z = 0; z < 8; z++) {
			cube_set_led(data, 0, 0, z, 1);
			draw(data, 100);
		}
		for (int i = 32; i<128; i++) {
			//draw_letter(i);
			draw_letter2(i);
		}*/
		const char *tekst = "Aki kad ces kocku da zavrsavas?";
		for (int i = 0; tekst[i]!='\0'; i++)
			draw_letter2(tekst[i]);
	}

	return 0;
}
