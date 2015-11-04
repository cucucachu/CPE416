/* Cody Jones and Gabriel Hernandez
 * Neuron
 * Description: 
 * Struct for a neuron and functions to set parameters and
 *  get neuron output.
 **/
 
#ifndef NEURON
#define NEURON

#include <stdint.h>

#define MAX_INPUTS 10
#define MAX_OUTPUTS 10

typedef struct Neuron {
	uint8_t id;
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

Neuron* create_neuron(uint8_t id);
void destroy_neuron(Neuron *this);

void set_as_input_neuron(Neuron *this);
void set_static_input(Neuron *this, float input);

void set_neuron_offset(Neuron *this, float offset);

uint8_t equals(Neuron *this, Neuron *other);

float get_weight_for_input_neuron(Neuron *this, Neuron *other);

void set_neuron_input(Neuron *this, Neuron *input, float weight);
void set_neuron_output(Neuron *this, Neuron *output);

float get_neuron_inputs(Neuron *this);
float get_neuron_output(Neuron *this);

void teach_neuron(Neuron *this, float alpha, float gradient);
#endif
