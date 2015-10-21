#include "IRSensors.h"

void ir_init() {
	init_lcd();
	init_adc();
}

u08 read_ir_sensor(u08 which_eye) {
   int light = analog(which_eye);
	
	light = (float)light * SENSOR_CALIBRATION;
	
	light = light >= BLACK ? 100 : light;
	light = light <= WHITE ? 0 : light;

	return light;
}

void eye_exam() { 
	while (!get_btn()) {
		u08 light;
		light = eye(LEFT);
		clear_screen();
		print_num(light);
		
		light = eye(RIGHT);
		lcd_cursor(6, 0);
		print_num(light);
		delay(100);
	}
}


