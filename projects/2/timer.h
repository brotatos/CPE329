#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

extern const uint8_t OCR0A_MAX;
extern const uint16_t MAX_POINTS;
extern uint16_t white_noise[];
extern uint16_t *current_wave_array;

void initTimer0(uint16_t freq);
void SetClkDiv(uint16_t freq_div);
void SetDutyCycle();

#endif
