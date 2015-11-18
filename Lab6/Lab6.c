#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "BlockSensor.h"

void wait();
void init();

void all_init() {
	init();
	ir_init();
	init_lcd();
   ws_init();
	motor_init();
	wait();
	
}

int main() {
	all_init();	
	while(1) {
      print_num(read_block_sensor);
      _delay_ms(100);
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
