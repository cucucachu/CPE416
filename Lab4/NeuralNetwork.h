#ifndef NEURALNETWORK
#define NEURALNETWORK

#include "Neuron.h"
#include <stdint.h>

typedef struct NeuralNetwork {
	Neuron **neurons;
	Neuron **input_neurons;
	Neuron **output_neurons;
	
	float alpha; // Learning rate
	float *desired_outputs;
	float *saved_outputs;
	
	uint8_t num_input_neurons;
	uint8_t num_output_neurons;
	uint8_t num_neurons;
} NeuralNetwork;

// Object Management
NeuralNetwork *create_neural_network(uint8_t num_neurons, uint8_t num_input_neurons, uint8_t num_output_neurons);
void destroy_neural_network(NeuralNetwork *this);

void connect_neurons(NeuralNetwork *this, uint8_t input, uint8_t output, float weight);
void set_offset(NeuralNetwork *this, uint8_t neuron, float offset);
void set_learning_rate(NeuralNetwork *this, float alpha);

void set_inputs(NeuralNetwork *this, float *inputs);

// Network Outputs
float get_output(NeuralNetwork *this, uint8_t neuron);
void get_outputs(NeuralNetwork *this, float *outputs);

// Learning Functions
void teach_network(NeuralNetwork *this, float *outputs);
void set_desired_output(NeuralNetwork *this, float *outputs);
void calculate_gradients(NeuralNetwork *this, float *gradients);

void save_outputs(NeuralNetwork *this);
float get_saved_output(NeuralNetwork *this, int id);
void backwards_prop(NeuralNetwork *this);

#endif
