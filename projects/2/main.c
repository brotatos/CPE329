#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include "button_interrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void pin_init() {
  DDRB = 1<<MOSI | 1<<SCK | 1<<SS; // make MOSI, SCK and SS outputs
}

int main(void) {
   pin_init();

   Initialize_SPI_Master();

   initTimer0(64);
   DDRB &= ~(1 << PB0);
   sei();

   while(1) {
      PollChangeWaveform();
   }

   return 0;
}
