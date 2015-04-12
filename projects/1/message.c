#include "lcd.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void) {
   UCSR0B = 0;        // disable TX, RX
   // PB2 = RS, PB1 = R/W, PB0 = E
   DDRB = 0b00000111; // E, RS, R/W
   DDRD = 0xFF;       // Set all D pins to output
   // Wait 100 ms for VDD to surpass 4.5V and to end busy state.
   _delay_ms(100);

   lcd_init();
   print_hello_world();

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
