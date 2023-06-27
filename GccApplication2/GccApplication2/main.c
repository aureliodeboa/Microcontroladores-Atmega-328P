/*
 * GccApplication2.c
 *
 * Created: 19/04/2023 20:30:27
 * Author : Aurelio
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  SET_BIT(VALUE,BIT)(VALUE |=(1<<BIT))
#define  CLEAR_BIT(VALUE,BIT)(VALUE &=~(1<<BIT))
#define  TOGLGLE_BIT(VALUE,BIT)(VALUE ^=(1<<BIT))
#define  GET_BIT(VALUE,BIT)((VALUE>>BIT)&1)

int main(void)
{
    DDRB= 0b00000010; //PB1 saida
	PORTB= 0b00000001; //PB0 Entrada
	
    while (1) 
    {
		if(GET_BIT(PINB,0))
		{
			SET_BIT(PORTB,1);
			
			
		}
		else
		{
			
			CLEAR_BIT(PORTB,1);
			
			
		}
    }
}

