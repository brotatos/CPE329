#ifndef DAC_H
#define DAC_H

#include <stdint.h>

typedef enum {SQUARE, SIN, SAWTOOTH} wave;
typedef enum {Hz_100, Hz_200, Hz_300, Hz_400, Hz_500} freq;

void DrawTriangle();
void SetDutyCycle();
void ChangeWaveform();
void SwitchFreq();
void ChangeDutyCycle();
void PollPinChange(uint8_t pin, void (*special_function)());
void PollChangeWaveform();

extern int squarewave[];
extern int sawtooth[];
extern int sinewave[];
extern wave current_wave;
extern int *current_wave_array;
extern int point_index;

#endif
