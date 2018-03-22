#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef MDRIVER_H_
#define MDRIVER_H_

extern void mdriver_timer0_init();
extern void md_fwd_run(uint8_t driver_port, uint8_t driver_forward_pin);
extern void md_fwd_stop(uint8_t driver_port, uint8_t driver_forward_pin);
extern void md_bwd_run(uint8_t driver_port, uint8_t driver_forward_pin);
extern void md_bwd_stop(uint8_t driver_port, uint8_t driver_forward_pin);

#endif