/* matrix.c
 * Contains functions for interacting with LED matrix.
 * authors: Robin Choudhury, Jeffrey Wilson
 */
#include "matrix.h"
#include "spi.h"
#include <avr/io.h>

// Writes a byte to the specified register.
void matrix_write(uint8_t data_register, uint8_t data) {
   PORTB &= ~(1 << SS); // Assert slave select.
   // Send the register where the data will be stored
   spi_send(data_register);
   // Send the data to be stored
   spi_send(data);
   PORTB |= 1 << SS; // Turn off slave select.
}

// Clears out the matrix.
void matrix_clear() {
   uint8_t digit;

   // Clear display
   for (digit = 0; digit < ALL_DIGITS; digit++) {
      matrix_write(digit + 1, 0);
   }
}

// Initializes the matrix to use no decoding mode.
void matrix_init() {
   matrix_write(MAX7219_MODE_SCAN_LIMIT, ALL_DIGITS); // Show all 8 digits.
   // Use binary values for lighting LEDs up.
   matrix_write(MAX7219_MODE_DECODE, 0);
   matrix_write(MAX7219_MODE_DISPLAYTEST, 0); // No Display test.
   matrix_write(MAX7219_MODE_INTENSITY, MAX_INTENSITY);
   matrix_write(MAX7219_MODE_SHUTDOWN, ON);

   matrix_clear();
}

// Returns the corresponding LEDs to display on the matrix.
uint8_t matrix_display(uint16_t value) {
   uint8_t leds = 0b0;
   uint16_t i;
   if (value >= MAX_VAL - THRESHOLD) {
      leds = 0b11111111;
   } else if (value >= THRESHOLD) {
      for (i = THRESHOLD; i <= value; i++) {
         if (i % THRESHOLD == 0) {
            // Shift leds over by one and OR in a 1.
            leds = (leds << 1) | 1;
         }
      }
   }
   return leds;
}
