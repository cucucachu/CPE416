#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"
#include "IRSensors.h"
#include "globals.h"

#define FULL_SPEED 60
#define NINETY_DEGREES 29
#define SIDE_LENGTH 2.8
#define DIAGONAL_LENGTH 3

void move_forward(float rotations);
void turn_left();
void turn_right();
void turn_quarter_left();
void turn_quarter_right();
void wait();
void test();
void init();

void all_init() {
	init();
	ir_init();
	init_lcd();
	motor_init();
	wait();
	
}

int main() {
	all_init();	
	while(1) {
		move_forward(SIDE_LENGTH);
		turn_right();
	}
}

void test() {
	int current_right = 0;
	motor(1, 20);
	motor(0, 20);
	
	clear_screen();
	lcd_cursor(2, 0);
	print_string("test");
	
	while(1) {
		if (right_count != current_right) {
			clear_screen();
			lcd_cursor(2, 0);
			print_num(right_count);
			current_right = right_count;
		}
	}
}

void move_forward(float rotations) {
	int left_end;
	int right_end;
	
	left_count = 0;
	right_count = 0;
	
	left_end = rotations * FULL_CIRCLE;
	right_end = rotations * FULL_CIRCLE;
	
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, FULL_SPEED);
	
	while(left_count < left_end || right_count < right_end);
	
	
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
}

void turn_left() {
	int left_end;
	int right_end;
	
	left_count = 0;
	right_count = 0;
	
	left_end = NINETY_DEGREES;
	right_end = NINETY_DEGREES;
	
	motor(LEFT_MOTOR, -FULL_SPEED);
	motor(RIGHT_MOTOR, FULL_SPEED);
	
	while(left_count < left_end || right_count < right_end);
	
	
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
	
}

void turn_right() {
	int left_end;
	int right_end;
	
	left_count = 0;
	right_count = 0;
	
	left_end = NINETY_DEGREES;
	right_end = NINETY_DEGREES;
	
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, -FULL_SPEED);
	
	while(left_count < left_end || right_count < right_end);
	
	
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
	
}

void turn_quarter_left() {
	int left_end;
	int right_end;
	
	left_count = 0;
	right_count = 0;
	
	left_end = (float)NINETY_DEGREES / 2.;
	right_end = (float)NINETY_DEGREES / 2.;
	
	motor(LEFT_MOTOR, -FULL_SPEED);
	motor(RIGHT_MOTOR, FULL_SPEED);
	
	while(left_count < left_end || right_count < right_end);
	
	
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
	
}

void turn_quarter_right() {
	int left_end;
	int right_end;
	
	left_count = 0;
	right_count = 0;
	
	left_end = (float)NINETY_DEGREES / 2.;
	right_end = (float)NINETY_DEGREES / 2.;
	
	motor(LEFT_MOTOR, FULL_SPEED);
	motor(RIGHT_MOTOR, -FULL_SPEED);
	
	while(left_count < left_end || right_count < right_end);
	
	
	motor(LEFT_MOTOR, 0);
	motor(RIGHT_MOTOR, 0);
	
}


void wait() {
	lcd_cursor(1, 0);
	print_string("Listo");
	
	while (!get_btn());
	
	clear_screen();
	lcd_cursor(3, 0);
	print_string("Go");
	_delay_ms(200);
}
