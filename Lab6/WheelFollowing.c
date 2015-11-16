#include "WheelFollowing.h"

void move_forward(float rotations) {
   int left_end;
   int right_end;
   
   left_count = 0;
   right_count = 0;
   
   left_end = rotations * FULL_CIRCLE;
   right_end = rotations * FULL_CIRCLE;
   
   motor(LEFT_MOTOR, FULL_SPEED);
   motor(RIGHT_MOTOR, FULL_SPEED);
   
   while(left_count < left_end || right_count < right_end);
   
   
   motor(LEFT_MOTOR, 0);
   motor(RIGHT_MOTOR, 0);
}

void turn_left() {
   int left_end;
   int right_end;
   
   left_count = 0;
   right_count = 0;
   
   left_end = NINETY_DEGREES;
   right_end = NINETY_DEGREES;
   
   motor(LEFT_MOTOR, -FULL_SPEED);
   motor(RIGHT_MOTOR, FULL_SPEED);
   
   while(left_count < left_end || right_count < right_end);
   
   
   motor(LEFT_MOTOR, 0);
   motor(RIGHT_MOTOR, 0);
   
}

void turn_right() {
   int left_end;
   int right_end;
   
   left_count = 0;
   right_count = 0;
   
   left_end = NINETY_DEGREES;
   right_end = NINETY_DEGREES;
   
   motor(LEFT_MOTOR, FULL_SPEED);
   motor(RIGHT_MOTOR, -FULL_SPEED);
   
   while(left_count < left_end || right_count < right_end);
   
   
   motor(LEFT_MOTOR, 0);
   motor(RIGHT_MOTOR, 0);
   
}

void turn_quarter_left() {
   int left_end;
   int right_end;
   
   left_count = 0;
   right_count = 0;
   
   left_end = (float)NINETY_DEGREES / 2.;
   right_end = (float)NINETY_DEGREES / 2.;
   
   motor(LEFT_MOTOR, -FULL_SPEED);
   motor(RIGHT_MOTOR, FULL_SPEED);
   
   while(left_count < left_end || right_count < right_end);
   
   
   motor(LEFT_MOTOR, 0);
   motor(RIGHT_MOTOR, 0);
   
}

void turn_quarter_right() {
   int left_end;
   int right_end;
   
   left_count = 0;
   right_count = 0;
   
   left_end = (float)NINETY_DEGREES / 2.;
   right_end = (float)NINETY_DEGREES / 2.;
   
   motor(LEFT_MOTOR, FULL_SPEED);
   motor(RIGHT_MOTOR, -FULL_SPEED);
   
   while(left_count < left_end || right_count < right_end);
   
   
   motor(LEFT_MOTOR, 0);
   motor(RIGHT_MOTOR, 0);
   
}
