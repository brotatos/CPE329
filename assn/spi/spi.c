//define internal CLK speed
#define F_CPU 16000000

#define MOSI 3  // PB pin 3
#define SCK  5  // PB pin 5
#define SS   2  // PB pin 2

#include <avr/io.h>
#include <util/delay.h>

void Initialize_SPI_Master(void);
void Transmit_SPI_Master(char Data);

int main(void) {
   // D2 D1 D0
   // MOSI 3 SCK 5 SS 2
   DDRB = 1<<MOSI | 1<<SCK | 1<<SS; // make MOSI, SCK and SS outputs
   //DDRB = 0xFF;

   Initialize_SPI_Master();

   while(1) {
      //Transmit_SPI_Master(00xF);
      Transmit_SPI_Master(0x0F);
      _delay_ms(1200);
      _delay_us(100);
      Transmit_SPI_Master(0x5A);
      _delay_ms(1200);
      _delay_us(100);
   }  // end while
   return 0;  // end main
 }


void Initialize_SPI_Master(void) {
   SPCR = (0<<SPIE) | //No interrupts
      (1<<SPE) | //SPI enabled
      (0<<DORD) | //send MSB first
      (1<<MSTR) | //master
      (0<<CPOL) | //clock idles low
      (1<<CPHA) | //sample leading edge
      (0<<SPR1) | (0<<SPR0) ; //clock speed
   SPSR = (0<<SPIF) | //SPI interrupt flag
      (0<<WCOL) | //Write collision flag
      (0<<SPI2X) ; //Doubles SPI clock

   PORTB = 1 << SS; // make sure SS is high
}

void Transmit_SPI_Master(char Data) {
   PORTB = 0 << SS;             // assert the slave select
   SPDR = Data;                 // Start transmission, send high byte first
   while (!(SPSR & (1<<SPIF))); // Wait (poll) for transmission complete
   PORTB = 1 << SS;             // deassert the slave select
}
