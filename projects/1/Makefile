CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = lcd.o message.o
CFLAGS=-Os -Wextra -Werror -g -MMD -mmcu=$(MMCU)
DEV=/dev/ttyACM0
BAUD=115200
OUT=message.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

message.hex: message
	avr-objcopy -O ihex -R .eeprom message $@

message: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

lcd.o: lcd.c
	$(CC) $(CFLAGS) -c -o $@ lcd.c

message.o: message.c
	$(CC) $(CFLAGS) -c -o $@ message.c

upload: message.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o message

.PHONY: all clean
