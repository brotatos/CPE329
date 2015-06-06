/* adc.h
 * Contains function declarations for ADC.
 * authors: Robin Choudhury, Jeffrey Wilson
 */
#ifndef _ADC_H_
#define _ADC_H_

#include <stdint.h>

void Initialize_ADC0(void);
uint16_t GetConversion();

#endif
