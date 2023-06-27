#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

//modo normal sem interrução
ISR(TIMER1_OVF_vect){
	
	PORTB ^= (1<<PB5);
	
	
}


int main()
{
	
	DDRB = 0x20; //pb5 o led 
	
	TIFR1 = 0x01; //bit tov
	PORTB = 0x00; //zera como saida
	TCNT1 = 0x00; //zera o contador mesmo isso não sendo possivel
	
	TCCR1A = 0x00; // modo normal
	TCCR1B = 0x03; // prescaler 1024
	TIMSK1 = 0x01;  //necessario apenas para ativar a interrupção
	sei();
	while (1){
		/*while((TIFR1 & 0x01) != 0x001){}
		TIFR1 = 0x01;
		PORTB ^= (1<<PB5);*/
	}
	
	
}