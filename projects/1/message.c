#include "lcd.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
   lcd_init();
   print_hello_world();
   PORTB |= 1 << BUTTON;

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
