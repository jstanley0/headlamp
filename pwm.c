#include <avr/io.h>
#include "io.h"
#include "pwm.h"
#include "sync_sleep.h"

void pwm_on()
{
    OCR0A = 0;
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // non-inverting fast PWM mode 3
    TCCR0B = (1 << CS00) | (1 << CS01); // 1/64 prescaler
}

void pwm_off()
{
    TCCR0B = 0;
    PORTB &= ~(1 << LED_PORT);
}

static const uint8_t BRIGHTTABLE[] = {0, 1, 6, 40, 255};

void fade(uint8_t from, uint8_t to)
{
    uint8_t dir = (from < to) ? 1 : -1;
    if (from != to) {
        for(uint8_t b = BRIGHTTABLE[from], e = BRIGHTTABLE[to]; b != e; b += dir) {
            OCR0A = b;
            sync_sleep(1);
        }
    }
    OCR0A = BRIGHTTABLE[to];
}
