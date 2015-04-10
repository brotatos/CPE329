CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = lcd.o message.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=message.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

all: upload

message.hex: message
	avr-objcopy -O ihex -R .eeprom message

message: $(OBJECTS)
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

lcd.o: lcd.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ lcd.c

message.o: message.c
	$(CC) -Os -mmcu=$(MMCU) -c -o $@ message.c

upload: message.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o message

.PHONY: all clean
