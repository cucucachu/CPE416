#ifndef MEMORY
#define MEMORY

#define MEMORY_SIZE 1000

typedef struct Input {
	uint8_t left;
	uint8_t right;
} Input;

typedef struct IO_Pair {
	Input input;
	MotorCommand motor_command;
} IO_Pair;

typedef IO_Pair *Memory;
#endif
