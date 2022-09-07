#include <avr/io.h>
#include "io.h"
#include "button.h"
#include "sync_sleep.h"

#define REPEAT_THRESHOLD 8

uint8_t get_input(int flush)
{
    static uint8_t prevState = 0;
    static uint8_t repeat = 0;

    if (flush) {
        wait_for_button_release();
        prevState = 0;
        return 0;
    }

    uint8_t curState = PINB & (1 << BUTTON_PORT);

    if (repeat >= REPEAT_THRESHOLD) {
        prevState = curState;
        if (curState == 0)
            repeat = 0;
        return 0;
    }

    if (curState != prevState) {
        repeat = 0;
        prevState = curState;
        if (curState == 0)
            return PRESS;
    } else if (curState != 0) {
        if (++repeat == REPEAT_THRESHOLD)
            return HOLD;
    }

    return 0;
}

uint8_t is_button_really_pressed()
{
    for(uint8_t i = 0; i < 3; ++i) {
        if (!(PINB & (1 << BUTTON_PORT)))
            return 0;
        sync_sleep(5);
    }
    return 1;
}

void wait_for_button_release()
{
    while(PINB & (1 << BUTTON_PORT))
        sync_sleep(50);
}
