#include "spi.h"

#define ON  1
#define OFF 0

#define MAX7219_MODE_NOOP 0x00
#define MAX7219_DIGIT0    0x01
#define MAX7219_DIGIT1    0x02
#define MAX7219_DIGIT2    0x03
#define MAX7219_DIGIT3    0x04
#define MAX7219_DIGIT4    0x05
#define MAX7219_DIGIT5    0x06
#define MAX7219_DIGIT6    0x07
#define MAX7219_DIGIT7    0x08

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_SHUTDOWN     0x0C
#define MAX7219_MODE_DISPLAYTEST  0x0F

#include <avr/io.h>
#include <util/delay.h>

void spiSendByte(uint8_t databyte) {
   SPDR = databyte; // Copy data into the SPI data register
   while (!(SPSR & (1 << SPIF))); // Wait until transfer is complete
}

void MAX7219_write(uint8_t data_register, uint8_t data) {
   PORTB &= ~(1 << SS); // Assert slave select.
   // Send the register where the data will be stored
   spiSendByte(data_register);
   // Send the data to be stored
   spiSendByte(data);
   PORTB |= 1 << SS; // Turn off slave select.
}

void PinInit() {
   DDRB |= 1 << SS | 1 << SCK | 1 << MOSI;
}

void ClearDisplay() {
   uint8_t digit;

   // Clear display
   for (digit = 0; digit < 8; digit++) {
      MAX7219_write(digit + 1, 0);
   }
}

void MAX7219_Init() {
   MAX7219_write(MAX7219_MODE_SCAN_LIMIT, 7); // Show all 8 digits.
   MAX7219_write(MAX7219_MODE_DECODE, 0); // use an led matrix (not digits)
   MAX7219_write(MAX7219_MODE_DISPLAYTEST, 0); // No Display test.
   MAX7219_write(MAX7219_MODE_INTENSITY, 7);
   MAX7219_write(MAX7219_MODE_SHUTDOWN, ON);

   ClearDisplay();
}

int main(void) {
   PinInit();
   Initialize_SPI_Master();
   MAX7219_Init();
   MAX7219_write(MAX7219_DIGIT0, 1);
   return 0;
}
