#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/power.h>
#include <avr/sleep.h>
// #include <avr/wdt.h>

#include "mdriver.h"

volatile uint8_t md_timer = 0;

ISR(TIMER0_OVF_vect)
{
	md_timer++;
}

/**
	Mdriver Timer0 is set to 0.008192 sec (~ every 8 mils)
	and gain 1 overflow 
**/
extern void mdriver_timer0_init()
{
	// set up timer0 with prescaler = 256
    TCCR0 |= (1 << CS02);
    // initialize counter
    TCNT0 = 0;
    // enable timer0 overflow interrupt
    TIMSK |= (1 << TOIE0);
}

extern void md_fwd_run(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port |= (1<<driver_forward_pin);
}

extern void md_fwd_stop(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port &= (~(1<<driver_forward_pin));
}

extern void md_bwd_run(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port |= (1<<driver_forward_pin);
}

extern void md_bwd_stop(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port &= (~(1<<driver_forward_pin));
}
