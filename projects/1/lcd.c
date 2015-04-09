#include "lcd.h"
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// Wait 2000ns just to be safe instead of 1000ns == T_C.
#define WAIT_TC() _delay_us(2) // Wait time T_C (entire cycle).


void lcd_cmd(char portD);
void lcd_init(void);

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

void lcd_cmd(char cmd) {
   E_HIGH(PORTB);
   PORTD = cmd;
   WAIT_TC();
   E_LOW(PORTB);
}

void lcd_init() {
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
   lcd_cmd(1 << PD3 | 1 << PD2 | 1 << PD1 | 1 << PD0);
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
}
