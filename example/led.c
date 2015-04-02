#include <avr/io.h>
#include <util/delay.h>

enum {
 BLINK_DELAY_MS = 50,
};

int main (void) {
 /* set pin 5 of PORTB for output*/
 DDRB |= (1<<PB5);

 while(1) {
  /* set pin 5 high to turn led on */
  PORTB |= (1<<PB5);
  _delay_ms(BLINK_DELAY_MS);

  /* set pin 5 low to turn led off */
  PORTB &= ~(1<<PB5);
  _delay_ms(BLINK_DELAY_MS);
 }

 return 0;
}
