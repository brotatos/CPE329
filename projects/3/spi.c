#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>


void Initialize_SPI_Master(void) {
   // SPI Enable, Master mode
   //SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPR1);
   SPCR |= (0<<SPIE) | // No interrupts
      (1<<SPE) |      // SPI enabled
      (1<<MSTR) |     // master
      (0<<DORD) |     // Send MSB first
      (0<<CPOL) |     // Clock idles low
      (0<<CPHA) |     // Sample on leading edge
      (1<<SPR1) |
      (0<<SPR0) ;     // Clock speed

   SPSR = 0x00;     //clear flags
   PORTB = 1 << SS; // make sure SS is high
}
