#ifndef CONFIG_H
#define CONFIG_H
// configuration file

// define pico gpio pins used for controlling 74HC595 chips
#define DATA_PIN 2
#define CLOCK_PIN 3
#define LATCH_PIN 4
#define LED_PIN 25

// define the order of 74HC595 chain
#define CHIP_0 0
#define CHIP_1 8
#define CHIP_2 6
#define CHIP_3 4
#define CHIP_4 2
#define CHIP_5 1
#define CHIP_6 3
#define CHIP_7 5
#define CHIP_8 7

#endif
