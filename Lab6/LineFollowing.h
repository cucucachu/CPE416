/* Cody Jones and Gabriel Hernandez
 * Lab 4 
 * Description: 
 * Encapsulates line following code from lab3.
 **/
#ifndef LINE_FOLLOWING
#define LINE_FOLLOWING

#include "globals.h"
#include "Motors.h"
#include "IRSensors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define FULL_SPEED 50

#define WEIGHT 1
#define DECAY 1
#define SUM_MAX 2500

#define PROPORTION .5
#define PRESENT_COEFFICIENT 1
#define DELTA_COEFFICIENT .5
#define SUM_COEFFICIENT .04

#define DELAY 3 // 3 for best cornering, 5 for best smoothness

void lf_init();
MotorCommand compute_proportional(uint8_t left, uint8_t right);

#endif
