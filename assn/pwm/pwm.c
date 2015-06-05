#define F_CPU 16000000
# include <avr/io.h>
# include <util/delay.h>

void initPWM();

int main(void) {
   initPWM(); // initialize fast PWM to PD5 and PD6
   while(1) {
   }
   return 0;
}

// initializes motors
void initPWM() {
   DDRD = 0xFF; //set port D as outputs
   TCCR0A = 0b10100011; //timer set to fast pwm
   TCCR0B = 3; //timer clk = system clk / 64;
   //outputs 16E6/64/255 = 980Hz PWM
   OCR0A = 50; //compare value => 20% duty cycle to PD6
   OCR0B = 191; //compare value => 75% duty cycle to PD5
}
