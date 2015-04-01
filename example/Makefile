CC=avr-gcc
F_CPU=16000000UL
MMCU=atmega328p
OBJECTS = led.o
CFLAGS=-Os
DEV=/dev/ttyACM0
BAUD=115200
OUT=led.hex
AVRDUDE_FLAGS = -F -V -c arduino
AVR_CC = avrdude
MEM=flash

led.hex: led
	avr-objcopy -O ihex -R .eeprom led $@

led: led.o
	$(CC) $(CFLAGS) -mmcu=$(MMCU) $(OBJECTS) -o $@

led.o: led.c
	$(CC) -Os -DF_CPU=$(F_CPU) -mmcu=$(MMCU) -c -o $@ led.c

upload: led.hex
	sudo $(AVR_CC) $(AVRDUDE_FLAGS) -p $(MMCU) -P $(DEV) -b $(BAUD) -U $(MEM):w:$(OUT)

clean:
	$(RM) *.hex *.o led

.PHONY: all clean
