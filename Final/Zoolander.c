/*
 * Lab 7 / Final. 
 * Cody Jones and Gabriel Hernandezd
 * 
 * Robot will spin around looking for cans. Once can is found it will move forward until
 * it reaches the edge of the board, as marked by black tape. The robot then attempts to
 * move back to the middle and start over.
 */


#include "globals.h"
#include "Motors.h"
#include "IRSensors.h"

#define HALF_WAY_DISTANCE 115
#define FULL_CIRCLE 100
#define NINETY_DEGREES 29
#define MAX_RANGE 25
#define SPIN_SPEED 40

// State functions
void go_to_center();
void find_target();
void attack();
void straighten_out();
void wait();

// Motor Functions
void motor_forward();
void motor_backward();
void motor_spin_right();
void motor_spin_left();
void motor_stop();

void (*state)() = &find_target; 
int first_led_to_hit = LEFT;

void init_all() {
	init();
	motor_init();
	ir_init();
	init_lcd();
	wait();
}

int main() {
	init_all();
	//eye_exam();
	while (1) {
		state();
		_delay_ms(300);
	}
}

void go_to_center() {
	clear_screen();
	print_string("BackUp");
	
	left_count = 0;
	
	motor_backward();
	while (left_count < HALF_WAY_DISTANCE);
	
	state = &find_target;
	motor_stop();
}

void find_target() {
	clear_screen();
	print_string("Targg");
	
	motor_spin_left();
	
	left_count = 0;
	while (get_range() > MAX_RANGE && left_count < 5 * NINETY_DEGREES) {
		clear_screen();
		print_num(get_range());
		_delay_ms(20);
	}
	
	motor_stop();
	
	if (left_count >= 5 * NINETY_DEGREES) {
		motor_forward();
		left_count = 0;
		while (left_count < 90);
		motor_stop();
	}
	else {
		motor_spin_right();
		_delay_ms(20);
		motor_stop();
	
		state = &attack;
	}
}

void attack() {
	int left, right;
	clear_screen();
	print_string("Attack");
   motor_forward();

   while(1) {
   		left = read_ir_sensor(LEFT);
   		right = read_ir_sensor(RIGHT);
   		
   		if (left >= BLACK && right < BLACK) {
   			first_led_to_hit = LEFT;
   			break;
   		}
   		else if (right >= BLACK && left < BLACK) {
   			first_led_to_hit = RIGHT;
   			break;
   		}
   		else if (left >= BLACK && right >= BLACK) {
   			first_led_to_hit = 47;
   			break;
   		}
   } 


   motor_stop();
   state = &straighten_out;

}

void straighten_out() {
	clear_screen();
	print_string("Fix");
	
	if (first_led_to_hit != 47) {	
		if (first_led_to_hit == LEFT)
			motor_spin_left();
		else if (first_led_to_hit == RIGHT)
			motor_spin_right();

		left_count = 0;	
		while (left_count < 5);

		motor_stop();
	}
	state = &go_to_center;
	
}



void wait() {
	clear_screen();
	lcd_cursor(1, 0);
	print_string("Listo");
	_delay_ms(500);
	while (!get_btn());
	
	clear_screen();
	lcd_cursor(3, 0);
	print_string("Go");
	_delay_ms(400);
}

// Motor Functions
void motor_forward() {
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, FULL_SPEED);
}

void motor_backward() {
	motor(LEFT_MOTOR, -FULL_SPEED);
	motor(RIGHT_MOTOR, -FULL_SPEED);
}

void motor_spin_left() {
	motor(LEFT_MOTOR, -SPIN_SPEED);
	motor(RIGHT_MOTOR, SPIN_SPEED);
}

void motor_spin_right() {
	motor(LEFT_MOTOR, SPIN_SPEED);
	motor(RIGHT_MOTOR, -SPIN_SPEED);
}

void motor_stop() {
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
}
