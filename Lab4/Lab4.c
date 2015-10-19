#include <stdio.h>
#include <stdlib.h>

#include "Neuron.h"
#include "NeuralNetwork.h"

#define NUM_NEURONS 7
#define NUM_INPUT_NEURONS 2
#define NUM_OUTPUT_NEURONS 2
#define LEARNING_RATE .001

void create_lab4_neural_network();
void neural_network_test();

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
	neural_network = create_neural_network(NUM_NEURONS, NUM_INPUT_NEURONS, NUM_OUTPUT_NEURONS);
	
	// Connect neuron 0 to other neurons
	connect_neurons(neural_network, 0, 2, 1);
	connect_neurons(neural_network, 0, 3, 1);
	connect_neurons(neural_network, 0, 4, 1);
	
	// Connect neuron 1 to other neurons
	connect_neurons(neural_network, 1, 2, 1);
	connect_neurons(neural_network, 1, 3, 1);
	connect_neurons(neural_network, 1, 4, 1);
	
	// Connect neuron 2 to other neurons
	connect_neurons(neural_network, 2, 5, 2);
	connect_neurons(neural_network, 2, 6, 2);
	
	// Connect neuron 3 to other neurons
	connect_neurons(neural_network, 3, 5, 2);
	connect_neurons(neural_network, 3, 6, 2);
	
	// Connect neuron 4 to other neurons
	connect_neurons(neural_network, 4, 5, 2);
	connect_neurons(neural_network, 4, 6, 2);
	
	// Set each neurons offset
	set_offset(neural_network, 2, 2);
	set_offset(neural_network, 3, 2);
	set_offset(neural_network, 4, 2);
	set_offset(neural_network, 5, 3);
	set_offset(neural_network, 6, 3);
	
	set_learning_rate(neural_network, LEARNING_RATE);
}

/* Here is a test of the network. 
 * Nodes 2 through 6 should output 1/2. The first two should output 1
 */
void neural_network_test() {
	int i;
	float input[NUM_INPUT_NEURONS];	
	
	input[0] = 1;
	input[1] = 1;
	set_inputs(neural_network, input);
	
	for (i = 0; i < NUM_NEURONS; i++)
		printf("Output from node %d network: %f\n", i, get_output(neural_network, i));
	
}
