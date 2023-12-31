/*
 * tcO.c
 *
 * Created: 21/05/2023 10:23:50
 * Author : Aurelio
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

ISR(TIMER0_OVF_vect)
{
	PORTB ^=(1<<PB5);
}

int main(void)
{
	DDRB= 0x20; // equivale 0b00100000 PB5 como saida
	
	TIFR0 = 0x07; //zera os flags OCFB, OCFA e TOV 
	TIMSK0= 0x01; //Habilita interrupçao timer 0
	sei(); //Habilita interrupção global
	
	
	PORTB = 0x00;
	TCNT0 = 0x00; //Zera timer 0
	
	TCCR0A= 0x0;
	
	TCCR0B= 0x05; //FOC0A= FOC0B=0 tudo zero CS0[2:0} = 001 (clkIO/1 -sem prescaling).
	
	
    while (1) 
    {
		
    }
}

