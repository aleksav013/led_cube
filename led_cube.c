#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>

// define the pins used controlling 74HC595
#define DATA_PIN 2
#define CLOCK_PIN 3
#define LATCH_PIN 4

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

// define the order of 74HC595 chain
#define MINUS 0
#define FIRST_PLUS 1
#define SECOND_PLUS 2
#define THIRD_PLUS 3
#define FOURTH_PLUS 4
#define FIFTH_PLUS 5
#define SIXTH_PLUS 6
#define SEVENTH_PLUS 7
#define EIGHTH_PLUS 8

void init_map(void)
{
	map[0] = MINUS;
	map[1] = FIRST_PLUS;
	map[2] = SECOND_PLUS;
	map[3] = THIRD_PLUS;
	map[4] = FOURTH_PLUS;
	map[5] = FIFTH_PLUS;
	map[6] = SIXTH_PLUS;
	map[7] = SEVENTH_PLUS;
	map[8] = EIGHTH_PLUS;

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
	for (size_t i = 0; i < 8; i++) {
		data[i] = (on_floor >> (8 * i)) & 0xFF;
	}

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
	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			for (size_t z = 0; z < 8; z++) {
				data[z] = 1 << (y * 8 + x);
				draw(data);
				data[z] = 0;
				sleep_ms(20);
			}
		}
	}
}


int main()
{
	init_pins();
	init_map();

	while(1) {
		test();
		test_every_pin();
	}

	return 0;
}
