/* matrix.h
 * Contains function declarations and register addresses for LED Matrix.
 * authors: Robin Choudhury, Jeffrey Wilson
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#define ON  1
#define OFF 0

#define MAX7219_MODE_NOOP 0x00
#define MAX7219_DIGIT0    0x01
#define MAX7219_DIGIT1    0x02
#define MAX7219_DIGIT2    0x03
#define MAX7219_DIGIT3    0x04
#define MAX7219_DIGIT4    0x05
#define MAX7219_DIGIT5    0x06
#define MAX7219_DIGIT6    0x07
#define MAX7219_DIGIT7    0x08

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_SHUTDOWN     0x0C
#define MAX7219_MODE_DISPLAYTEST  0x0F

#define THRESHOLD 128
#define MAX_VAL 1023
#define MAX_INTENSITY 8
#define ALL_DIGITS 7

void matrix_clear();
void matrix_init();
void matrix_write(uint8_t data_register, uint8_t data);

#endif
