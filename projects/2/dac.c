#include "spi.h"
#include "dac.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define INTERRUPT_DELAY 250

const int MAX_POINTS = 40;
int *current_wave_array = squarewave;

const int OCR0A_MAX_VALUES[] = {
   61, 255, 165, 124, 99
};

int squarewave[] = {
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0xFFF, 0xFFF,
   0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF,
   0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF
};

int sawtooth[] = {
   0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300,
   1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500,
   2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700,
   3800, 3900
};

int sinewave[] = {
   2047, 2900, 3360, 3560, 3690, 3800, 3900, 4000, 4060, 4095, 4060, 4000,
   3900, 3800, 3690, 3560, 3360, 3000, 2520, 2047, 1574, 1094, 734, 534, 404,
   294, 194, 94, 35, 0, 35, 94, 194, 294, 404, 534, 734, 1094, 1574, 2047
};

const int DUTY_CYCLE_LIMITS[] = {
   0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40
};

void SetDutyCycle(int duty_cycle) {
   int zero_points = MAX_POINTS - DUTY_CYCLE_LIMITS[duty_cycle];
   int i;

   for (i = 0; i < DUTY_CYCLE_LIMITS[duty_cycle]; i++) {
      squarewave[i] = 0xFFF;
   }

   for (; i < MAX_POINTS; i++) {
      squarewave[i] = 0x000;
   }
}

void ChangeDutyCycle() {
   static uint16_t current_duty = 6;
   SetDutyCycle(current_duty++);
   if (current_duty > 10) {
      current_duty = 0;
   }
}


void ChangeWaveform() {
   static wave current_wave = SIN;

   switch (current_wave) {
      case SQUARE:
         current_wave_array = squarewave;
         ++current_wave;
         break;
      case SIN:
         current_wave_array = sinewave;
         ++current_wave;
         break;
      case SAWTOOTH:
         current_wave_array = sawtooth;
         current_wave = SQUARE;
         break;
   }
}

void ChangeFreq(uint16_t freq, uint8_t index) {
   SetClkDiv(freq);
   OCR0A = OCR0A_MAX_VALUES[index];
}

void SwitchFreq() {
   static freq current_freq = Hz_200;

   switch (current_freq) {
      case Hz_100:
         ChangeFreq(64, current_freq++);
         break;
      case Hz_200:
         ChangeFreq(8, current_freq++);
         break;
      case Hz_300:
         ChangeFreq(8, current_freq++);
         break;
      case Hz_400:
         ChangeFreq(8, current_freq++);
         break;
      case Hz_500:
         ChangeFreq(8, current_freq++);
         current_freq = Hz_100;
         break;
   }
}

// Pin is a bitmask
void PollPinChange(uint8_t pin, void (*special_function)()) {
   if (PIND & pin) {
      //cli();
      special_function();
      _delay_ms(INTERRUPT_DELAY);
      //sei();
   }
}
