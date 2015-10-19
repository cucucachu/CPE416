/* Cody Jones and Gabriel Hernandez
 * Lab 3 
 * Description: 
 * Line following robot. Press button twice to start.
 **/

#include "globals.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define RIGHT_SERVO     0  //Right motor when looking at screen. Goes backwards at 255
#define LEFT_SERVO      1  //Left motor when looking at screen. Goes forwards at 255
#define MAXSPEEDRANGE   27.0
#define FULL_SPEED 50

#define WEIGHT 1
#define DECAY 1
#define SUM_MAX 2500
#define PRESENT_COEFFICIENT 1
#define DELTA_COEFFICIENT .5
#define SUM_COEFFICIENT .04
#define PROPORTION .5

#define SENSOR_CALIBRATION .39
#define BLACK 77
#define WHITE 7

#define DELAY 3 // 3 for best cornering, 5 for best smoothness

#define LEFT 0
#define RIGHT 1

void setup();
void wait();
void delay(uint16_t ms);
void decay(float array[], int size);

void motor(uint8_t num, int8_t speed);
void motor_test();

u08 eye(u08 which_eye);
void eye_exam();
void follow_line();

float left_speed;
float right_speed;

int main(void) {
	setup();
	
	wait();
	eye_exam();
	follow_line();
   return 0;
}

void follow_line() {
	float error;
	float previous, present, delta, sum;
	float new_left_speed;
	float new_right_speed;
	int index;
	int count;
	
	
	new_left_speed = FULL_SPEED;
	new_right_speed = FULL_SPEED;
	present = 0;
	previous = 0;
	delta = 0;
	sum = 0;
	error = 0;
	
	count = 0;
	
	index = 0;
	
	while(1) {
		
		present = WEIGHT * (eye(RIGHT) - eye(LEFT));
		delta = present - previous;
		sum += present;
		
		sum = sum < -SUM_MAX ? -SUM_MAX : sum;
		sum = sum > SUM_MAX ? SUM_MAX : sum;
		
		error = PRESENT_COEFFICIENT * present + DELTA_COEFFICIENT * delta + SUM_COEFFICIENT * sum;
		error *= PROPORTION;
		
		if (error < 1 && error > -1)
			error = 0;
		
		if (error > 0) {
			new_left_speed = FULL_SPEED;
			new_right_speed = FULL_SPEED - error;
			new_right_speed = new_right_speed > 0 ? new_right_speed : 0;
		}
		else if (error < 0) {
			new_right_speed = FULL_SPEED;
			new_left_speed = FULL_SPEED + error;
			new_left_speed = new_left_speed > 0 ? new_left_speed : 0;
		}
		else {
			new_right_speed = FULL_SPEED;
			new_left_speed = FULL_SPEED;
		}
		
		
		if (!(count % 16)) {
			clear_screen();
			lcd_cursor(0, 0);
			//print_num((int)(present));
			//lcd_cursor(4, 0);
			//print_num((int)(delta));
			//lcd_cursor(0, 1);
			//print_num((int)(sum));
			//lcd_cursor(4, 1);
			print_num((int)(error));
		}
		
		
		motor(LEFT, new_left_speed);
		motor(RIGHT, new_right_speed);
		_delay_ms(DELAY);
		
		sum *= DECAY;
		previous = present;		
		count++;
		index++;
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

void setup() {
   init();
	init_lcd();
	init_adc();
	
	motor(0, 0);
	motor(1, 0);
	left_speed = 0;
	right_speed = 0;
	
	int i;
}

void delay(uint16_t ms) {
   while(ms--)
      _delay_ms(1);
}

void motor(uint8_t num, int8_t speed) {
	
   if(num == RIGHT_SERVO)
      speed = speed/100.0 * MAXSPEEDRANGE + 127;
   else {
      speed = -1*speed/100.0 * MAXSPEEDRANGE + 127;
   }
   set_servo(num, speed);
}

u08 eye(u08 which_eye) {
   int light = analog(which_eye);
	
	light = (float)light * SENSOR_CALIBRATION;
	
	light = light >= BLACK ? 100 : light;
	light = light <= WHITE ? 0 : light;

	return light;
}