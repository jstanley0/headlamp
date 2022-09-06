#pragma once

#include <avr/io.h>

void pwm_on();
void pwm_off();

// brightness levels range from 0 (dim) to 3 (zomgblinding)
void fade(int8_t from, int8_t to);
