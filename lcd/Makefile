all: clean compile flash

flash: main.hex
	avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex

compile: main.c
	avr-gcc -Os -D__AVR_ATmega328P__ -mmcu=atmega328p -c main.c
	avr-gcc -D__AVR_ATmega328P__ -mmcu=atmega328p -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

clean:
	rm main.o main.elf main.hex || true
