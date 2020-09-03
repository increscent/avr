// This program lights up LED's connected to pins 10-13

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

#define MIN_LIGHT 0b000010
#define MAX_LIGHT 0b111110
 
int main(void)
{
    uint8_t lights;

    // Initialize ports B 2-5
    DDRB = 0b111100;

    lights = MIN_LIGHT;
    while(1)
    {
        PORTB = lights;
        _delay_ms(500);

        lights |= lights << 1;
        if (lights > MAX_LIGHT) lights = MIN_LIGHT;
    }
}
