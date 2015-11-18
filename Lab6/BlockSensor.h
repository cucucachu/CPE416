#ifndef BLOCK_SENSOR
#define BLOCK_SENSOR

#include <stdint.h>
#include <util/delay.h>
#include "globals.h"

#define BLOCK     77
#define NO_BLOCK  7

#define BLOCK_PIN 6

void block_sensor_init();

uint8_t read_block_sensor();

#endif