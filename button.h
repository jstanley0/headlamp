#pragma once

#define PRESS 1
#define HOLD 2
uint8_t get_input(int flush);

void wait_for_button_release();
