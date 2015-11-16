#ifndef WHEEL_FOLLOWING
#define WHEEL_FOLLOWING

#define FULL_SPEED 60
#define NINETY_DEGREES 29
#define SIDE_LENGTH 2.8
#define DIAGONAL_LENGTH 3

void move_forward(float rotations);
void turn_left();
void turn_right();
void turn_quarter_left();
void turn_quarter_right();

#endif