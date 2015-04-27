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

   initTimer0(64);
   sei();

   while(1) {
   }

   return 0;
}
