#include "BlockSensor.h"

void block_sensor_init() {
   init_adc();
}

u08 read_block_sensor() {   

   return analog(BLOCK_PIN);
}