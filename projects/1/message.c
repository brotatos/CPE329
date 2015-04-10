#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
   UCSR0B = 0;        // disable TX, RX
   // PB2 = RS, PB1 = R/W, PB0 = E
   DDRB = 0b00000111; // E, RS, R/W
   DDRD = 0xFF;       // Set all D pins to output
   // Wait 60 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   lcd_init();

   return 0;
}
