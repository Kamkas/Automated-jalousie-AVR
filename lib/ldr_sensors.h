#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef LDR_SENSORS_H_
#define LDR_SENSORS_H_


void ldr_adc_init(uint8_t adc_pin);
void ldr_timer2_init();
uint16_t get_ldr_data(uint8_t ldr_port, uint8_t ldr_pin);

#endif