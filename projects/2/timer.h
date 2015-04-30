#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

extern const uint8_t OCR0A_MAX;
extern const int MAX_POINTS;
extern int squarewave[];
extern int sawtooth[];
extern int sinewave[];
extern int *current_wave_array;

void initTimer0(int low);
void SetClkDiv(int freq_div);
void SetDutyCycle();

#endif
