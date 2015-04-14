#include "lcd.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {
   char firstTime = TRUE;

   nibble_lcd_init();
   nibble_print_hello_world();
   //lcd_init();
   //print_hello_world();

   PORTB |= 1 << BUTTON;

   while (firstTime) {
      if (PINB & (1 << BUTTON_CHECK)) {
         firstTime = FALSE;
         //print_alt_message();
         nibble_print_alt_message();
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

void nibble_print(char character) {
   lcd_write(character & 0xF0);
   lcd_write((character & 0x0F) << 4);
}

void nibble_print_hello_world() {
   nibble_print(0x48); // H
   nibble_print(0x65); // e
   nibble_print(0x6C); // l
   nibble_print(0x6C); // l
   nibble_print(0x6F); // o
   nibble_print(0x20); // blank
   nibble_print(0x57); // W
   nibble_print(0x6F); // o
   nibble_print(0x72); // r
   nibble_print(0x6C); // l
   nibble_print(0x64); // d
}

void nibble_print_alt_message() {
   nibble_lcd_clear_display();
   nibble_print(0x57); // W
   nibble_print(0x6F); // o
   nibble_print(0x72); // r
   nibble_print(0x6C); // l
   nibble_print(0x64); // d
   nibble_print(0x20); // blank
   nibble_print(0x48); // H
   nibble_print(0x65); // e
   nibble_print(0x6C); // l
   nibble_print(0x6C); // l
   nibble_print(0x6F); // o
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
