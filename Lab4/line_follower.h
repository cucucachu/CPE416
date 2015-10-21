#ifdef LINE_FOLLOWER
#define LINE_FOLLOWER

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct motor_command {
   uint8_t left;
   uint8_t right;
} motor_command; 

#define RIGHT_SERVO     0  //Right motor when looking at screen. Goes backwards at 255
#define LEFT_SERVO      1  //Left motor when looking at screen. Goes forwards at 255
#define MAXSPEEDRANGE   27.0
#define FULL_SPEED 50

#define WEIGHT 1
#define DECAY 1
#define SUM_MAX 2500
#define PRESENT_COEFFICIENT 1
#define DELTA_COEFFICIENT .5
#define SUM_COEFFICIENT .04
#define PROPORTION .5

#define SENSOR_CALIBRATION .39
#define BLACK 77
#define WHITE 7

#define DELAY 3 // 3 for best cornering, 5 for best smoothness

#define LEFT 0
#define RIGHT 1

void setup();
void wait();
void delay(uint16_t ms);
void decay(float array[], int size);

void motor(uint8_t num, int8_t speed);
void motor_test();
motor_command compute_proportional(uint8_t left, uint8_t right);

u08 eye(u08 which_eye);
void eye_exam();
void follow_line();
#endif 