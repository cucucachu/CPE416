#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"
#include "IRSensors.h"
#include "LineFollowing.h"
#include "MonteCarlo.h"
#include "globals.h"

void wait();

void all_init() {
	init();
	monte_carlo_init();
	ir_init();
	init_lcd();
	motor_init();
	wait();
	
}

int main() {
	all_init();	
	while(1) {
		_delay_ms(400);
		clear_screen();
		print_num((int)(guassian_sample(50, 25)));
	}
}


void wait() {
	lcd_cursor(1, 0);
	print_string("Listo");
	
	while (!get_btn());
	
	clear_screen();
	lcd_cursor(3, 0);
	print_string("Go");
	_delay_ms(200);
}
