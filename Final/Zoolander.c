#include "globals.h"
#include "Motors.h"
#include "IRSensors.h"

#define HALF_WAY_DISTANCE 125
#define FULL_CIRCLE 100
#define NINETY_DEGREES 29

void go_to_center();
void find_target();
void attack();
void straighten_out();

void (*state)() = &go_to_center; 

int main() {
	while (1) {
		state();
	}
}

void go_to_center() {
	if (left_count == 0)
		motor_backward();
	else if (left_count >= HALF_WAY_DISTANCE) {
		state = &find_target();
		motor_stop();
		left_count = 0;
	}
}

void find_target() {
	
}

void attack() {

}

void check_for_border() {
	
}

void turn_around() {

}

