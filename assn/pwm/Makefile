CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = pwm.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=pwm.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

pwm.hex: pwm
	avr-objcopy -O ihex -R .eeprom pwm $@

pwm: pwm.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

pwm.o: pwm.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ pwm.c

upload: pwm.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o pwm

.PHONY: all clean
