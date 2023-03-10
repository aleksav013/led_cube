#include "tests.h"
#include <string.h>

void test_every_floor(void)
{
	for (size_t i = 0; i < 8; i++) {
		send_data((1 << i), 0xFFFFFFFFFFFFFFFF);
		sleep_ms(125);
	}
}

void test_every_pin(void)
{
	uint64_t data[8];
	memset(data, 0, 64);

	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			for (size_t z = 0; z < 8; z++) {
				cube_set_led(data, x, y, z, 1);
			}
			draw(data, 125);
			for (size_t z = 0; z < 8; z++) {
				data[z] = 0;
			}
		}
	}
}

void test_sphere(void)
{
	uint64_t data[8];

	for (size_t r = 0; r < 7; r++) {
		memset(data, 0, 64);
		for (int8_t x = 0; x < 8; x++) {
			for (int8_t y = 0; y < 8; y++) {
				for (int8_t z = 0; z < 8; z++) {
					if ((3.5-x)*(3.5-x) + (3.5-y)*(3.5-y) + (3.5-z)*(3.5-z) <= (float)r*r) {
						cube_set_led(data, x, y, z, 1);
					}
				}
			}
		}
		draw(data, 500);
	}
}

void test_letter(uint64_t letter)
{
	uint64_t data[8];
	for (size_t i = 0; i < 8; i++) {
		if(i<2)
			data[i] = letter;
		else
			data[i] = 0LL;
	}
	draw(data, 2000);
}
