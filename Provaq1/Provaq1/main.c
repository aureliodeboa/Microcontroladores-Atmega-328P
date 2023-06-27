/*
 * Provaq1.c
 *
 * Created: 23/05/2023 14:54:51
 * Author : Aurelio
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	int cont=0;
	
    DDRD=0x20;
	TIFR0=0x07; //
	
	TCCR0A = 0x00;
	TCCR0B = 0x04;
	
    while (1) 
    {
		while ((TIFR0 & 0x01 ) != 0x01)
		{
		}
		TIFR0 = 0x01;
		cont++;
		if (cont==250)
		{
			PORTD ^= (1<<PD5);
			cont=0;
			
		}
    }
}

