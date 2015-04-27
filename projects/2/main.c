#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
   pin_init();
   Initialize_SPI_Master();

   initTimer0(TRUE);
   sei();

   //Transmit_SPI_Master(0xFFF);
   while(1) {
      //Transmit_SPI_Master(squarewave[idx++]);
      //if (idx == MAX_POINTS) {
      //   idx = 0;
      //}
      //_delay_ms(100);
   }

   return 0;
}
