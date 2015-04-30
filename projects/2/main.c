#include "spi.h"
#include "dac.h"
#include "util.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Button pin locations.
#define FREQ (1 << PD3)
#define DUTY (1 << PD4)
#define WAVE (1 << PD5)

// Set up the DDR* registers as needed.
void pin_init() {
  // Make MOSI, SCK and SS outputs
  DDRB |= 1 << MOSI | 1 << SCK | 1 << SS;
  // Set button pins as inputs.
  DDRD &= ~FREQ | ~DUTY | ~WAVE;
}

int main(void) {
   pin_init();

   // Fill the white noise array for the DAC to output.
   FillWhiteNoise();

   Initialize_SPI_Master();

   // Initialize the timer to produce a 50% duty cycle square wave at 100Hz.
   initTimer0(64);
   // Enable interrupts.
   sei();

   // Constantly poll for any changes to the button pins.
   while(1) {
      PollPinChange(WAVE, ChangeWaveform);
      PollPinChange(FREQ, SwitchFreq);
      PollPinChange(DUTY, ChangeDutyCycle);
   }

   return 0;
}
