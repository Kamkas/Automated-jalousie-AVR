#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/power.h>
#include <avr/sleep.h>
// #include <avr/wdt.h>

#include "lib/ldr_sensors.h"

// extern volatile uint16_t adc_tmp = 0;
// extern volatile uint16_t ldr_ovrflw_timer = 0;

// ISR(TIMER2_OVF_vect)
// {
// 	ldr_ovrflw_timer++;
// }

// ISR(ADC_vect)
// {
// 	adc_tmp = ADCL;
// 	adc_tmp += ADCH<<8;
// 	ADCSRA |= 1<<ADSC;
// }


/**
	Reference is set to AVcc
	adc_pin defines pin for adc measurement
**/
void ldr_adc_init(uint8_t adc_pin)
{
	ADCSRA = 0x8F;
	ADMUX = 0;
	ADMUX |= (1<<REFS0);
	ADMUX += adc_pin;
}

/**
	LDR sensors Timer2 presets:
	5min -> ldr_ovrflw_timer = 9155
	1min -> ldr_ovrflw_timer = 1831
	test 2sec -> ldr_ovrflw_timer = 61
**/
void ldr_timer2_init()
{
	// set up timer0 with prescaler = 1024
    TCCR2 |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    // initialize counter
    TCNT2 = 0;
    // enable timer0 overflow interrupt
    TIMSK |= (1 << TOIE2);
}

uint16_t get_ldr_data(uint8_t ldr_port, uint8_t ldr_pin)
{
	return adc_tmp;
}