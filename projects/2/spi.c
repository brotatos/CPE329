#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

void pin_init() {
  DDRB = 1<<MOSI | 1<<SCK | 1<<SS; // make MOSI, SCK and SS outputs
}

void Initialize_SPI_Master(void) {
   SPCR = (0<<SPIE) | // No interrupts
      (1<<SPE) |      // SPI enabled
      (1<<MSTR) |     // master
      (0<<DORD) |     // Send MSB first
      (0<<CPOL) |     // Clock idles low
      (0<<CPHA) |     // Sample on leading edge
      (0<<SPR1) |
      (0<<SPR0) ;     // Clock speed

   SPSR = 0x00;     //clear flags
   PORTB = 1 << SS; // make sure SS is high
}

// Data is 16 bits on the ATMega 328p.
void Transmit_SPI_Master(int Data) {
   PORTB &= ~(1 << SS);                  // Assert slave select (active low)
   SPDR = ((Data >> 8) & 0xF) | 0x70;    // Attach configuration Bits onto MSB
   while (!(SPSR & (1<<SPIF)));
   SPDR = 0xFF & Data;
   while (!(SPSR & (1<<SPIF)));
   PORTB |= 1 << SS;                     // Turn off slave select
}
