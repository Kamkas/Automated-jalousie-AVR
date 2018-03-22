#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t adc_tmp = 0;
volatile uint16_t ldr_ovrflw_timer = 0;
volatile uint8_t md_timer = 0;

ISR(TIMER2_OVF_vect)
{
	ldr_ovrflw_timer++;
}

ISR(ADC_vect)
{
	adc_tmp = ADCL;
	adc_tmp += ADCH<<8;
	ADCSRA |= 1<<ADSC;
}

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

ISR(TIMER0_OVF_vect)
{
	md_timer++;
}

/**
	Mdriver Timer0 is set to 0.008192 sec (~ every 8 mils)
	and gain 1 overflow 
**/
void mdriver_timer0_init()
{
	// set up timer0 with prescaler = 256
    TCCR0 |= (1 << CS02);
    // initialize counter
    TCNT0 = 0;
    // enable timer0 overflow interrupt
    TIMSK |= (1 << TOIE0);
}

void md_fwd_run(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port |= (1<<driver_forward_pin);
}

void md_fwd_stop(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port &= (~(1<<driver_forward_pin));
}

void md_bwd_run(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port |= (1<<driver_forward_pin);
}

void md_bwd_stop(uint8_t driver_port, uint8_t driver_forward_pin)
{
	driver_port &= (~(1<<driver_forward_pin));
}

int main(void)
{
	DDRB = 0x00;
	PORTB = 0x00;

	DDRC = (1<<PC0);
	PORTC = 0x00;

	DDRD = 0x01; 
	PORTD = 0x00;

	ldr_adc_init(0x00);
	ldr_timer2_init();

	sei();

	while(1)
	{
		if (ldr_ovrflw_timer >= 61)
		{
			if (!(PIND&(1<<PD0)))
			{
				PORTD |= (1<<PD0);
			}
			else
			{
				PORTD &= ~(1<<PD0);
			}
			ldr_ovrflw_timer = 0;
		}
	}

	return 0;
}