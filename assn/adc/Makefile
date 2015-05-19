CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = adc.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=adc.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

adc.hex: adc
	avr-objcopy -O ihex -R .eeprom adc $@

adc: adc.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

adc.o: adc.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ adc.c

upload: adc.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o adc

.PHONY: all clean
