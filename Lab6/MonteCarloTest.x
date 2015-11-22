#include <stdio.h>

#include "MonteCarlo.h"
#include "Map.h"

#define NUM_BLOCKS 2
#define BLOCK_POS_1 90.
#define BLOCK_POS_2 180.
#define VADER 1

#define ALL_THE_WAY 275.
#define NUM_PARTICLES 200
#define NINETY_DEGREES 29

#define POSITION_PROBABILITY_THRESHOLD (BLOCK_WIDTH / 2.)
#define TRAVEL_DISTANCE 5
#define TICKS_PER_DEGREE (ALL_THE_WAY / 360.)
#define MOTION_NOISE .2

float robot_position;

int compare_particles(const void *a, const void *b);

void psuedo_carlo(Map map, Particle *particles) {
	float probabilities[NUM_PARTICLES];
	Particle new_particles[NUM_PARTICLES];
	int i;
	
	for (i = 0; i < NUM_PARTICLES; i++) {
		probabilities[i] = (float)i / (float)NUM_PARTICLES;
	}
	
	for (i = 0; i < NUM_PARTICLES; i++) 
		new_particles[i] = particles[roulette(probabilities, NUM_PARTICLES)];
	
	for (i = 0; i < NUM_PARTICLES; i++) 
		particles[i] = new_particles[i];

}

void move_particles(Particle particles[]) {
	int i;
	
	for (i = 0; i < NUM_PARTICLES; i++) {
		particles[i].position += gaussian_sample(TRAVEL_DISTANCE, MOTION_NOISE);
		if (particles[i].position > 360)
			particles[i].position -= 360;
	}
}

float find_location(Map map, Particle particles[]) {
	float readings[72] = {
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 15, 15, 15, 
		15, 15, 30,	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 15, 15, 15, 
		15, 15, 30, 30, 30, 30,	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30
		};
	int i = 0, ii;
	int *histogram = calloc(360, sizeof(int));
	
	robot_position = 0;
	
	while (standard_deviation(particles, NUM_PARTICLES) > POSITION_PROBABILITY_THRESHOLD) {
		
		move_particles(particles);
		robot_position += TRAVEL_DISTANCE;
	
		if (robot_position > 360)
			robot_position -= 360;
	
		monte_carlo(map, particles, NUM_PARTICLES, readings[i % 24]);
		
		qsort(particles, NUM_PARTICLES, sizeof(Particle), compare_particles);
		if (i == 1 || i == 10) {
			printf("at time %d:\n", i);
			
			for (ii = 0; ii < NUM_PARTICLES; ii++) {
				histogram[(int)particles[ii].position]++;
			}
			
			for (ii = 0; ii < 360; ii++) {
				printf("%d, %d\n", ii, histogram[ii]);
			}
		}
		printf("at time %d std deviation: %.2f\n", i, standard_deviation(particles, NUM_PARTICLES));
		i++;
	}
	
	printf("Location %.2f in %d turns\n", mean_position(particles, NUM_PARTICLES), i);
	printf("Actual location %d\n", (int)robot_position);
	free(histogram);
	return mean_position(particles, NUM_PARTICLES);
}

int main() {
	int i;	
	monte_carlo_init();
	Map map;
	Particle particles[NUM_PARTICLES];
	float block_positions[NUM_BLOCKS];
	
	block_positions[0] = BLOCK_POS_1;
	block_positions[1] = BLOCK_POS_2;
	
	map = create_map(2, block_positions, 0);
	
	for (i = 0; i < NUM_PARTICLES; i++) {
		particles[i].position = (random_float()) * 360;
	}
	
	find_location(map, particles);

	return 0;
}

int compare_particles(const void *a, const void *b) {
	return ((Particle *)a)->position - ((Particle *)b)->position;
}
