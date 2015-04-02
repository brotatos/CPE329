CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = timer.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=timer.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

timer.hex: timer
	avr-objcopy -O ihex -R .eeprom timer $@

timer: timer.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

timer.o: timer.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ timer.c

upload: timer.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o timer

.PHONY: all clean
