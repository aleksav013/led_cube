#include "draw.h"
#include "config.h"
#include <string.h>

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

void cube_set_led(uint64_t data[8], uint8_t x, uint8_t y, uint8_t z, bool value)
{
	uint64_t mask = 1LL << (y * 8 + x);
	if (value != (bool)(data[z] & mask))
		data[z] ^= mask;
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
			sleep_ms(1);
		}
		tight_loop_contents();
	}
}
