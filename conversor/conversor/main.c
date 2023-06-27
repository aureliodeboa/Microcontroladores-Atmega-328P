#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>



int main(void)
{
	uint8_t datal,datah; //dados do tipo usigned int
	uint16_t  data;       //dados 16bits
	float tensao,temp;     //variaveis para calculo da tensão
	int numero[4],i;		//guarda o numero que vamos enviar
	//char str;
	int aux;		
	
	// Configuração ADC
	
	ADMUX= 0x00;  // bit7 e 6 seleciona AREF como tensão de referencia, ADLAR=0 então ADCH 2bits e ADCL 8 bits,  MUX[3:0]=000 ADC0
	ADCSRA = 0x87; // 0b10000111	// bit 7 liga o ADC, bit 6 converão é incnializada , bit 5 ADATE habilita o auto gatilho, bit 4 ADIF setado quando a conversão é finalizada,
					//bit 3 - ADIE = SE 1 habilita a interrupção ADC, bits 2 ao 0 ADPS[2:0] seleciona o valor de divisão de frequencia.
	ADCSRB = 0b00000000;
	
	// Configuração USART
	
	UBRR0H = 0b00000000;
	UBRR0L = 0b01100111; //9600 bits/s
	
	UCSR0A = 0b01000000;  //TXC0 = 1 (zera esse flag) , U2x0 = 0 (velocidade normal), MPCM0 = 0 (desabilita modo multiprocessador) 
	
	UCSR0B = 0b00011000; //desabilita interrupção recepçãp (RXCIe0= 0), transmissão (TXCIE0 = 0)
						//e buffer vaxio (UDRIE0=0), habilita receptor USART RXEN0 =1
						//(RxD torna-se uma entrada), habilita transmissor TXEN0 =1
						//(TxD torna-se uma saída), seleciona 8 bits de dados (UCSZ2 =0).
	
	UCSR0C = 0b00000110; //habilita o modo assincrono ( UMSEL01/00=00), desabilita paridade (UPM01/00=00),
						//seleciona um bit de stop (USBS0 = 0 ), seleciona 8 bits de  dados (UCSZ1/0 =11) e
						//sem polaridade (UCPOL0 = 0 - modo assincrono).
	

	
	
	while (1)
	{
		_delay_ms(1000);
		ADCSRA = ADCSRA | 0x40; //inicia a conversão ADCS =1
		
		while((ADCSRA & 0x10) != 0x10){} //aguarda a recepção de dados
		
		datal = ADCL;
		datah = ADCH;
		
		ADCSRA = ADCSRA | 0x10; // zera flag
		
		data = ((datah <<8 ) | (datal)); //inteiro sem sinal de 16bits... 0 a 1023. 0 <= d <= 1023
		
		data=64; //31c
		tensao = ((5*data)/1023.0); //valor da tensão
		
		temp = (tensao*1000); //tensão *100 para pegar 3 digit
		aux = temp*10;

		numero[0]= ((aux/1000) + 48); //numero da tabela ascci os nuemros começão em 48 então o valor sera aux+ 48
		aux %=1000;
		numero[1]= ((aux/100) + 48);
		aux %=100;
		numero[2]= 46; // .
		numero[3]= ((aux/10)+ 0x30);
		
		//numero[4]= 111; //o
		//numero[5]= 67; // C
		
		//while((UCSR0A & 0x80) != 0x80){}
		for (i=0;i<4;i++)
		{
			while((UCSR0A & 0x20) != 0x20){}
			UDR0 = numero[i];
			while((UCSR0A & 0x40) != 0x40){}
			UCSR0A= 0x40;
		}
		
		while((UCSR0A & 0x20) != 0x20){}
		UDR0 = 'o';
		while((UCSR0A & 0x40) != 0x40){}
		UCSR0A= 0x40;
		
		
		while((UCSR0A & 0x20) != 0x20){}
		UDR0 = 'C';
		while((UCSR0A & 0x40) != 0x40){}
		UCSR0A= 0x40;
		
		
		while((UCSR0A & 0x20) != 0x20){}
		UDR0 = '\n';
		while((UCSR0A & 0x40) != 0x40){}
		UCSR0A= 0x40;
		
		
		
		
		
		
		
		
		
	}
}