#ifndef MOTORS
#define MOTORS

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define RIGHT_SERVO     0 
#define LEFT_SERVO      1 

typedef struct MotorCommand {
	uint8_t left;
	uint8_t right;
} MotorCommand;

void motor_init();
void motors(MotorCommand motor_command);
void motor(uint8_t num, int8_t speed);

#endif
