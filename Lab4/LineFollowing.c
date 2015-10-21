/* Cody Jones and Gabriel Hernandez
 * Lab 3 
 * Description: 
 * Line following robot. Press button twice to start.
 **/

#include "LineFollowing.h"

float sum;
float previous;

void lf_init() {
	motor_init();
	ir_init()
	
	sum = 0;
	previous = 0;
}

MotorCommand compute_proportional(uint8_t left, uint8_t right) {
	MotorCommand motor_command;
	float error;
	float present, delta;
	
	motor_command.left = FULL_SPEED;
	motor_command.right = FULL_SPEED;

	present = WEIGHT * (read_ir_sensor(RIGHT) - read_ir_sensor(LEFT));
	delta = present - previous;
	sum += present;
	
	sum = sum < -SUM_MAX ? -SUM_MAX : sum;
	sum = sum > SUM_MAX ? SUM_MAX : sum;
	
	error = PRESENT_COEFFICIENT * present + DELTA_COEFFICIENT * delta + SUM_COEFFICIENT * sum;
	error *= PROPORTION;
	
	if (error < 1 && error > -1)
		error = 0;
	
	if (error > 0) {
		motor_command.left = FULL_SPEED;
		motor_command.right = FULL_SPEED - error;
		motor_command.right = motor_command.right > 0 ? motor_command.right : 0;
	}
	else if (error < 0) {
		motor_command.right = FULL_SPEED;
		motor_command.left = FULL_SPEED + error;
		motor_command.left = motor_command.left > 0 ? motor_command.left : 0;
	}
	else {
		motor_command.right = FULL_SPEED;
		motor_command.left = FULL_SPEED;
	}
	
	previous = present;
	
	return motor_command;
}


