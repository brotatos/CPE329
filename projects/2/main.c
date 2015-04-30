#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include "lcd.h"
#include "nibble.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FREQ (1 << PD3)
#define DUTY (1 << PD4)
#define WAVE (1 << PD5)

void pin_init() {
  DDRB |= 1 << MOSI | 1 << SCK | 1 << SS; // make MOSI, SCK and SS outputs
  DDRD &= ~FREQ | ~DUTY | ~WAVE;
}

int main(void) {
   pin_init();

   FillWhiteNoise();

   Initialize_SPI_Master();

   initTimer0(64);
   sei();

   while(1) {
      PollPinChange(WAVE, ChangeWaveform);
      PollPinChange(FREQ, SwitchFreq);
      PollPinChange(DUTY, ChangeDutyCycle);
   }

   return 0;
}
