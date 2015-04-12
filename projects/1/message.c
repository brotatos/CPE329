#include "lcd.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
   char firstTime = TRUE;
   int pressed;

   lcd_init();
   print_hello_world();

   PORTB |= 1 << BUTTON;

   while (firstTime) {
      if (PINB & (1 << BUTTON_CHECK)) { // this if statement isn't working
         firstTime = FALSE;
         print_alt_message();
      }
   }
   return 0;
}

void print_hello_world() {
   lcd_write(0x48); // H
   lcd_write(0x65); // e
   lcd_write(0x6C); // l
   lcd_write(0x6C); // l
   lcd_write(0x6F); // o
   lcd_write(0x20); // blank
   lcd_write(0x57); // W
   lcd_write(0x6F); // o
   lcd_write(0x72); // r
   lcd_write(0x6C); // l
   lcd_write(0x64); // d
}

void print_alt_message() {
   lcd_clear_display();
   lcd_write(0x57); // W
   lcd_write(0x6F); // o
   lcd_write(0x72); // r
   lcd_write(0x6C); // l
   lcd_write(0x64); // d
   lcd_write(0x20); // blank
   lcd_write(0x48); // H
   lcd_write(0x65); // e
   lcd_write(0x6C); // l
   lcd_write(0x6C); // l
   lcd_write(0x6F); // o
}
