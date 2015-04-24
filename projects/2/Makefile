CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = dac.o spi.o timer.o
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

main: main.c $(OBJECTS)
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) main.c -o $@

dac.o: dac.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ dac.c

spi.o: spi.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ spi.c

timer.o: timer.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ timer.c

clean:
	$(RM) *.hex *.o dac

.PHONY: all clean
