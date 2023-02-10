#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// define the pins used controlling 74HC595
#define DATA_PIN 2
#define CLOCK_PIN 3
#define LATCH_PIN 4
#define LED_PIN 25

// define the order of 74HC595 chain
#define CHIP_0 0
#define CHIP_1 1
#define CHIP_2 3
#define CHIP_3 5
#define CHIP_4 7
#define CHIP_5 8
#define CHIP_6 6
#define CHIP_7 4
#define CHIP_8 2

extern uint8_t map[9];

#endif
