/*
 * GccApplication1.c
 *
 * Created: 15/04/2023 19:56:44
 * Author : Aurelio
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00100000;
	PORTB = 0x20;
    /* Replace with your application code */
	
	_delay_ms(1000);
    while (1) 
    {
		PORTB = 0x00;
		_delay_ms(50);
		PORTB = 0x20;
		_delay_ms(50);
    }
}

