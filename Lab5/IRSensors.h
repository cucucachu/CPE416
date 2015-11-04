#ifndef IR_SENSORS
#define IR_SENSORS

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>
#include "globals.h"

#define FULL_CIRCLE 50

volatile uint16_t left_count;
volatile uint16_t right_count;

void ir_init();


void init_encoder();


ISR(PCINT0_vect);

ISR(PCINT1_vect);


#endif
