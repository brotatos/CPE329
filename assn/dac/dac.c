#define F_CPU 16000000 //define internal CLK speed
// assumes vdd = 3.3v, your voltages may vary for 5v
#define MOSI 3 // PB pin 3
#define SCK  5 // PB pin 5
#define SS   2 // PB pin 2

#include <avr/io.h>
#include <util/delay.h>

void Initialize_SPI_Master(void);
void Transmit_SPI_Master(int Data);
void DrawTriangle();

int main(void) {
   int count = 0;
   DDRB = 1<<MOSI | 1<<SCK | 1<<SS; // make MOSI, SCK and SS outputs

   Initialize_SPI_Master();

   while(1) {
      //Transmit_SPI_Master(0x333); // 0x333 / 0xFFF = 819 / 4096 * 5V (ref)  ~ 0.99
      //_delay_ms(100);
      DrawTriangle();
      // 0x700 -> used for 1V peak to peak
   }  // end while
   return 0;
}  // end main

void DrawTriangle() {
   int data;
   int incr = 0x050;
   for (data = 0x333; data < 0xAAA; data += incr) {
      Transmit_SPI_Master(data); // 0x333 / 0xFFF = 819 / 4096 * 5V (ref)  ~ 0.99
      _delay_ms(100);
   }

   for (; data >= 0x333; data -= incr) {
      Transmit_SPI_Master(data); // 0x333 / 0xFFF = 819 / 4096 * 5V (ref)  ~ 0.99
      _delay_ms(100);
   }
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
