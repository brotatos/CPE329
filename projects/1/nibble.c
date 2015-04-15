#include "nibble.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void nibble_lcd_clear_display() {
   lcd_cmd(0);
   lcd_cmd(1 << PD4);
   _delay_ms(10);
}

void nibble_lcd_init() {
   DDRD = 0xF0;       // Set only top 4 D pins to output.

   /* Function set
    *
    * PD5: must be high
    * PD4: must be high
    * PD3: N -> 2-line mode
    * PD2: F -> display on
    */
   lcd_cmd(1 << PD5);
   lcd_cmd(1 << PD5);
   // pd7 -> 2 line mode; pd6 -> display on
   lcd_cmd(1 << PD7 | 1 << PD6);
   _delay_us(60);

   /* Display ON/OFF Ctl
    *
    * PD3: must be high
    * PD2: display on
    * PD1: cursor on
    * PD0: blink on
    */
   lcd_cmd(0);
   lcd_cmd(1 << PD7 | 1 << PD6 | 1 << PD5 | 1 << PD4);
   _delay_us(60);

   /* Display clear
    *
    * PD0: must be high.
    */
   lcd_cmd(0);
   lcd_cmd(1 << PD4);
   _delay_ms(5);

   /* Entry Mode Set
    *
    * PD2: Must be high
    * PD1: Decrement mode (cursor blinks to right)
    * PD0: Shift mode (OFF)
    */
   lcd_cmd(0);
   lcd_cmd(1 << PD6 | 1 << PD5);

   _delay_ms(10); // Wait until busy state ends.
}
