#include <stdio.h>
#include <stdlib.h>

#include "Neuron.h"
#include "NeuralNetwork.h"
#include "Motors.h"
#include "IRSensors.h"
#include "Memory.h"
#include "LineFollowing.h"
#include "globals.h"

#define NUM_NEURONS 7
#define NUM_INPUT_NEURONS 2
#define NUM_OUTPUT_NEURONS 2

#define LEARNING_RATE .05
#define LEARNING_ITERATIONS 200
#define SEED 420

void setup();

void switch_state();

void learn_by_doing();

void proportional();
void capture();
void training();
void neural();

int get_training_iterations();

MotorCommand compute_neural_network(uint8_t left, uint8_t right);
void destroy();

void create_lab4_neural_network();
void neural_network_test();
float random_float();
void wait();

NeuralNetwork *neural_network;
Memory memory;
int memory_index;
int learning_index;
void (*state)(void);
int capture_count;
int number_of_iterations;

int main() {
	setup();
	wait();
	
	//learn_by_doing();
	
	while (1) {
		if (get_btn() == 1)
			switch_state();
		
		state();
	}
	
	destroy();
}

void setup() {
	init();
	init_lcd();
	lf_init();
	create_lab4_neural_network();
	
	state = &proportional;
	
	memory = calloc(MEMORY_SIZE, sizeof(IO_Pair));
	memory_index = 0;
	learning_index = 0;
	capture_count = 0;
	number_of_iterations = 0;
}

void switch_state() {

	if (state == &proportional)
		state = &capture;
	else if (state == &capture)
		state = &training;
	else if (state == &training)
		state = &neural;
	else if (state == &neural)
		state = &training;

	_delay_ms(200);
}

int get_training_iterations() {
	int num_iterations;
	int tilt;
	
	num_iterations = LEARNING_ITERATIONS;
	

	while (!get_btn()) {
		clear_screen();
		print_string("How Many");
		
		tilt = get_accel_y();
		
		if (tilt > 128)
			tilt = -(256 - tilt);
		
		num_iterations -= tilt;
		
		lcd_cursor(2, 1);	
		print_num(num_iterations);
		_delay_ms(500);
	}
	
	return num_iterations;
}

void proportional() {
	Input input;
	MotorCommand motor_command;
	
	clear_screen();
	print_string("Proportional");
	
	input.left = read_ir_sensor(LEFT);
	input.right = read_ir_sensor(RIGHT);
	
	motor_command = compute_proportional(input.left, input.right);
	
	motors(motor_command);
	_delay_ms(DELAY);
}

void capture() {
	Input input;
	motor(LEFT, 0);
	motor(RIGHT, 0);
	
	if (memory == 0) {
		clear_screen();
		lcd_cursor(0, 0);
		print_string("MemError");
		while(1);
	}
	
	if (memory_index < MEMORY_SIZE) {
	
		input.left = read_ir_sensor(LEFT);
		input.right = read_ir_sensor(RIGHT);
		
		if (capture_count == 0) {
			clear_screen();
			lcd_cursor(0, 0);
			print_string("Data");
			lcd_cursor(5, 0);
			print_num(memory_index);
			lcd_cursor(0, 1);
			print_num(input.left);
			lcd_cursor(4, 1);
			print_num(input.right);
		}
	
		memory[memory_index].input = input;
		memory_index++;
		capture_count = capture_count < 10 ? capture_count + 1 : 0;
	}
	else {
		clear_screen();
		lcd_cursor(0, 0);
		print_string("Mem Full");
	}
	
	_delay_ms(30);
}

void training() {
	float input[NUM_INPUT_NEURONS];
	float desired_values[NUM_OUTPUT_NEURONS];
	MotorCommand motor_command;
	Input current_input;
	int i, ii;
	
	motor(LEFT, 0);
	motor(RIGHT, 0);
	clear_screen();
	
	_delay_ms(200);
	
	if (number_of_iterations == 0)
		number_of_iterations = get_training_iterations();
	
	for (i = 0; i < number_of_iterations; i++)  {
		clear_screen();
		lcd_cursor(0, 0);
		print_string("Training");
		lcd_cursor(2, 1);
		print_num(i);
		
		for (ii = 0; ii < memory_index; ii++) {
			//lcd_cursor(2, 1);
			//print_num(ii);
			current_input = memory[ii].input;
			input[0] = (float)(memory[ii].input.left) / 100.0;
			input[1] = (float)(memory[ii].input.right) / 100.0;
			set_inputs(neural_network, input);
	
			motor_command = compute_proportional(current_input.left, current_input.right);
	
			desired_values[0] = ((float)motor_command.left) / 100.0;
			desired_values[1] = ((float)motor_command.right) / 100.0;

			teach_network(neural_network, desired_values);
		}
	}
	
	
	clear_screen();
	print_string("Finished");
	
	_delay_ms(700);
	state = &neural;
}

void neural() {
	MotorCommand motor_command;
	Input input;
	
	clear_screen();
	print_string("Neural");
	
	input.left = (float)read_ir_sensor(LEFT) / 100.0;
	input.right = (float)read_ir_sensor(RIGHT) / 100.0;
	
	motor_command = compute_neural_network(input.left, input.right);
	motors(motor_command);
	
	lcd_cursor(0, 1);
	print_num(motor_command.left);
	lcd_cursor(5, 1);
	print_num(motor_command.right);
	
	_delay_ms(DELAY);
}

void learn_by_doing() {
   float input[NUM_INPUT_NEURONS];
   float desired_values[NUM_OUTPUT_NEURONS];
   MotorCommand motor_command;
   Input nInput;
   int i = 0, ii;


   while(1) {
	   while(!get_btn())  {
   		clear_screen();
   		print_string("Training");
			
	      nInput.left = read_ir_sensor(LEFT);
			nInput.right = read_ir_sensor(RIGHT);

	      input[0] = (float)nInput.left / 100.0;
	      input[1] = (float)nInput.right / 100.0;
	      set_inputs(neural_network, input);
	   
	      motor_command = compute_proportional(nInput.left, nInput.right);
	   	
	   	motors(motor_command);
	      desired_values[0] = ((float)motor_command.left) / 100.0;
	      desired_values[1] = ((float)motor_command.right) / 100.0;

	      lcd_cursor(2, 1);
	      print_num(i++);
	
			for (ii = 0; ii < 20; ii++)
	      	teach_network(neural_network, desired_values);
	
			_delay_ms(1);
	   }
		
		_delay_ms(400);
		
	   while(!get_btn()) {
		   clear_screen();
		   print_string("Network");
		
   		nInput.left = (float)read_ir_sensor(LEFT) / 100.0;
			nInput.right = (float)read_ir_sensor(RIGHT) / 100.0;
			
			motor_command = compute_neural_network(nInput.left, nInput.right);
			motors(motor_command);
	
			lcd_cursor(0, 1);
			print_num(motor_command.left);
			lcd_cursor(5, 1);
			print_num(motor_command.right);
			_delay_ms(DELAY);
	   }
		_delay_ms(400);
	}
}


MotorCommand compute_neural_network(uint8_t left, uint8_t right) {
	float input[NUM_INPUT_NEURONS];
	float outputs[NUM_OUTPUT_NEURONS];
	MotorCommand motor_command;
	
	input[0] = left;
	input[1] = right;
	set_inputs(neural_network, input);
	
	get_outputs(neural_network, outputs);
	
	motor_command.left = (uint8_t)(100 * outputs[0]);
	motor_command.right = (uint8_t)(100 * outputs[1]);
	
	return motor_command;
}

void destroy() {
	destroy_neural_network(neural_network);
	free(memory);
}

/* This is all the setup for the NeuralNetwork for lab4. Still need to make the
 * weights random though
 */
void create_lab4_neural_network() {
	neural_network = create_neural_network(NUM_NEURONS, NUM_INPUT_NEURONS, NUM_OUTPUT_NEURONS);
	
	srand(SEED);
	
	// Connect neuron 0 to other neurons
	connect_neurons(neural_network, 0, 2, random_float() * 8. / 2.);
	connect_neurons(neural_network, 0, 3, random_float() * 8. / 2.);
	connect_neurons(neural_network, 0, 4, random_float() * 8. / 2.);
	
	// Connect neuron 1 to other neurons
	connect_neurons(neural_network, 1, 2, random_float() * 8. / 2.);
	connect_neurons(neural_network, 1, 3, random_float() * 8. / 2.);
	connect_neurons(neural_network, 1, 4, random_float() * 8. / 2.);
	
	// Connect neuron 2 to other neurons
	connect_neurons(neural_network, 2, 5, random_float() * 8. / 3.);
	connect_neurons(neural_network, 2, 6, random_float() * 8. / 3.);
	
	// Connect neuron 3 to other neurons
	connect_neurons(neural_network, 3, 5, random_float() * 8. / 3.);
	connect_neurons(neural_network, 3, 6, random_float() * 8. / 3.);
	
	// Connect neuron 4 to other neurons
	connect_neurons(neural_network, 4, 5, random_float() * 8. / 3.);
	connect_neurons(neural_network, 4, 6, random_float() * 8. / 3.);
	
	// Set each neurons offset
	set_offset(neural_network, 2, 4);
	set_offset(neural_network, 3, 4);
	set_offset(neural_network, 4, 4);
	set_offset(neural_network, 5, 4);
	set_offset(neural_network, 6, 4);
	
	set_learning_rate(neural_network, LEARNING_RATE);
}

float random_float() {
	return (float)rand() / (float)RAND_MAX;
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

/* Here is a test of the network. 
 * Nodes 2 through 6 should output 1/2. The first two should output 1
 */
void neural_network_test() {
	int i;
	float input[NUM_INPUT_NEURONS];
	float desired_values[NUM_OUTPUT_NEURONS];
	
	create_lab4_neural_network();
	printf("Network created\n");
	
	for (i = 0; i < LEARNING_ITERATIONS; i++) {
		
		input[0] = 0;
		input[1] = 0;
		set_inputs(neural_network, input);
		
		desired_values[0] = 0;
		desired_values[1] = 0;

		teach_network(neural_network, desired_values);
		
		input[0] = 1;
		input[1] = 0;
		set_inputs(neural_network, input);
		
		desired_values[0] = 1;
		desired_values[1] = 0;

		teach_network(neural_network, desired_values);
		
		
		input[0] = 0;
		input[1] = 1;
		set_inputs(neural_network, input);
		
		desired_values[0] = 0;
		desired_values[1] = 1;

		teach_network(neural_network, desired_values);
	
		input[0] = 1;
		input[1] = 1;
		set_inputs(neural_network, input);
		
		desired_values[0] = 1;
		desired_values[1] = 1;
		
		teach_network(neural_network, desired_values);
	}

	printf("\nSmart Network\n");
		
	input[0] = 0;
	input[1] = 0;
	set_inputs(neural_network, input);
	
	for (i = 5; i < NUM_NEURONS; i++)
		printf("Output from node %d network (0, 0): %f\n", i, get_output(neural_network, i));
		
	input[0] = 0;
	input[1] = 1;
	set_inputs(neural_network, input);
	
	for (i = 5; i < NUM_NEURONS; i++)
		printf("Output from node %d network (0, 1): %f\n", i, get_output(neural_network, i));
		
	input[0] = 1;
	input[1] = 0;
	set_inputs(neural_network, input);
	
	for (i = 5; i < NUM_NEURONS; i++)
		printf("Output from node %d network (1, 0): %f\n", i, get_output(neural_network, i));
		
	input[0] = 1;
	input[1] = 1;
	set_inputs(neural_network, input);
	
	for (i = 5; i < NUM_NEURONS; i++)
		printf("Output from node %d network (1, 1): %f\n", i, get_output(neural_network, i));
	
	destroy_neural_network(neural_network);
	printf("Network destroyed\n");
}
