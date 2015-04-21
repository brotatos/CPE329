CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = uart.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=uart.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

uart.hex: uart
	avr-objcopy -O ihex -R .eeprom uart $@

uart: uart.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

uart.o: uart.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ uart.c

upload: uart.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o uart

.PHONY: all clean
