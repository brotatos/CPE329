#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initPWM();

int main(void) {
   initPWM(); // Initialize fast PWM to PD5 and PD6
   while(1) {
   }
   return 0;
}

// Initializes motors
void initPWM() {
   DDRD = 0xFF; // Set port D as outputs
   TCCR0A = 0b10100011; // Timer set to fast pwm
   TCCR0B = 0b010; // Timer clk = system clk / 64;
   // outputs 16E6/64/255 = 980Hz PWM
   OCR0A = 50; // Compare value => 20% duty cycle to PD6
   OCR0B = 191; // Compare value => 75% duty cycle to PD5
}
