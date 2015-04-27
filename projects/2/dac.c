#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

const int MAX_POINTS = 40;

int squarewave[] = {
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0xFFF, 0xFFF,
   0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF,
   0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF
};

int sawtooth[] = {
   0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400,
   1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700,
   2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900
};

const int DUTY_CYCLE_LIMITS[] = {
   0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40
};

void SetDutyCycle(int duty_cycle) {
   int zero_points = MAX_POINTS - DUTY_CYCLE_LIMITS[duty_cycle];
   int i;

   for (i = 0; i < DUTY_CYCLE_LIMITS[duty_cycle]; i++) {
      squarewave[i] = 0xFFF;
   }

   for (; i < MAX_POINTS; i++) {
      squarewave[i] = 0x000;
   }
}


