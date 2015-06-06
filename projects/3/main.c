/* main.c
 * Main control flow.
 * authors: Robin Choudhury, Jeffrey Wilson
 */
#include "spi.h"
#include "matrix.h"
#include "adc.h"

#include <avr/io.h>
#include <util/delay.h>

#define STROBE PB0
#define RESET PB1

void Initialize_MSGEQ7() {
   DDRB |= 1 << STROBE | 1 << RESET;
   // Create an initial state for our pins
   PORTB &= ~(1 << STROBE) & ~(1 << RESET);
   _delay_ms(1);

   // Reset the MSGEQ7 as per the datasheet timing diagram
   PORTB |= 1 << RESET;
   _delay_ms(1);
   PORTB &= ~(1 << RESET);
   PORTB |= 1 << STROBE;
   _delay_ms(1);
}


int main(void) {
   uint8_t i;

   Initialize_SPI_Master();
   Initialize_ADC0();
   Initialize_MSGEQ7();
   matrix_init();

   while(1) {
      // Get 7 random values from the analog signal.
      for (i = 0; i < 7; i++) {
         PORTB &= ~(1 << STROBE);
         _delay_us(100); // Delay necessary due to timing diagram
         // Display the ADC value on the matrix.
         matrix_write(i + 1, matrix_display(GetConversion()));
         PORTB |= 1 << STROBE;
         _delay_us(100); // Delay necessary due to timing diagram
      }
   }

   return 0;
}
