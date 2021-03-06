/*
 * CPE460 - Mobile Robotics
 * Lab 6 - Localization
 * Authors: Cody Jones and Gabriel Hernandez
 */


#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"
#include "IRSensors.h"
#include "LineFollowing.h"
#include "MonteCarlo.h"
#include "globals.h"

#define NUM_BLOCKS 4
#define BLOCK_POS_1 0.
#define BLOCK_POS_2 45.
#define BLOCK_POS_3 90.
#define BLOCK_POS_4 180.
#define VADER 3

#define ALL_THE_WAY 275.
#define NUM_PARTICLES 185
#define NINETY_DEGREES 29

#define POSITION_PROBABILITY_THRESHOLD (BLOCK_WIDTH / 2.)
#define TRAVEL_DISTANCE 5.
#define TICKS_PER_DEGREE (ALL_THE_WAY / 360.)
#define MOTION_NOISE 1

void wait();
float find_location();
void move_robot();
void move_particles(Particle particles[]);
void return_of_the_jedi(float starting_position);
int ask_user(int start, int delta, int max, char *msg);
void map_init();

Map map;
Particle particles[NUM_PARTICLES];




void all_init() {
	init();
	monte_carlo_init();
	ir_init();
	init_lcd();
	motor_init();
	map_init();
	wait();
}

void callibrate() {
	MotorCommand motor_command;
	
	while (left_count < ALL_THE_WAY) {
		clear_screen();
		print_num(left_count);
	
		motor_command = compute_proportional(read_ir_sensor(LEFT), read_ir_sensor(RIGHT));
	
		motors(motor_command);
		_delay_ms(DELAY);
	}
	
	motor_command.left = 0;
	motor_command.right = 0;
	motors(motor_command);
	
	
}

int main() {
	float position;
	int i;
	all_init();
	
	//callibrate();
	//wait();
	/*
	while (1) {
		move_robot();
		clear_screen();
		print_num(get_range());
		_delay_ms(400);
	}
	*/
	while (1) {
		position = find_location();
		clear_screen();
		print_num((int)position);
		
		_delay_ms(600);
		
		return_of_the_jedi(position);
		
		while(!get_btn());
		
		_delay_ms(1000);
		for (i = 0; i < NUM_PARTICLES; i++)
			particles[i].position = 360 * random_float();
		wait();
	}
	return 0;
}


float find_location() {
	float position;
	float std_dev = variance(particles, NUM_PARTICLES);
	while (std_dev > POSITION_PROBABILITY_THRESHOLD * POSITION_PROBABILITY_THRESHOLD) {
		// move robot
		move_robot();
		// move particles
		move_particles(particles);
	
		// monte carlo
		clear_screen();
		print_num((int)get_range());
		monte_carlo(map, particles, NUM_PARTICLES, get_range());
		std_dev = variance(particles, NUM_PARTICLES);
	}
	
	position = mean_position(particles, NUM_PARTICLES);
	
	clear_screen();
	print_string("Found!");
	_delay_ms(1000);
	return position;
}

void return_of_the_jedi(float starting_position) {
	float vader = vader_position(map);
	float position;
	MotorCommand motor_command;
	
	left_count = 0;
	position = ((float)left_count / (float)TICKS_PER_DEGREE) + starting_position;
	position = position >= 360 ? position - 360 : position;
	
	while ((int)(position) < (int)vader - (BLOCK_WIDTH / 4.) ||
			(int)(position) > (int)vader + (BLOCK_WIDTH / 4.)) {
		motor_command = compute_proportional(read_ir_sensor(LEFT), read_ir_sensor(RIGHT));
		motors(motor_command);
		_delay_ms(DELAY);
	
		clear_screen();
		print_string("Hunt");
		lcd_cursor(0, 1);
		position = ((float)left_count / (float)TICKS_PER_DEGREE) + starting_position;
		position = position > 360 ? position - 360 : position;
		print_num((int)position);
		lcd_cursor(4, 1);
		print_num(vader);
	}
	
	clear_screen();
	print_string("Attack");
	
	motor_command.left = 0;
	motor_command.right = 0;
	motors(motor_command);
	
	motor_command.left = FULL_SPEED;
	motor_command.right = -FULL_SPEED;
	motors(motor_command);
	
	left_count = 0;
	while (left_count < NINETY_DEGREES);
	
	motor_command.left = FULL_SPEED;
	motor_command.right = FULL_SPEED;
	motors(motor_command);
	
	left_count = 0;
	while (left_count < 75);
	
	motor_command.left = 0;
	motor_command.right = 0;
	motors(motor_command);
}

void move_robot() {
	MotorCommand motor_command;
	
	left_count = 0;
	
	while (left_count < (TICKS_PER_DEGREE * TRAVEL_DISTANCE)) {
		clear_screen();
		print_string("Moving");
	
		motor_command = compute_proportional(read_ir_sensor(LEFT), read_ir_sensor(RIGHT));
	
		motors(motor_command);
		_delay_ms(DELAY);
	}
	
	motor_command.left = 0;
	motor_command.right = 0;
	motors(motor_command);
}

void move_particles(Particle particles[]) {
	int i;
	
	for (i = 0; i < NUM_PARTICLES; i++) {
		particles[i].position += gaussian_sample(TRAVEL_DISTANCE, MOTION_NOISE);
		if (particles[i].position > 360)
			particles[i].position -= 360;
	}
}

int get_map() {
	float block_positions[4];
	int i;
	int num_blocks;
	int vader;
	
	num_blocks = ask_user(3, 1, 4, "Blocks?");
	
	if (num_blocks == 0)
		return 0;
	
	for (i = 0; i < num_blocks; i++) {
		clear_screen();
		block_positions[i] = ask_user(180, 5, 360, "Where?");
		lcd_cursor(7, 0);
	}
	
	vader = ask_user(0, 1, num_blocks-1, "Vader?");
	
	map = create_map(num_blocks, block_positions, vader);
	
	for (i = 0; i < NUM_PARTICLES; i++)
		particles[i].position = 360 * random_float();
		
	return 1;
}

void map_init() {
	int i;
	float block_positions[5];
	
	if (get_map() == 0) {
	
		block_positions[0] = BLOCK_POS_1;
		block_positions[1] = BLOCK_POS_2;
		block_positions[2] = BLOCK_POS_3;
		block_positions[3] = BLOCK_POS_4;
		
		map = create_map(NUM_BLOCKS, block_positions, VADER);
	
	}
	for (i = 0; i < NUM_PARTICLES; i++)
		particles[i].position = 360 * random_float();
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

int ask_user(int start, int delta, int max, char *msg) {
	int num = start;
	int tilt;

	num = 0;

	while (!get_btn()) {
		clear_screen();
		print_string(msg);
		
		tilt = get_accel_y();
		
		if (tilt > 180 && tilt < 360)
			num += ((360 - tilt) / 4) * delta;
		else if (tilt > 0 && tilt < 180)
			num -= tilt / 4 * delta;
		
		num = num <= 0 ? 0 : num;
		num = num > max ? max : num;
		
		lcd_cursor(2, 1);	
		print_num(num);
		_delay_ms(800);
	}
	
	clear_screen();
	print_string("Got it...");
	_delay_ms(500);
	return num;
}
