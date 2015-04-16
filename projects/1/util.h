#ifndef UTIL_H
#define UTIL_H

#define F_CPU 16000000

#define TRUE 1
#define FALSE 0

#define E_HIGH(f) (f |= 1)
#define RW_HIGH(f) (f |= 2)
#define RS_HIGH(f) (f |= 4)

#define E_LOW(f) (f &= 0b11111110)
#define RW_LOW(f) (f &= 0b11111101)
#define RS_LOW(f) (f &= 0b11111011)

// Wait 2000ns just to be safe instead of 1000ns == T_C.
#define WAIT_TC() _delay_us(2) // Wait time 2*T_C (2 entire cycle).

#endif
