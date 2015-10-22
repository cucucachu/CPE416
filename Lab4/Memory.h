/* Cody Jones and Gabriel Hernandez
 * Memory
 * Description: 
 * Holds input output pairs which coorespond to results from the
 *  line following algorithm. Neural Network can learn from this.
 **/
 
 #ifndef MEMORY
#define MEMORY

#include <stdint.h>

#define MEMORY_SIZE 500

typedef struct Input {
	uint8_t left;
	uint8_t right;
} Input;

typedef struct IO_Pair {
	Input input;
	MotorCommand motor_command;
} IO_Pair, *Memory;

//typedef IO_Pair *Memory;
#endif
