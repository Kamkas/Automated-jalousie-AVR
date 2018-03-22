#ifndef NEC_PROTOCOL_H_
#define NEC_PROTOCOL_H_

// port for connecting IR receiver
#define IRR_PORT PORTD
#define IRR_DDR DDRD
#define IRR_PIN PD2
#define IRR_PIN_PORT PIND
// init IR receiver pin port
#define init_IRR_PIN()  \
IRR_DDR&=~(1<<IRR_PIN); \
IRR_PORT|=(1<<IRR_PIN); \
MCUCR|=(1<<ISC00); \
GICR|=(1<<INT0);

#define NEC_MAX_PACKET_BIT_NUMBER 32

#define MAX_DELAY_FOR_REPEAT_COMMAND 100 // in ms
#define MAX_BIT_TRANSMISSION_DELAY 16 // in ms

// packet receiving state
#define PACKET_STATE_NO_PACKET 0
#define PACKET_STATE_READING 1
#define PACKET_STATE_READY 2
#define PACKET_STATE_READ 3
#define PACKET_STATE_WRITING 4
#define PACKET_STATE_WRITE 5


// Packet of data
struct IR_Packet
{
	uint8_t addr; // address
	uint8_t addr_inv; // inverted address
	uint8_t command; // command 
	uint8_t command_inv; // inverted command
	uint8_t repeat; // 0 if the packet is not repeat
};

typedef struct IR_Packet IR_Packet;

extern uint8_t check_new_packet(IR_Packet * received_packet);
extern void init_receiver();

#endif