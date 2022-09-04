#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "sync_sleep.h"

volatile uint8_t wakeup;
ISR(TIMER1_COMPA_vect)
{
	wakeup = 1;
}

void sync_sleep(uint8_t kiloclocks)
{
	TCCR1 = 0;            // stop the timer
	TIFR |= (1 << OCF1A); // clear output-compare A flag
	OCR1A = kiloclocks;	  // set compare match A target
	TCNT1 = 0;            // reset timer counter
	if (kiloclocks > 0) {
		TIMSK |= (1 << OCIE1A);	// enable compare match A interrupt
	}
	wakeup = 0;

	// start timer with 1/1024 prescaler
	TCCR1 = (1 << CS13) | (1 << CS11) | (1 << CS10);

	// sleep until it's time to wake up
	// use a loop here because other interrupts will happen
	set_sleep_mode(SLEEP_MODE_IDLE);
	do {
		sleep_mode();
	} while( !wakeup );

	TIMSK &= ~(1 << OCIE1A); // stop the interrupt
	TCCR1 = 0;		         // stop the timer
}
