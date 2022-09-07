#pragma once

#define PRESS 1
#define HOLD 2
uint8_t get_input(int flush);

uint8_t is_button_really_pressed();
void wait_for_button_release();
