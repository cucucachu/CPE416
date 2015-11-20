#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"
#include "IRSensors.h"
#include "LineFollowing.h"
#include "MonteCarlo.h"
#include "globals.h"

#define NUM_BLOCKS 1
#define BLOCK_POS_1 45
#define VADER 0;

#define NUM_PARTICLES 100
#define NINETY_DEGREES 29

#define POSITION_PROBABILITY_THRESHOLD 20
#define TRAVEL_DISTANCE 10
#define TICKS_PER_DEGREE 10
#define MOTION_NOISE 1

void wait();
float find_location();
void move_robot();
void move_particles(Particle particles[]);
void return_of_the_jedi(float starting_position);
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

int main() {
	float position;
	all_init();
	/*
	while (1) {
		move_robot();
		clear_screen();
		print_num(get_range());
		_delay_ms(400);
	}*/
	position = find_location();
	clear_screen();
	print_num((int)position);
	
	_delay_ms(600);
	
	return_of_the_jedi(position);
	return 0;
}


float find_location() {
	while (standard_deviation(particles, NUM_PARTICLES) > POSITION_PROBABILITY_THRESHOLD) {
		// move robot
		move_robot();
		clear_screen();
		print_string("Stopped");
	
		// move particles
		move_particles(particles);
	
		// monte carlo
		monte_carlo(map, particles, NUM_PARTICLES, get_range());
	
		// check std_dev
		_delay_ms(500);
	}
	
	return mean_position(particles, NUM_PARTICLES);
}

void return_of_the_jedi(float starting_position) {
	int distance;
	int start_count = left_count;
	float vader = vader_position(map);
	
	clear_screen();
	print_string("Hunt");
	
	if (starting_position <= vader)
		distance = (vader - starting_position) * TICKS_PER_DEGREE;
	else 
		distance = (360 -(starting_position - vader)) * TICKS_PER_DEGREE;
	
	while (left_count < start_count + distance) {
		motor_command = compute_proportional(read_ir_sensor(LEFT), read_ir_sensor(RIGHT));
	
		motors(motor_command);
		_delay_ms(DELAY);
	}
	
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
	
	while (left_count < 300);
	
	motor_command.left = 0;
	motor_command.right = 0;
	motors(motor_command);
}

void move_robot() {
	MotorCommand motor_command;
	int start = left_count;
	
	while (left_count < start + (TICKS_PER_DEGREE * TRAVEL_DISTANCE)) {
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

void map_init() {
	float block_positions[NUM_BLOCKS];
	int i;
	
	block_positions[0] = BLOCK_POS_1;
	
	map = create_map(NUM_BLOCKS, block_positions, VADER);
	
	for (i = 0; i < NUM_PARTICLES; i++)
		particles[i].position = 360 * random_float();
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
