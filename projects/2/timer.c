#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t OCR0A_MAX = 61;
int point_index = 0;

void SetClkDiv(int freq_div) {
   TCCR0B &= ~(0b111);
   switch(freq_div) {
      case 8:
         TCCR0B |= 1 << CS01;
         break;
      case 64:
         TCCR0B |= 1 << CS01 | 1 << CS00;
         break;
      case 256:
         TCCR0B |= 1 << CS02;
         break;
      case 1024:
         TCCR0B |= 1 << CS02;
         break;
      default:
         TCCR0B |= 1 << CS00; // No prescaling.
         break;
   }
}

void initTimer0(int freq_div) {
   SetClkDiv(freq_div);
   TCCR0B |= 1 << FOC0A;
   TCCR0A = 1 << WGM01 | 1 << COM0A0 | 1 << COM0A1; // CTC, Cmp A mode
   OCR0A = OCR0A_MAX;      // Count up to a max of 128
   TIFR0 = 1 << OCF0A;     // clear previous timer overflow
   TIMSK0 = 1 << OCIE0A;   // timer overflow interrupt enabled
}

ISR(TIMER0_COMPA_vect) {
   Transmit_SPI_Master(squarewave[point_index++]);

   if (point_index == MAX_POINTS) {
      point_index = 0;
   }
}
