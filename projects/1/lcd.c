#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void lcd_cmd(char cmd) {
   PORTB = 0;
   E_HIGH(PORTB);
   PORTD = cmd;
   WAIT_TC();
   E_LOW(PORTB);
}

void lcd_clear_display() {
   lcd_cmd(1 << PD0);
   _delay_ms(10);
}

void lcd_write(char character) {
   PORTB = 0;
   E_HIGH(PORTB);
   RS_HIGH(PORTB);
   RW_LOW(PORTB);
   PORTD = character;
   WAIT_TC();
   E_LOW(PORTB);
   _delay_us(50); // Wait just in case for sequential writes.
}

void lcd_print(char *str, int nibble_mode) {
   while (*str) {
      if (nibble_mode) {
         lcd_write(*str & 0xF0);
         lcd_write((*str++ & 0x0F) << 4);
      } else {
         lcd_write(*str++);
      }
   }
}

void lcd_init() {
   DDRD = 0xFF;       // Set all D pins to output

   /* Function set
    *
    * PD5: must be high
    * PD4: must be high
    * PD3: N -> 2-line mode
    * PD2: F -> display on
    */
   lcd_cmd(1 << PD5 | 1 << PD4 | 1 << PD3 | 1 << PD2);
   _delay_us(60);

   /* Display ON/OFF Ctl
    *
    * PD3: must be high
    * PD2: display on
    * PD1: cursor on
    * PD0: blink on
    */
   lcd_cmd(1 << PD3 | 1 << PD2 | 1 << PD1 | 0 << PD0);
   _delay_us(60);

   /* Display clear
    *
    * PD0: must be high.
    */
   lcd_cmd(1 << PD0);
   _delay_ms(5);

   /* Entry Mode Set
    *
    * PD2: Must be high
    * PD1: Decrement mode (cursor blinks to right)
    * PD0: Shift mode (OFF)
    */
   lcd_cmd(1 << PD2 | 1 << PD1);

   _delay_ms(10); // Wait until busy state ends.
}
