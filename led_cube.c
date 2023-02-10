#include "pico/stdlib.h"
#include "config.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void init_pins(void)
{
	gpio_init(DATA_PIN);
	gpio_init(CLOCK_PIN);
	gpio_init(LATCH_PIN);
	gpio_set_dir(DATA_PIN, GPIO_OUT);
	gpio_set_dir(CLOCK_PIN, GPIO_OUT);
	gpio_set_dir(LATCH_PIN, GPIO_OUT);
        printf("pin initialization successful!\n");
}

uint8_t map[9];

void init_map(void)
{
	map[0] = CHIP_0;
	map[1] = CHIP_1;
	map[2] = CHIP_2;
	map[3] = CHIP_3;
	map[4] = CHIP_4;
	map[5] = CHIP_5;
	map[6] = CHIP_6;
	map[7] = CHIP_7;
	map[8] = CHIP_8;
}

void send_raw_data(uint8_t data[9])
{
	gpio_put(LATCH_PIN, 0);
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 8; j++)
		{
			gpio_put(DATA_PIN, data[map[i]] & (1 << j));
			gpio_put(CLOCK_PIN, 0);
			gpio_put(CLOCK_PIN, 1);
		}
	}
	gpio_put(LATCH_PIN, 1);
}

void send_data(uint8_t floor, uint64_t on_floor)
{
	uint8_t data[9];
	data[0] = floor;
	memcpy(&data[1], &on_floor, 8);
	send_raw_data(data);
}

void draw(uint64_t data[8])
{
	for (size_t i = 0; i < 8; i++) {
		send_data((1 << i), data[i]);
	}
}


void test(void)
{
	for (size_t i = 0; i < 8; i++) {
		send_data((1 << i), 0xFFFFFFFFFFFFFFFF);
		sleep_ms(200);
	}
}

void test_every_pin(void)
{
	uint64_t data[8];
	memset(data, 0, 64);

	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			for (size_t z = 0; z < 8; z++) {
				data[z] = 1LL << (y * 8 + x);
				draw(data);
				data[z] = 0;
				sleep_ms(20);
			}
		}
	}
}


int main()
{
	stdio_init_all();
	init_pins();
	init_map();

	while(1) {
		test();
		test_every_pin();
	}

	return 0;
}
