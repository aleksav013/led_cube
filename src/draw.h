#ifndef DRAW_H
#define DRAW_H
// library used for manipulating and displaying cube matrix

#include "pico/stdlib.h"

extern uint8_t map[9]; // map[] is defined in init.h

void send_raw_data(uint8_t data[9]);
void send_data(uint8_t floor, uint64_t on_floor);
void cube_set_led(uint64_t data[8], uint8_t x, uint8_t y, uint8_t z, bool value);
int64_t zero_byte(alarm_id_t id, void* user_data);
void draw(uint64_t data[8], uint32_t time);

#endif
