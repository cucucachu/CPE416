#ifndef IR_SENSORS
#define IR_SENSORS

#include <stdint.h>
#include <util/delay.h>
#include "globals.h"

#define SENSOR_CALIBRATION .39
#define BLACK 77
#define WHITE 7

#define LEFT 0
#define RIGHT 1


void ir_init();

uint8_t read_ir_sensor(uint8_t which_eye);
void eye_exam();

#endif
