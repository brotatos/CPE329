#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Execute a command by setting the corresponding signals.
 * This is meant for initialization purposes.
 */
void lcd_cmd(char cmd) {
   PORTB = 0;
   E_HIGH(PORTB);
   PORTD = cmd;
   WAIT_TC();
   E_LOW(PORTB);
}

/* Clears the LCD display.
 * If nibble_mode is true, the display is cleared using the nibble version of
 * clear display.
 */
void lcd_clear_display(int nibble_mode) {
   if (nibble_mode) {
      lcd_cmd(0);
      lcd_cmd(1 << PD4);
   } else {
      lcd_cmd(1 << PD0);
   }
   _delay_ms(10);
}

/* Writes a single byte to RAM. */
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

/* Takes a string and writes each individual character of it.
 * If nibble_mode is true, it writes the upper 4 bits and then the lower 4
 * bits.
 */
void lcd_print(char *str, int nibble_mode) {
   while (*str) {
      if (nibble_mode) {
         lcd_write(*str & 0xF0);
         lcd_write(*str++ << 4);
      } else {
         lcd_write(*str++);
      }
   }
}

/* Initializes the LCD with 2-line mode, a cursor, and 8 bit interface. */
void lcd_init() {
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
