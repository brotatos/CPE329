/* adc.c
 * Contains functions needed to get digital values of internal ADC.
 * authors: Robin Choudhury, Jeffrey Wilson
 */
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>

// Note to self:
// AREF + ADC GND are *not* hardwired on the ATMega328P.
// Initializes ACD on channel 0.
void Initialize_ADC0(void) {
   ADCSRA = 0x87; //Turn On ADC and set prescaler (CLK/128)
   ADCSRB = 0x00; //turn off autotrigger
   ADMUX = 0x00; //Set ADC channel ADC0
}

// Grabs a single conversion from the ADC and returns it.
uint16_t GetConversion() {
   ADCSRA = 0xC7;
   _delay_us(260);
   return ADC & 0x3FF; // 10-bit DAC so get only 10-bits.
}
