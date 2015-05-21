#include "matrix.h"
#include "spi.h"
#include <avr/io.h>


void matrix_write(uint8_t data_register, uint8_t data) {
   PORTB &= ~(1 << SS); // Assert slave select.
   // Send the register where the data will be stored
   spi_send(data_register);
   // Send the data to be stored
   spi_send(data);
   PORTB |= 1 << SS; // Turn off slave select.
}

void matrix_clear() {
   uint8_t digit;

   // Clear display
   for (digit = 0; digit < 8; digit++) {
      matrix_write(digit + 1, 0);
   }
}

void matrix_init() {
   matrix_write(MAX7219_MODE_SCAN_LIMIT, 7); // Show all 8 digits.
   matrix_write(MAX7219_MODE_DECODE, 0); // use an led matrix (not digits)
   matrix_write(MAX7219_MODE_DISPLAYTEST, 0); // No Display test.
   matrix_write(MAX7219_MODE_INTENSITY, 7);
   matrix_write(MAX7219_MODE_SHUTDOWN, ON);

   matrix_clear();
}
