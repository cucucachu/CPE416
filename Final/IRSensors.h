#ifndef IR_SENSORS
#define IR_SENSORS

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>
#include "globals.h"

#define SENSOR_CALIBRATION .39
#define BLACK 77
#define WHITE 7

#define RANGE_FINDER_PIN 5
#define RANGE_TO_CENTIMETERS .17647

#define LEFT 0
#define RIGHT 1

volatile uint16_t left_count;
volatile uint16_t right_count;

// Wheel Encoder
void ir_init();
void init_encoder();
ISR(PCINT0_vect);
ISR(PCINT1_vect);

// Line Sensors
uint8_t read_ir_sensor(uint8_t which_eye);
void eye_exam();

// Range Sensor
uint8_t get_range();

#endif
