#include <stdio.h>
#include <stdlib.h>

#include "Neuron.h"
#include "NeuralNetwork.h"

#define NUM_NEURONS 7
#define NUM_INPUT_NEURONS 2
#define NUM_OUTPUT_NEURONS 2
#define LEARNING_RATE .02
#define LEARNING_ITERATIONS 100000
#define SEED 111

void create_lab4_neural_network();
void neural_network_test();
float random_float();

NeuralNetwork *neural_network;

void main() {
	create_lab4_neural_network();
	printf("Network created\n");
	
	neural_network_test();
	
	destroy_neural_network(neural_network);
	printf("Network destroyed\n");
}

/* This is all the setup for the NeuralNetwork for lab4. Still need to make the
 * weights random though
 */
void create_lab4_neural_network() {
	float temp;
	neural_network = create_neural_network(NUM_NEURONS, NUM_INPUT_NEURONS, NUM_OUTPUT_NEURONS);
	
	srand(SEED);
	
	// Connect neuron 0 to other neurons
	connect_neurons(neural_network, 0, 2, random_float() * 8 / 2);
	connect_neurons(neural_network, 0, 3, random_float() * 8 / 2);
	connect_neurons(neural_network, 0, 4, random_float() * 8 / 2);
	
	// Connect neuron 1 to other neurons
	connect_neurons(neural_network, 1, 2, random_float() * 8 / 2);
	connect_neurons(neural_network, 1, 3, random_float() * 8 / 2);
	connect_neurons(neural_network, 1, 4, random_float() * 8 / 2);
	
	// Connect neuron 2 to other neurons
	connect_neurons(neural_network, 2, 5, random_float() * 8 / 3);
	connect_neurons(neural_network, 2, 6, random_float() * 8 / 3);
	
	// Connect neuron 3 to other neurons
	connect_neurons(neural_network, 3, 5, random_float() * 8 / 3);
	connect_neurons(neural_network, 3, 6, random_float() * 8 / 3);
	
	// Connect neuron 4 to other neurons
	connect_neurons(neural_network, 4, 5, random_float() * 8 / 3);
	connect_neurons(neural_network, 4, 6, random_float() * 8 / 3);
	
	// Set each neurons offset
	set_offset(neural_network, 2, 4);
	set_offset(neural_network, 3, 4);
	set_offset(neural_network, 4, 4);
	set_offset(neural_network, 5, 4);
	set_offset(neural_network, 6, 4);
	
	set_learning_rate(neural_network, LEARNING_RATE);
}

/* Here is a test of the network. 
 * Nodes 2 through 6 should output 1/2. The first two should output 1
 */
void neural_network_test() {
	int i;
	float input[NUM_INPUT_NEURONS];
	float desired_values[NUM_OUTPUT_NEURONS];
	
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
		
}

float random_float() {
	return (float)rand() / (float)RAND_MAX;
}
