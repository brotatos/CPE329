#include "lcd.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {
   char firstTime = TRUE;

   UCSR0B = 0; // disable TX, RX
   /* PB4 = ButtonCheck    IN
    * PB3 = Button         OUT
    * PB2 = RS             OUT
    * PB1 = R/W            OUT
    * PB0 = E              OUT
    */
   DDRB = 0b00001111;
   // Wait 100 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   PORTB = 0; //  RS, R/W, E = low

   lcd_init();
   print_hello_world();
   //nibble_lcd_init();
   //nibble_print_hello_world();

   PORTB |= 1 << BUTTON;

   while (firstTime) {
      if (PINB & (1 << BUTTON_CHECK)) {
         firstTime = FALSE;
         print_alt_message();
         //nibble_print_alt_message();
      }
   }
   return 0;
}

void print_hello_world() {
   lcd_print("Hello World", FALSE);
}

void nibble_print_hello_world() {
   lcd_print("Hello World", TRUE);
}

void nibble_print_alt_message() {
   nibble_lcd_clear_display();
   lcd_print("Project 1 done", TRUE);
}

void print_alt_message() {
   lcd_clear_display();
   lcd_print("Project 1 done.", FALSE);
}
