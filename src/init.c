#include "pico/stdlib.h"
#include "config.h"
#include "init.h"

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
