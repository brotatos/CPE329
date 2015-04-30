#ifndef DAC_H
#define DAC_H

typedef enum {SQUARE, SIN, SAWTOOTH} wave;

void DrawTriangle();
void SetDutyCycle();
void ChangeWaveform();
void PollChangeWaveform();

extern int squarewave[];
extern int sawtooth[];
extern int sinewave[];
extern wave current_wave;
extern int *current_wave_array;
extern int point_index;

#endif
