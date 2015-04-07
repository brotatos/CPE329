CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = lcd.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=lcd.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

lcd.hex: lcd
	avr-objcopy -O ihex -R .eeprom lcd $@

lcd: lcd.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

lcd.o: lcd.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ lcd.c

upload: lcd.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o lcd

.PHONY: all clean
