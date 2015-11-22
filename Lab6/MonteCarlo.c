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
	
	
	for (i = 0; i < num - RANDOM_PARTICLES; i++) 
		particles[i] = new_particles[i];
	
	for (i = num - RANDOM_PARTICLES; i < num; i++)
		particles[i].position = 360. * random_float();
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
	float max_probability;
	
	for (i = 0; i < map.num_blocks; i++) {
		if (map.blocks[i].position == 0) {
			if ((particle.position >= 360 - (.5 * BLOCK_WIDTH) && particle.position < 360)
				|| (particle.position <= (.5 * BLOCK_WIDTH) && particle.position > 0)) {
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
	
	if (near_block == 1) {
		max_probability = 2 / (TRAP_D + TRAP_C - TRAP_B - TRAP_A);
		if (range < TRAP_A || range > TRAP_D) 
			probability = LOW_PROBABILITY;
		else if (range >= TRAP_A && range < TRAP_B) 
			probability = max_probability * ((range - TRAP_A) / (TRAP_B - TRAP_A));
		else if (range >= TRAP_C && range < TRAP_D) 
			probability = max_probability * ((TRAP_D - range) / (TRAP_D - TRAP_C));
		else 
			probability = max_probability;
	}
	else {
		max_probability = 1 / ( (32 - (TRAP_D - TRAP_A)) + (.5*(TRAP_B - TRAP_A)) + (.5 * (TRAP_D - TRAP_C )) );
		if (range < TRAP_A || range > TRAP_D) 
			probability = max_probability;
		else if (range >= TRAP_A && range < TRAP_B) 
			probability = max_probability * ((TRAP_B - range) / (TRAP_B - TRAP_A));
		else if (range >= TRAP_C && range < TRAP_D) 
			probability = max_probability * ((range - TRAP_C) / (TRAP_D - TRAP_C));
		else 
			probability = LOW_PROBABILITY;
	}
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
	float mean_angle;
	float radians;
	int i;
	float imaginary, real;
	
	imaginary = 0;
	real = 0;
	
	for (i = 0; i < num; i++) {
		radians = particles[i].position * (M_PI / 180.);
		imaginary += sin(radians);
		real += cos(radians);
	}
	
	imaginary /= num;
	real /= num;
	
	mean_angle = atan2(imaginary, real);
	
	return mean_angle * (180. / M_PI);
}

float standard_deviation(Particle particles[], int num) {
	float mean;
	int i;
	float sum = 0;
	float offset;
	float adjusted_position;
	
	mean = mean_position(particles, num);
	
	offset = 180 - mean;
	
	for (i = 0; i < num; i++) {
		adjusted_position = particles[i].position + offset;
		
		if (adjusted_position < 0)
			adjusted_position += 360;
		else if (adjusted_position > 360)
			adjusted_position -= 360;
			
		sum += (adjusted_position - 180) * (adjusted_position - 180);
	}
	
	sum /= (float)num;
	
	return sqrt(sum);
}

float random_float() {
	return (float)rand() / (float)RAND_MAX;
}


