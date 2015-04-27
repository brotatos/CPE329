#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int MAX_COUNT = 128;
int point_index = 0;

//function prototype
void initTimer0(int);

// global variable declaration!
volatile unsigned char myCounter;

void initTimer0(int low) {
   // timer clk = system clk / 8 = 7.8kHz
   TCCR0B = 1 << CS02 | 1 << FOC0A;
   if (low) {
      // timer clk = system clk / 64 = 976Hz
      TCCR0B |= 1 << CS00;
   }
   // CTC, Cmp A mode
   TCCR0A = 1 << WGM01 | 1 << COM0A0 | 1 << COM0A1;
   OCR0A = MAX_COUNT;      // Count up to a max of 128
   TIFR0 = 1 << OCF0A;     // clear previous timer overflow
   TIMSK0 = 1 << OCIE0A;   // timer overflow interrupt enabled
}

ISR(TIMER0_COMPA_vect) {
   Transmit_SPI_Master(squarewave[point_index++]);

   if (point_index == MAX_POINTS) {
      point_index = 0;
   }
}
