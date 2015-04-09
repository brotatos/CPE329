#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define TRUE 1
#define FALSE 0
#define MAX_COUNT 127

//function prototype
void initTimer0(int);

// global variable declaration!
volatile unsigned char myCounter;

int main(void) {
   myCounter = 1;

   initTimer0(TRUE);

   DDRB |= 1<<PB5;

   sei();    //enable global interrupts

   while(1)  //stuck here forever :)
   {
   }
   return 0;

} // end main

void initTimer0(int low) {
   // timer clk = system clk / 8 = 7.8kHz
   TCCR0B = 1 << CS01 | 1 << FOC0A;
   if (low) {
      // timer clk = system clk / 64 = 976Hz
      TCCR0B |= 1 << CS00;
   }
   // CTC, Cmp A mode
   TCCR0A = 1 << WGM01 | 1 << COM0A0 | 1 << COM0A1;
   OCR0A = MAX_COUNT;      // Count up to a max of 128
   TIFR0 = 1 << OCF0A;     // clear previous timer overflow
   TIMSK0 = 1 << OCIE0A;   // timer overflow interrupt enabled
}


ISR(TIMER0_COMPA_vect) {
   if (myCounter == 1) {
      myCounter = 0;
      PORTB |= 1<<PB5;
   } else {
      myCounter++;
      PORTB &= ~(1<<PB5);
   }
}

