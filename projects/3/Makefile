CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = spi.o matrix.o main.o adc.o
CFLAGS=-Os -Wall -Wextra -Werror -g -MMD
DEV=/dev/ttyACM0
BAUD=115200
AVRDUDE_FLAGS = -F -V -c arduino
# AVR uploader
AVR_CC = avrdude
# Memory to write to
MEM=flash
MAIN=main

all: upload

upload: $(MAIN).hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(MAIN).hex

main.hex: $(MAIN)
	avr-objcopy -O ihex -R .eeprom $(MAIN) $@

main: $(OBJECTS)
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

main.o: main.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ $^

spi.o: spi.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ $^

matrix.o: matrix.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ $^

adc.o: adc.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ $^

clean:
	$(RM) *.hex *.o *.d main

.PHONY: all clean
