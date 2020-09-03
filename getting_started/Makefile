all: clean compile flash

flash:
	avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:test.hex

compile:
	avr-gcc -Os -D__AVR_ATmega328P__ -mmcu=atmega328p -c test.c
	avr-gcc -D__AVR_ATmega328P__ -mmcu=atmega328p -o test.elf test.o
	avr-objcopy -O ihex test.elf test.hex

clean:
	rm test.o test.elf test.hex || true
