#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL


ISR(TIMER1_COMPA_vect){
	PORTB ^= (1<<PB5);
	//TIFR1= 0x02;
}


int main(void)
{
	DDRB = 0x20; //pb5
	
	TCCR1A = 0b01000000;
	TCCR1B = 0b00001100;
	
	TCCR1C= 0x00;
	
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	
	OCR1AH = 0b11111111;
	OCR1AL=  0b11111111;
	
	sei();
	
	TIMSK1= 0x02; //interrupção em compare macth a
 
   	TIFR1 = 0x02;
	   	
	 
	
   
    while (1) 
    {
		/*while((TIFR1 & 0x02) != 0x02){}
			PORTB ^= (1<<PB5);
			TIFR1 = 0x02;*/
    }
}

