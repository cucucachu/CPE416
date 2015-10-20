#include <stdlib.h>
#include <stdio.h>
#include "NeuralNetwork.h"

/*
typedef struct NeuralNetwork {
	Neuron **neurons;
	Neuron **input_neurons;
	Neuron **output_neurons;
	
	float alpha;
	float *desired_outputs;
	
	uint8_t num_input_neurons;
	uint8_t num_output_neurons;
	uint8_t num_neurons;
} NeuralNetwork;
*/

/*
 *	Object Management
 */
NeuralNetwork *create_neural_network(uint8_t num_neurons, uint8_t num_input_neurons, uint8_t num_output_neurons) {
	int i;
	NeuralNetwork *this;
	this = calloc(1, sizeof(NeuralNetwork));
	
	this->num_neurons = num_neurons;
	this->num_input_neurons = num_input_neurons;
	this->num_output_neurons = num_output_neurons;
	
	this->alpha = 0;
	
	this->neurons = calloc(num_neurons, sizeof(Neuron *));
	this->input_neurons = calloc(num_input_neurons, sizeof(Neuron *));
	this->output_neurons = calloc(num_output_neurons, sizeof(Neuron *));
	
	for (i = 0; i < num_neurons; i++) {
		this->neurons[i] = create_neuron(i);
		if (i < num_input_neurons)
			this->input_neurons[i] = this->neurons[i];
		else if (i >= num_neurons - num_output_neurons)
			this->output_neurons[i - (num_neurons - num_output_neurons)] = this->neurons[i];
	}
	
	// setup input neuron(s)
	for (i = 0; i < num_input_neurons; i++) {
		set_as_input_neuron(this->input_neurons[i]);
	}
	
	return this;
}

void destroy_neural_network(NeuralNetwork *this) {
	int i;
	
	if (this != NULL) {
		if (this->neurons != NULL) {
			for (i = 0; i < this->num_neurons; i++)
				if (this->neurons[i] != NULL)
					destroy_neuron(this->neurons[i]);
				
			free(this->neurons);
		}
		
		if (this->input_neurons != NULL)
			free(this->input_neurons);
			
		if (this->output_neurons != NULL)
			free(this->output_neurons);
		
		free(this);
	}
}

void connect_neurons(NeuralNetwork *this, uint8_t input, uint8_t output, float weight) {
	set_neuron_input(this->neurons[output], this->neurons[input], weight);
	set_neuron_output(this->neurons[input], this->neurons[output]);
}

void set_offset(NeuralNetwork *this, uint8_t neuron, float offset) {
	set_neuron_offset(this->neurons[neuron], offset);
}


void set_learning_rate(NeuralNetwork *this, float alpha) {
	this->alpha = alpha;
}

void set_inputs(NeuralNetwork *this, float *inputs) {
	int i;
	
	for (i = 0; i < this->num_input_neurons; i++)
		set_static_input(this->input_neurons[i], inputs[i]);
};

/*
 *	Network Output
 */

float get_output(NeuralNetwork *this, uint8_t neuron) {
	return get_neuron_output(this->neurons[neuron]);
}

void get_outputs(NeuralNetwork *this, float *outputs) {
	int i;
	
	for (i = 0; i < this->num_output_neurons; i++)
		outputs[i] = get_neuron_output(this->output_neurons[i]);
}

/*
 *	Learning Functions
 */

void teach_network(NeuralNetwork *this, float *outputs) {
	set_desired_output(this, outputs);
	backwards_prop(this);
}

void set_desired_output(NeuralNetwork *this, float *outputs) {
	this->desired_outputs = outputs;
}

void calculate_gradients(NeuralNetwork *this, float *gradients) {
	uint8_t i, ii;
	uint8_t neuron_index;
	uint8_t output_neuron_index;
	uint8_t num_hidden_neurons;
	Neuron *neuron;
	Neuron *output_neuron;
	float neuron_output;
	float output_neuron_output;
	float weight;
	float sum;
	
	num_hidden_neurons = this->num_neurons - this->num_input_neurons - this->num_output_neurons;
	//printf("HERE");
	// compute gradients for the output neurons
	
	for (i = 0; i < this->num_output_neurons; i++) {
		neuron_index = this->num_neurons - (i + 1);
		neuron = this->neurons[neuron_index];
		neuron_output = get_output(this, neuron_index);
		
		gradients[i] = neuron_output * (1 - neuron_output) 
			* (this->desired_outputs[this->num_output_neurons - (i + 1)]);
		//printf("gradients[i] = %lf\n", gradients[i]);
	}
	
	for (; i < this->num_output_neurons + num_hidden_neurons; i++) {
		sum = 0;
		
		neuron_index = this->num_neurons - (i + 1);
		neuron = this->neurons[neuron_index];
		neuron_output = get_output(this, neuron_index);
		
		for (ii = 0; ii < neuron->number_of_outputs; ii++) {
			output_neuron_index = this->num_neurons - (ii + 1);
			output_neuron = this->neurons[output_neuron_index];
			output_neuron_output = get_output(this, output_neuron_index);
			
			weight = get_weight_for_input_neuron(neuron, output_neuron);
			sum += weight * gradients[this->num_neurons - (output_neuron_index + 1)];
		}
		
		gradients[i] = neuron_output * (1 - neuron_output) * sum;
		//printf("gradients[i] = %lf\n", gradients[i]);
	}
}

void backwards_prop(NeuralNetwork *this) {
	uint8_t neuron_index;
	uint8_t num_hidden_neurons;
	Neuron *neuron;
	float *gradients;
	int i;
	
	num_hidden_neurons = this->num_neurons - this->num_input_neurons - this->num_output_neurons;
	
	gradients = calloc(num_hidden_neurons, sizeof(float));
	calculate_gradients(this, gradients);
	
	for (i = 0; i < this->num_output_neurons + num_hidden_neurons; i++) {
		neuron_index = this->num_neurons - (i + 1);
		neuron = this->neurons[neuron_index];
		
		teach_neuron(neuron, this->alpha, gradients[i]);
	}
	
	free(gradients);
}
