#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// Wait 2000ns just to be safe instead of 1000ns == T_C.
#define WAIT_TC() _delay_us(2) // Wait time 2*T_C (2 entire cycle).

static void lcd_cmd(char cmd) {
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
   _delay_ms(1);
}

void lcd_init() {
   UCSR0B = 0;        // disable TX, RX
   // PB2 = RS, PB1 = R/W, PB0 = E
   DDRB = 0b00001111; // E, RS, R/W, Button
   DDRD = 0xFF;       // Set all D pins to output
   // Wait 100 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   PORTB = 0; //  RS, R/W, E = low

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
