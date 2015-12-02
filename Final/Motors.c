#include "Motors.h"
#include "globals.h"

void motor_init() {
	motor(0, 0);
	motor(1, 0);
}

void motors(MotorCommand motor_command) {
	motor(LEFT_MOTOR, motor_command.left);
	motor(RIGHT_MOTOR, motor_command.right);
}

void motor(uint8_t num, int8_t speed) {
	
   if(num == RIGHT_SERVO)
      speed = speed/100.0 * MAXSPEEDRANGE + 127;
   else 
      speed = -1*speed/100.0 * MAXSPEEDRANGE + 127;
   
   set_servo(num, speed);
}

void motor_forward() {
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, FULL_SPEED);
}

void motor_backward() {
	motor(LEFT_MOTOR, -FULL_SPEED);
	motor(RIGHT_MOTOR, -FULL_SPEED);
}

void motor_spin() {
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, -FULL_SPEED);
}

void motor_stop() {
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
}
