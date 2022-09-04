#pragma once

#include <avr/io.h>

void pwm_on();
void pwm_off();

// brightness levels range from 0 (off) to 4 (zomgblinding)
void fade(uint8_t from, uint8_t to);
