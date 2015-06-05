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
}

void initPCINT0(void) {
   //PCICR = 0x01;     // Enable PCINT7..0
   //PCMSK0 = 0x01;    // Enable PCINT0 interrupt
   //PCIFR = 0x01;     // Clear previous interrupts
   EIMSK = 0x01;     // Enable PCINT0
   EICRA = 0x01;     // Any voltage change will cause an interrupt.
   EIFR = 0x01;      // Clear previous interrupts. Set it.
}

ISR(INT0_vect) {
   cli();
   PORTB |= 1<<PB5;
   _delay_ms(250);
   PORTB &= ~(1<<PB5);
   sei();
}
