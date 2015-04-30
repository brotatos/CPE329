#ifndef DAC_H
#define DAC_H

#include <stdint.h>

typedef enum {
   SQUARE, SIN, SAWTOOTH, TRIANGLE, TROCHOID, TRAPEZOID, WHITE_NOISE
} wave;
typedef enum {Hz_100, Hz_200, Hz_300, Hz_400, Hz_500} freq;

void DrawTriangle();
void SetDutyCycle();
void ChangeWaveform();
void SwitchFreq();
void ChangeDutyCycle();
void PollPinChange(uint8_t pin, void (*special_function)());
void PollChangeWaveform();
void FillWhiteNoise();

extern uint16_t squarewave[];
extern uint16_t sawtooth[];
extern uint16_t sinewave[];
extern wave current_wave;
extern uint16_t *current_wave_array;
extern uint16_t pouint16_t_index;

#endif
