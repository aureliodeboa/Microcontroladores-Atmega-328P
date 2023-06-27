#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	int cont=-1;
	/*No modo CTC, O TC0 conta até OCR0A (top) e reincia a contagem. Ao atingir top o flag 0CF0A=1*/
	
	DDRD = 0x40; //PD6 COMO SAIDA
	
	TIFR0 = 0x07; //ZERA OS FLAGS OCFB, OCFA E TOV
	PORTD = 0x00; //zera PD6.
	TCNT0 = 0x00; //Zera o timer 0.
	
	OCR0A = 0xFF; //quero que a contagem pare em 256;
	
	TCCR0A = 0x42; //COM0A1 =0 e COM0A0 = 1 (toogle Oc0a on compare match), CM0B1 = CM0B0 = 0 (operação da porta normal)
	//WGM01 = 1, WGM00 = 0  e WGM02 - 0(TCCR0B) (modo CTC, TOP = OCR0A, flag OCF0A setado em TOP).
	TCCR0B = 0x05; //FOC0A= FOC0B = 0, WGM02 = 0, CS0[2:0] = 001 (clkIO/a - sem prescaling), ou seja, N=1.
	// OCR0A = 0xFF e N=1, temos : 62,2n *256=16us a cada 16us ha uma transição.
	
	
	while (1)
	{
		while ((TIFR0 & 0x02) !=0x02){} //verifica se houve overflow, se não houve, não faz nada.
			TIFR0 = 0x02; //Escrevo 1 no bit 1 (OCFA) para zerá-lo.
			
			
		
		
				OCR0A = OCF0A+cont;
				if (OCR0A<=0)
				{
					//OCR0A= 0xFF;
					cont=-1;
					OCR0A = OCF0A-4;
				}
				else{
					if (OCR0A<= 0xFF)
					{
						cont=1;
						OCR0A = OCF0A+4;
						
					}
				}
			
			
			
			
			
			
	}
	
}