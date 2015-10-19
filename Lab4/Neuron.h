#ifndef NEURON
#define NEURON

#include <stdint.h>

#define MAX_INPUTS 10
#define MAX_OUTPUTS 10

typedef struct Neuron {
	float *weights;
	float offset;
	
	uint8_t number_of_inputs;
	uint8_t number_of_outputs;
	uint8_t set_inputs;
	uint8_t set_outputs;
	
	
	struct Neuron **input_neurons;
	struct Neuron **output_neurons;
	
	uint8_t this_is_an_input_neuron;
	float input;
} Neuron;

Neuron* create_neuron();
void destroy_neuron(Neuron *this);

void set_as_input_neuron(Neuron *this);
void set_static_input(Neuron *this, float input);

void set_neuron_weights(Neuron *this, float *weights, uint8_t number);
void set_neuron_offset(Neuron *this, float offset);

/*
void set_neuron_inputs(Neuron *this, Neuron **input_neurons, uint8_t number);
void set_neuron_outputs(Neuron *this, Neuron **output_nuerons, uint8_t number);
*/

void set_neuron_input(Neuron *this, Neuron *input, float weight);
void set_neuron_output(Neuron *this, Neuron *output);

float get_neuron_inputs(Neuron *this);
float get_neuron_output(Neuron *this);


void change_input_weight(Neuron *this, uint8_t input_index, float new_weight);
#endif
