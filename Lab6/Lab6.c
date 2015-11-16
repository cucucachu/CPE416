#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"
#include "IRSensors.h"
#include "globals.h"
#include "WheelFollowing.h"

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
   ws_init();
	motor_init();
	wait();
	
}

int main() {
	all_init();	
	while(1) {
      motors(compute_proportional(read_ir_sensor(0), read_ir_sensor(1)));
      print_num(left_count);
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


void wait() {
	lcd_cursor(1, 0);
	print_string("Listo");
	
	while (!get_btn());
	
	clear_screen();
	lcd_cursor(3, 0);
	print_string("Go");
	_delay_ms(200);
}
