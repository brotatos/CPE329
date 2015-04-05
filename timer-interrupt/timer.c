#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//function prototype
void initTimer0(void);

// global variable declaration!
volatile unsigned char myCounter;

int main(void) {
   myCounter = 1;
   initTimer0();

   DDRB |= 1<<PB5;

   sei();    //enable global interrupts

   while(1)  //stuck here forever :)
   {
   }
   return 0;

} // end main

// How would we do this in normal?

/* CTC MODE 7.747kHz w/ 50% */
void initTimer0(void) {
   TCCR0A = 0x00;// timer overflow mode
   TCCR0A = (1 << WGM01) | (1 << COM0A0) | (1 << COM0A1); // CTC mode
   //TCCR0B |= 1 << CS00; // timer clk = system clk
   // timer clk = system clk  / 8 -> 7.8kHz
   // 1khz
   TCCR0B = (1 << CS01) | (1 << CS00) | (1 << FOC0A);
   // 7.752 kHz
   //TCCR0B = (1 << CS01) | (1 << FOC0A);
   OCR0A = 128;
   TIFR0 = 0x01;  // clear previous timer overflow
   TIMSK0 = 0x02; // timer overflow interrupt enabled
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

