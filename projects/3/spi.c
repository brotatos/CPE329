#include "spi.h"
#include <avr/io.h>

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

   // Set SS, SCK, and MOSI pins to output.
   DDRB |= 1 << SS | 1 << SCK | 1 << MOSI;
   PORTB = 1 << SS; // make sure SS is high
}

void spi_send(uint8_t databyte) {
   SPDR = databyte; // Copy data into the SPI data register
   while (!(SPSR & (1 << SPIF))); // Wait until transfer is complete
}
