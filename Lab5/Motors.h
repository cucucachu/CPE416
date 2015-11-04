#ifndef MOTORS
#define MOTORS

#include <stdint.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define RIGHT_SERVO     0 
#define LEFT_SERVO      1 
#define MAXSPEEDRANGE   27.0

typedef struct MotorCommand {
	uint8_t left;
	uint8_t right;
} MotorCommand;

void motor_init();
void motors(MotorCommand motor_command);
void motor(uint8_t num, int8_t speed);

#endif
