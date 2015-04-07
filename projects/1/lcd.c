#include "lcd.h"
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define WAIT_TC() _delay_us(1)


//void lc_write_cmd(char cmd);

int main(void) {
   UCSR0B = 0;        // disable TX, RX
   // PB2 = RS, PB1 = R/W, PB0 = E
   DDRB = 0b00000111; // E, RS, R/W
   DDRD = 0xFF;       // Set all D pins to output
   // Wait 40 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(40);

   PORTB = 0; //  RS, R/W, E = low
   _delay_ms(1); // Just to be safe. (Not required.)

   // Function set
   //E_HIGH(PORTB);
   PORTD = 1 << PD5 | 1 << PD4 | 1 << PD3 | 1 << PD2;
   //WAIT_TC();
   //E_LOW(PORTB);
   _delay_us(60);

   /* Display ON/OFF Ctl
    *
    * PD3: must be high
    * PD2: display on
    * PD1: cursor on
    * PD0: blink on
    */
   PORTD = 1 << PD3 | 1 << PD2 | 1 << PD1 | 1 << PD0;
   _delay_us(60);

   // Display clear
   PORTD = 1 << PD0;
   _delay_ms(5);

   // Entry Mode Set
   PORTD = 1 << PD2;
   // Complete initialization.
   _delay_ms(1);

   while (1) {

   }

   return 0;
}
