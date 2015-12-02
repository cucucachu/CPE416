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


