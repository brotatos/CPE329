#include "lcd.h"
#include "message.h"
#include "display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const char NIBBLE_MODE = FALSE;
const char TOGGLE = TRUE;

void pin_init() {
   UCSR0B = 0; // disable TX, RX
   /* PB3 = ButtonCheck    OUT -> needed for r/w
    * PB2 = RS             OUT
    * PB1 = R/W            OUT
    * PB0 = E              OUT
    */
   DDRB = 0b00001111;
   // Nibble mode only uses the top 4 pins of PORTD.
   DDRD = NIBBLE_MODE ? 0xF0 : 0xFF;
   // Wait 100 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   PORTB = 0; //  RS, R/W, E = low
}

int main() {
   pin_init();

   if (NIBBLE_MODE) {
      nibble_lcd_init();
   } else {
      lcd_init();
   }

   lcd_print(DEFAULT_MESSAGE, NIBBLE_MODE);

   if (TOGGLE) {
      toggle(TRUE);
   } else {
      one_shot(TRUE);
   }

   return 0;
}
