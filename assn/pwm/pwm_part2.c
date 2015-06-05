#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define INCREMENT 26

void initPWM();

int main(void) {
   initPWM(); // Initialize fast PWM to PD5 and PD6
   while(1) {
      if (PINB & (1 << PB0)) {
         OCR0A += INCREMENT;
         OCR0B -= INCREMENT;
      }
      _delay_ms(100);
   }
   return 0;
}

// Initializes motors
void initPWM() {
   DDRD = 0xFF; // Set port D as outputs
   TCCR0A = 0b10100011; // Timer set to fast pwm
   TCCR0B = 0x3; // Timer clk = system clk / 64;
   // Outputs 16E6/64/255 = 980Hz PWM
   OCR0A = 154; // Compare value => 50% duty cycle to PD6
   OCR0B = 154; // Compare value => 50% duty cycle to PD5
}
