CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = spi.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=spi.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

spi.hex: spi
	avr-objcopy -O ihex -R .eeprom spi $@

spi: spi.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

spi.o: spi.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ spi.c

upload: spi.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o spi

.PHONY: all clean
