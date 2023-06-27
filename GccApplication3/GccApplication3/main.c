/*
 * tcO.c
 *
 * Created: 21/05/2023 10:23:50
 * Author : Aurelio
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL


int main(void)
{
	int cont=0;
	DDRB= 0x20; // equivale 0b00100000 PB5 como saida
	
	TIFR0 = 0x07; //zera os flags OCFB, OCFA e TOV 
	PORTB = 0x00;
	TCNT0 = 0x00; //Zera timer 0
	
	TCCR0A= 0x0;
	
	TCCR0B= 0x05; //FOC0A= FOC0B=0 tudo zero CS0[2:0} = 001 (clkIO/1 -sem prescaling).
	
	
    while (1) 
    {
		
		while ((TIFR0 & 0x01) != 0x01)
		{
			//nada acontece, fica nesse while até o flag ir para 1 
		}
				cont++;
		
			TIFR0= 0x01;
			if(cont== 500)
			{
				TIFR0= 0x01; //escreve 1 no bit 0 (TOV) para zerá-lo
				PORTB^=(1<<PB5); //TOOGLE
				cont=0;
			}
		
		
		
    }
   
}

