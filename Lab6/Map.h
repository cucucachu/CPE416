#ifndef MAP
#define MAP

#include <stdlib.h>

#define MAX_POSITION 360
#define BLOCK_WIDTH 15

typedef struct Block {
	float position;
} Block;

typedef struct Particle {
	float position;
} Particle;

typedef struct Map {
	Block *blocks;
	int num_blocks;	
} Map;

Map create_map(int num_blocks, float block_positions[]);
#endif
