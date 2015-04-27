CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = interrupt.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=interrupt.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

interrupt.hex: interrupt
	avr-objcopy -O ihex -R .eeprom interrupt $@

interrupt: interrupt.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

interrupt.o: interrupt.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ interrupt.c

upload: interrupt.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o interrupt

.PHONY: all clean
