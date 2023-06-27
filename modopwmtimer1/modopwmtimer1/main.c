

#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU 16000000UL

ISR(TIMER1_COMPA_vect){
	TIFR1= 0x02;
	PORTB ^= (1<<PB5);
	
}

int main(void)
{
	//int cont = 0;
    DDRB= 0x20; //pb5 
	
	//TCCR1A = 0b0100001; //fast pwm for top tov
	//TCCR1B = 0b00001101;//fast pwm for top tov
	TCCR1A = 0b0100011; //fast pwm top ocr1a
	TCCR1B = 0b00011101;//fast pwm for top ocr1a
	sei();
	TCCR1C = 0x00;
	OCR1AH = 0b11111111;
	OCR1AL = 0b11111111;
	TIMSK1 = 0b00000010;
	 
	  //TIFR1 =  0b00000001;  // fast pwm for top tov
	TIFR1 =  0b00000010;  // fast pwm for top ocr1a
    while (1) 
    {
		/*while ((TIFR1 & 0x02) != 0x02)
		{
			//do nothing
		}
		TIFR1= 0x02;
		PORTB ^= (1<<PB5);*/
		
		/*cont++;
		TIFR1=0x01;
		if (cont>=10)
		{
			cont=0;
			
			PORTB ^=(1<<PB5);
			
			
		}*/
    }
}

