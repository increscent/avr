// This program lights up LED's connected to pins 10-13

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
 
#include <avr/io.h>
#include <util/delay.h>

// 10 ms delay
void lcd_command(unsigned char command, int is_char)
{
    // set data bits
    PORTB = (command & 0xF0) >> 2;
    // set control bits (enable = 1)
    PORTD = 0b01000000 | (is_char ? 0b00010000 : 0);
    _delay_ms(2);
    // set control bits (enable = 0)
    PORTD = 0b00000000 | (is_char ? 0b00010000 : 0);
    _delay_ms(2);

    // set data bits
    PORTB = (command & 0x0F) << 2;
    // set control bits (enable = 1)
    PORTD = 0b01000000 | (is_char ? 0b00010000 : 0);
    _delay_ms(2);
    // set control bits (enable = 0)
    PORTD = 0b00000000 | (is_char ? 0b00010000 : 0);
    _delay_ms(4);
}

void write_char(char c)
{
    lcd_command(c, 1);
}

void write_string(char *str)
{
    int i;
    for (i = 0; str[i] != 0; i++) write_char(str[i]);
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

    int hour = 22;
    int minute = 21;
    int second = 0;

    while (1)
    {
        second++;

        if (second == 60)
        {
            minute++;
            second = 0;
        }

        if (minute == 60)
        {
            hour++;
            minute = 0;
        }

        if (hour == 24)
        {
            hour = 0;
        }

        write_char(hour / 10 + 0x30);
        write_char(hour % 10 + 0x30);
        write_char(':');
        write_char(minute / 10 + 0x30);
        write_char(minute % 10 + 0x30);
        write_char(':');
        write_char(second / 10 + 0x30);
        write_char(second % 10 + 0x30);

        for (int i = 0; i < 8; i++) lcd_command(0x10, 0);

        _delay_ms(840);
    }

    return 0;
}
