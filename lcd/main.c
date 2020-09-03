// This program lights up LED's connected to pins 10-13

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
 
#include <avr/io.h>
#include <util/delay.h>

void lcd_command(unsigned char command, int is_char)
{
    // set data bits
    PORTB = (command & 0xF0) >> 2;
    // set control bits (enable = 1)
    PORTD = 0b01000000 | (is_char ? 0b00010000 : 0);
    _delay_us(1);
    // set control bits (enable = 0)
    PORTD = 0b00000000 | (is_char ? 0b00010000 : 0);
    _delay_us(1);

    // set data bits
    PORTB = (command & 0x0F) << 2;
    // set control bits (enable = 1)
    PORTD = 0b01000000 | (is_char ? 0b00010000 : 0);
    _delay_us(1);
    // set control bits (enable = 0)
    PORTD = 0b00000000 | (is_char ? 0b00010000 : 0);
    _delay_us(37);

    if (command == 0x01 && !is_char) _delay_ms(2);
    if (command == 0x02 && !is_char) _delay_ms(2);
}

void write_string(char *str)
{
    int i;
    for (i = 0; str[i] != 0; i++) lcd_command(str[i], 1);
}

int main(void)
{
    // Initialize ports B (10-13)
    DDRB = 0b00111100;
    // Initialize ports D (4 & 6)
    DDRD = 0b01010000;

    // It takes time to turn on the lcd
    _delay_ms(20);

    lcd_command(0x02, 0);
    lcd_command(0x28, 0);
    lcd_command(0x0C, 0);
    lcd_command(0x01, 0);

    write_string("!@#$%^&*()");
    lcd_command(0xC0, 0);
    write_string("YAY! ____ _____");

    return 0;
}
