/* Cody Jones and Gabriel Hernandez
 * Neuron
 * Description: 
 * Struct for a neuron and functions to set parameters and
 *  get neuron output.
 **/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <util/delay.h>
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "globals.h"

/*
typedef struct Neuron {
	uint8_t id;
	float *weights;
	float offset;
	
	uint8_t number_of_inputs;
	uint8_t number_of_outputs;
	uint8_t set_inputs;
	uint8_t set_outputs;
	
	Neuron **input_neurons;
	Neuron **output_neurons;
	
	uint8_t this_is_an_input_neuron;
	float input;
} Neuron;
*/

Neuron *create_neuron(uint8_t id) {
	Neuron *this;
	this = calloc(1, sizeof(Neuron));
	
	this->id = id;
	this->weights = NULL;
	this->offset = 0;
	
	this->number_of_inputs = 0;
	this->number_of_outputs = 0;
	this->set_inputs = 0;
	this->set_outputs = 0;
	
	this->input_neurons = NULL;
	this->output_neurons = NULL;

	this->this_is_an_input_neuron = 0;
	this->input = 0;

	return this;
}

void destroy_neuron(Neuron *this) {
	if (this->weights != NULL)
		free(this->weights);
	if (this->input_neurons != NULL)
		free(this->input_neurons);
	if (this->output_neurons != NULL)
		free(this->output_neurons);
}


void set_as_input_neuron(Neuron *this) {
	this->this_is_an_input_neuron = 1;
}

void set_static_input(Neuron *this, float input) {
	this->input = input;
}

void set_neuron_input(Neuron *this, Neuron *input_neuron, float weight) {
	
	if (this->weights == NULL)
		this->weights = calloc(MAX_INPUTS, sizeof(float));
	
	if (this->input_neurons == NULL)
		this->input_neurons = calloc(MAX_INPUTS, sizeof(Neuron *));
	
	if (this->number_of_inputs < MAX_INPUTS) {
		this->input_neurons[this->number_of_inputs] = input_neuron;
		this->weights[this->number_of_inputs] = weight;
		this->number_of_inputs++;
	}
	else
		fprintf(stderr, "You have exceeded the maximum number of inputs on this neuron.\n");
}

void set_neuron_output(Neuron *this, Neuron *output_neuron) {
	
	if (this->output_neurons == NULL)
		this->output_neurons = calloc(MAX_OUTPUTS, sizeof(Neuron *));
	
	if (this->number_of_outputs < MAX_INPUTS)
		this->output_neurons[this->number_of_outputs++] = output_neuron;
	else
		fprintf(stderr, "You have exceeded the maximum number of outputs on this neuron.\n");
}

void set_neuron_offset(Neuron *this, float offset) {
	this->offset = offset;
}

uint8_t neuron_equals(Neuron *this, Neuron *other) {
	if (this->id == other->id)
		return 1;
	return 0;
}

float get_weight_for_input_neuron(Neuron *this, Neuron *other) {
	uint8_t input_neuron_index;
	int i;
	
	input_neuron_index = -1;
	
	for (i = 0; i < this->number_of_inputs; i++)
		if (neuron_equals(this->input_neurons[i], other))
			input_neuron_index = i;
	
	if (input_neuron_index == -1) {
		print_string("error");//printf("Error in get_weight_for_input_neuron this %d other %d\n", this->id, other->id);
		while(1);
	}
	
	return this->weights[i];
}

float get_inputs(Neuron *this) {
	int i;
	float weighted_sum;
	
	weighted_sum = 0;
	
	if (this->this_is_an_input_neuron)
		weighted_sum = this->input;
	else 
		for (i = 0; i < this->number_of_inputs; i++) 
			weighted_sum += this->weights[i] * get_neuron_output(this->input_neurons[i]);
	
	return weighted_sum;
}

float get_neuron_output(Neuron *this) {
	float weighted_sum;
	
	weighted_sum = get_inputs(this);
	
	if (this->this_is_an_input_neuron)
		return weighted_sum;
	
	return 1.0 / (1 + exp(-1 * (weighted_sum - this->offset)));
}

void teach_neuron(Neuron *this, float alpha, float gradient) {
	int i;
	
	for (i = 0; i < this->number_of_inputs; i++)
		this->weights[i] += alpha * get_neuron_output(this->input_neurons[i]) * gradient;
}
