/* Cody Jones and Gabriel Hernandez
 * Lab 3 
 * Description: 
 * Line following robot. Press button twice to start.
 **/
#ifndef LINE_FOLLOWING
#define LINE_FOLLOWING

#include "globals.h"
#include "Motors.h"
#include "IRSensors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAXSPEEDRANGE   27.0
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
MotorCommand compute_proportional(uint8_t left, uint8_t right) {

#endif
