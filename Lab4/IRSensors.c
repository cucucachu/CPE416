#include "IRSensors.h"

void ir_init() {
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
		light = read_ir_sensor(LEFT);
		clear_screen();
		print_num(light);
		
		light = read_ir_sensor(RIGHT);
		lcd_cursor(6, 0);
		print_num(light);
		_delay_ms(100);
	}
}


