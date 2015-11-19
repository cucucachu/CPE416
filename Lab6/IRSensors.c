#include "IRSensors.h"


void ir_init() {
	init_encoder();
	left_count = right_count = 0;
	init_adc();
}

// Wheel Encoder
void init_encoder() {
    // enable encoder interrupts
    EIMSK = 0;
    EIMSK |= _BV(PCIE1) | _BV(PCIE0);
    PCMSK1 |= _BV(PCINT13); //PB5 - digital 5
    PCMSK0 |= _BV(PCINT6);  //PE6 - digital 4
    // enable pullups
    PORTE |= _BV(PE6);
    PORTB |= _BV(PB5);
}

ISR(PCINT0_vect) {
   left_count++;  //increment left encoder
}

ISR(PCINT1_vect) {
   right_count++;  //increment right encoder
}

// Line Sensors
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

// Range Finder
uint8_t get_range() {
	return (int)((185 - analog(RANGE_FINDER_PIN)) * RANGE_TO_CENTIMETERS);
}


