#ifndef MONTE_CARLO
#define MONTE_CARLO
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "Map.h"


#define SEED 1

#define TRAP_A 9.
#define TRAP_B 11.
#define TRAP_C 18.
#define TRAP_D 20.

#define RANDOM_PARTICLES 0

#define LOW_PROBABILITY .00
#define HIGH_PROBABILITY .98

void monte_carlo_init();

void monte_carlo(Map map, Particle *particles, int num, float range);

float gaussian_sample(float mean, float standard_deviation);

float probability(Map map, Particle particle, float range);

int roulette(float probabilities[], int num);

float mean_position(Particle particles[], int num);

float standard_deviation(Particle particles[], int num);

float random_float();

#endif
