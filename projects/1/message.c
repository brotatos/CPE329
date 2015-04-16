#include "lcd.h"
#include "message.h"
#include "display.h"
#include "nibble.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* NIBBLE_MODE indicates whether a 4-bit or 8-bit interface is being used. */
const char NIBBLE_MODE = FALSE;
/* TOGGLE indicates whether a button press will toggle a new message or not.
 * If TOGGLE is FALSE, the alternate message will be displayed onces and
 * nothing else will be displayed from that point on..
 */
const char TOGGLE = TRUE;

/* Setups pins as needed. */
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

/* Runs the main program. */
int main() {
   pin_init();

   (NIBBLE_MODE ? nibble_lcd_init : lcd_init)();
   lcd_print(DEFAULT_MESSAGE, NIBBLE_MODE);
   (TOGGLE ? toggle : one_shot)();

   return 0;
}
