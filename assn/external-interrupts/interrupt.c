#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//function prototype
void initPCINT0(void);

int main(void) {
   initPCINT0();
   DDRB |= 1<<PB5; // LED as output
   sei();    //enable global interrupts
   while(1); //stuck here forever :)
   return 0;

} // end main

void initPCINT0(void) {
   PCICR = 0x01;     // enable PCINT7..0
   PCMSK0 = 0x01;    // enable PCINT0 interrupt
   PCIFR = 0x01;     // clear previous interrupts
}


ISR(PCINT0_vect) {
   cli();
   PORTB |= 1<<PB5;
   _delay_ms(250);
   PORTB &= ~(1<<PB5);
   sei();
}

