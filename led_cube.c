#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "config.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

uint8_t map[9];

void init_pins(void)
{
	gpio_init(DATA_PIN);
	gpio_init(CLOCK_PIN);
	gpio_init(LATCH_PIN);
	gpio_set_dir(DATA_PIN, GPIO_OUT);
	gpio_set_dir(CLOCK_PIN, GPIO_OUT);
	gpio_set_dir(LATCH_PIN, GPIO_OUT);

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);
}

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

int64_t zero_byte(alarm_id_t id, void* user_data)
{
	memset(user_data, 0, 1);
	return 0;
}

void draw(uint64_t data[8], uint32_t time)
{
	volatile uint8_t ind = 1;
	add_alarm_in_ms(time, (void*)zero_byte, (void*)&ind, false);

	while (ind) {
		for (size_t i = 0; i < 8; i++) {
			send_data((1 << i), data[i]);
		}
		tight_loop_contents();
	}
}

void test_every_floor(void)
{
	for (size_t i = 0; i < 8; i++) {
		send_data((1 << i), 0xFFFFFFFFFFFFFFFF);
		sleep_ms(125);
	}
}

#define PIN(x, y) (1LL << ((y) * 8 + (x)))

void test_every_pin(void)
{
	uint64_t data[8];
	memset(data, 0, 64);

	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			for (size_t z = 0; z < 8; z++) {
				data[z] = PIN(x, y);
			}
			draw(data, 125);
			for (size_t z = 0; z < 8; z++) {
				data[z] = 0;
			}
		}
	}
}

void sphere(void)
{
	uint64_t data[8];

	for (size_t i = 0; i < 7; i++) {
		memset(data, 0, 64);
		for (int8_t x = 0; x < 8; x++) {
			for (int8_t y = 0; y < 8; y++) {
				for (int8_t z = 0; z < 8; z++) {
					if ((3.5-x)*(3.5-x) + (3.5-y)*(3.5-y) + (3.5-z)*(3.5-z) < 1.0*i*i) {
						data[z] = PIN(x, y);
					}
				}
			}
		}
		draw(data, 200 - i * 20);
	}
}

int main()
{
	stdio_init_all();
	init_pins();
	init_map();
	test_every_floor();
	test_every_pin();

	while(1) {
		sphere();
	}

	return 0;
}
