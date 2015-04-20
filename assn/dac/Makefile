CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = dac.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=dac.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

dac.hex: dac
	avr-objcopy -O ihex -R .eeprom dac $@

dac: dac.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

dac.o: dac.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ dac.c

upload: dac.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o dac

.PHONY: all clean
