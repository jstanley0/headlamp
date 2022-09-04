#include <avr/io.h>
#include "io.h"

void io_init()
{
    DDRB  = (1 << LED_PORT);
    PORTB = 0;
}
