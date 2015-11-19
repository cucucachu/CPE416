#include "MonteCarlo.h"

void monte_carlo_init() {
	srand(SEED);
}

float guassian_sample(float mean, float standard_deviation) {
	float x, y;
	
	x = (float)rand() / (float)RAND_MAX;
	y = (float)rand() / (float)RAND_MAX;
	return mean + (standard_deviation * (sqrt(-2 * log(x)) * cos(2 * M_PI * y)));
}

float probability_at_block(Map map, Particle particle) {
	float probability;
	float a, b, c, d;
	int near_block = 0;
	int nearest_block = 0;
	int i;
	
	for (i = 0; i < map.num_blocks; i++) {
		if (particle.position > (map.blocks[i].position - (.5 * BLOCK_WIDTH) - (TRAPEZOID_WIDTH))
			&& particle.position < (map.blocks[i].position + (.5 * BLOCK_WIDTH) + (TRAPEZOID_WIDTH))) {
			near_block = 1;
			nearest_block = 1;
			break;
		}
	}
	
	if (near_block) {
		b = map.blocks[nearest_block].position - (.5 * BLOCK_WIDTH);
		a = b - TRAPEZOID_WIDTH;
		c = map.blocks[nearest_block].position + (.5 * BLOCK_WIDTH);
		d = c + TRAPEZOID_WIDTH;
	
		if (particle.position < b) {
			probability = HIGH_PROBABILITY * ((particle.position - a) / TRAPEZOID_WIDTH);
		}
		else if (particle.position > c) {
			probability = HIGH_PROBABILITY * ((d - particle.position) / TRAPEZOID_WIDTH);
		}
		else {
			probability = HIGH_PROBABILITY;
		}
	}
	else {
		probability = LOW_PROBABILITY;
	}
	
	return probability;
}

float probability_not_at_block(Map map, Particle particle) {
	float probability;
	float a, b, c, d;
	int near_block = 0;
	int nearest_block = 0;
	int i;
	
	for (i = 0; i < map.num_blocks; i++) {
		if (particle.position > (map.blocks[i].position - (.5 * BLOCK_WIDTH) - (TRAPEZOID_WIDTH))
			&& particle.position < (map.blocks[i].position + (.5 * BLOCK_WIDTH) + (TRAPEZOID_WIDTH))) {
			near_block = 1;
			nearest_block = 1;
			break;
		}
	}
	
	if (near_block) {
		b = map.blocks[nearest_block].position - (.5 * BLOCK_WIDTH);
		a = b - TRAPEZOID_WIDTH;
		c = map.blocks[nearest_block].position + (.5 * BLOCK_WIDTH);
		d = c + TRAPEZOID_WIDTH;
	
		if (particle.position < b) {
			probability = HIGH_PROBABILITY * ((particle.position - a) / TRAPEZOID_WIDTH);
		}
		else if (particle.position > c) {
			probability = HIGH_PROBABILITY * ((d - particle.position) / TRAPEZOID_WIDTH);
		}
		else {
			probability = HIGH_PROBABILITY;
		}
	}
	else {
		probability = LOW_PROBABILITY;
	}
	
	return probability;
}
