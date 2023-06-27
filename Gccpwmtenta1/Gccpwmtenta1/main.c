/*
 * pwm.c
 *
 * Created: 23/05/2023 08:41:54
 * Author : Aurelio
 */ 

#include <avr/io.h>
#define  F_CPU 16000000UL

int main(void)
{
   // No modo fast PWM, o TC0 conta até TOP (0xFF ou OCR0A) e reinicia a contagem. ao atingir TOP, o flag OCF0A=1;
   //0 sinal PWM é gerado no pino 0C0A (PD6).
   // clkSYS = 1/16MHz = 60,5 ns = cljIO = clkT0
   
   DDRB = 0x40; //ob01000000 ativa o PD6
   DDRB = 0b00001000;
   TIFR0 = 0x07; //zera o flags OCFB e, OCFA e TOV 0b00000111
   PORTD = 0x00; //zera o PD6
   TCNT0 = 0x00; //zera timer 0

	OCR0A = 0x00;
	//OCR0B= 0xFF;
	
	TCCR0A =  0x83; //0b10100011;// // COM0A1 = 1 e COM0A0 = 0 (zera OC0A on cmopare match), COM0B1 = COM0B0 = 0 (operação da porta normal).
	//WGM01 = 1, WGM00 = 1 WGM02 - 0 (TCCR0B) (modo fast PWM, TOP = 0xFF, flag TOV setado em TOP= 0xFF).
	
	TCCR0B= 0x04; // 0b00001101;// //FOC0A = FOC0B = 0, WGM02 = 0, CS0[2:0]= 101 (clkIO/1024), ou seja, N= 1024.
	// OCR0A = 0xFF e N=1, temos: 62,5 n*256 = 16us *1024 =~ 16,4ms... freqPWM=~61HZ
   
    while (1) 
    {
		while((TIFR0 & 0x02) != 0x02){} //verifica se hove overflow, se não houve, não faz nada.
		TIFR0 = 0x02; //Escrevo 1 no bit (OCFA) para zerá-lo
		
		OCR0A = OCR0A + 1;
		if (OCR0A >= 255)
		{
			OCR0A = 0x00;
			PORTD ^= (1<<PD6);
			PORTD ^= (1<<PD3);
			TIFR0 = 0x02;
		}
		
    }
}

