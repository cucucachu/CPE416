#include "MonteCarlo.h"

void monte_carlo_init() {
	srand(SEED);
}

void monte_carlo(Map map, Particle *particles, int num, float range) {
	float probabilities[num];
	Particle new_particles[num];
	int i;
	
	for (i = 0; i < num; i++)
		probabilities[i] = probability(map, particles[i], range);
	
	for (i = 0; i < num; i++) 
		new_particles[i] = particles[roulette(probabilities, num)];
	
	
	for (i = 0; i < num; i++) 
		particles[i] = new_particles[i];
}

float gaussian_sample(float mean, float standard_deviation) {
	float x, y;
	
	x = (float)rand() / (float)RAND_MAX;
	y = (float)rand() / (float)RAND_MAX;
	return mean + (standard_deviation * (sqrt(-2 * log(x)) * cos(2 * M_PI * y)));
}

float probability(Map map, Particle particle, float range) {
	float probability;
	int near_block = 0;
	int i;
	float max_probability = 2 / (TRAP_D + TRAP_C - TRAP_B - TRAP_A);
	
	for (i = 0; i < map.num_blocks; i++) {
		if (map.blocks[i].position == 0) {
			if (particle.position > 360 - (.5 * BLOCK_WIDTH) && particle.position < 360
				|| particle.position < (.5 * BLOCK_WIDTH) && particle.position > 0) {
					near_block = 1;
					break;
				}
		}
		else if (particle.position > (map.blocks[i].position - (.5 * BLOCK_WIDTH))
			&& particle.position < (map.blocks[i].position + (.5 * BLOCK_WIDTH))) {
			near_block = 1;
			break;
		}
	}
	
	if (range < TRAP_A || range > TRAP_D) 
		probability = LOW_PROBABILITY;
	else if (range > TRAP_A && range < TRAP_B) 
		probability = max_probability * ((range - TRAP_A) / (TRAP_B - TRAP_A));
	else if (range > TRAP_C && range < TRAP_D) 
		probability = max_probability * ((TRAP_D - range) / (TRAP_D - TRAP_C));
	else 
		probability = max_probability;
	
	if (near_block == 0)
		probability = (max_probability + LOW_PROBABILITY) - probability;
	
	return probability;
}

int roulette(float probabilities[], int num) {
	int winner = 0;
	float sum = 0;
	float spinner;
	float bottom, top;
	int i;
	
	for (i = 0; i < num; i++)
		sum += probabilities[i];
		
	spinner = random_float() * sum;
	
	bottom = 0;
	for (i = 0; i < num; i++) {
		top = bottom + probabilities[i];
		if (spinner > bottom && spinner <= top) {
			winner = i;
			break;
		}
		bottom = top;
	}
	
	return winner;
}

float mean_position(Particle particles[], int num) {
	float sum = 0;
	int i;
	
	for (i = 0; i < num; i++)
		sum += particles[i].position;
	
	return sum / (float)num;
}

float standard_deviation(Particle particles[], int num) {
	float mean;
	int i;
	float sum = 0;
	
	mean = mean_position(particles, num);
	
	for (i = 0; i < num; i++)
		sum += (particles[i].position - mean) * (particles[i].position - mean);
	
	sum /= (float)num;
	
	return sqrt(sum);
}

float random_float() {
	return (float)rand() / (float)RAND_MAX;
}


