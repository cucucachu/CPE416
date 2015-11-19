#ifndef MONTE_CARLO
#define MONTE_CARLO
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Map.h"


#define SEED 1

#define TRAPEZOID_WIDTH 2

#define LOW_PROBABILITY .1
#define HIGH_PROBABILITY .98

void monte_carlo_init();

float guassian_sample(float mean, float standard_deviation);

float probability_at_block(Map map, Particle particle);
#endif
