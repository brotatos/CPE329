#include "lcd.h"
#include "message.h"
#include "display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void pin_init() {
   UCSR0B = 0; // disable TX, RX
   /* PB3 = ButtonCheck    OUT -> needed for r/w
    * PB2 = RS             OUT
    * PB1 = R/W            OUT
    * PB0 = E              OUT
    */
   DDRB = 0b00001111;
#if NIBBLE_MODE == FALSE
   DDRD = 0xFF; // Use the entire data bus.
#else
   DDRD = 0xF0; // Use top 4 bits of the data bus.
#endif
   // Wait 100 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   PORTB = 0; //  RS, R/W, E = low
}

int main(void) {
   pin_init();

#if NIBBLE_MODE == FALSE
   lcd_init();
#else
   nibble_lcd_init();
#endif

   lcd_print(DEFAULT_MESSAGE, NIBBLE_MODE);

#if TOGGLE == FALSE
   one_shot(TRUE);
#else
   toggle(TRUE);
#endif

   return 0;
}
