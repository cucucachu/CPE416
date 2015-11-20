#include "Map.h"

Map create_map(int num_blocks, float block_positions[]) {
	int i;
	Map map;
	
	map.blocks = calloc(num_blocks, sizeof(Block));
	
	for (i = 0; i < num_blocks; i++) {
		map.blocks[i].position = block_positions[i];
	}
	
	map.num_blocks = num_blocks;
	
	map.vader = vader;
	return map;
}

float vader_position(Map map) {
	return map.blocks[map.vader].position;
}
