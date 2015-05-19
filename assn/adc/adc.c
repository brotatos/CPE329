#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


// Note to self:
// AREF + ADC GND are *not* hardwired on the ATMega328P.

void Initialize_ADC0(void);

int getTimeDelay(int voltage) {
   int time = -1;

   // [4-5) => 16 Hz
   if (voltage < 1023 && voltage >= 818) {
      time = 31;
   // [3-4) => 8 Hz
   } else if (voltage < 818 && voltage >= 614) {
      time = 62;
   // [2-3) => 4 Hz
   } else if (voltage < 614 && voltage >= 409) {
      time = 124;
   // [1-2) => 2 Hz
   } else if (voltage < 409 && voltage >= 205) {
      time = 248;
   // [0-1) => 1 Hz
   } else if (voltage < 205 && voltage >= 0) {
      time = 496;
   }

   return time;
}

int main(void) {
   int i, voltage = 0;
   char toggle = 0;
   int time;

   DDRB = 1 << PB5; // Set PB5 output
   Initialize_ADC0(); // Initialize ADC0 for manual trigger

   while(1) {
      ADCSRA = 0xC7; // start conversion
      _delay_us(260); // ensure max sampling rate not exceeded
      voltage = ADC & 0x3FF; // read voltage
      toggle ^= 1;
      PORTB = toggle << 5; // toggle LED
      time = getTimeDelay(voltage);
      // Wait approx (0 <­> 1023)/33 mS
      for (i = 0; i < time; ++i) {
         _delay_ms(1);
      }
   }

   return 0;
}

void Initialize_ADC0(void) {
   ADCSRA = 0x87; //Turn On ADC and set prescaler (CLK/128)
   ADCSRB = 0x00; //turn off autotrigger
   ADMUX = 0x01; //Set ADC channel ADC1
}
