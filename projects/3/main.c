#include "spi.h"
#include "matrix.h"

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
   Initialize_SPI_Master();

   matrix_init();
   matrix_write(MAX7219_DIGIT0, 0b101);

   return 0;
}
