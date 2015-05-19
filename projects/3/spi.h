#ifndef SPI_H
#define SPI_H

#define F_CPU 16000000 // Define internal CLK speed.

// Assumes VDD = 3.3V, your voltages may vary for 5V.
// Pins are indexed at 0.
#define MOSI 3 // PB pin 3
#define SCK  5 // PB pin 5
#define SS   2 // PB pin 2

void Initialize_SPI_Master(void);
// Data is 16-bits.
void Transmit_SPI_Master(int Data);

#endif
