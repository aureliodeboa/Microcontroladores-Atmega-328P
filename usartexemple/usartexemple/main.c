
#include <string.h>
#include <avr/io.h>
#define F_CPU  16000000UL


int main(void)
{
	char invertido[30]="";
	int cont = 0;
	//Para Fosc = 160M, U2Xn =0 e um baud rate= 9600, temos que UBRR0= 103d = 00000000 01100111
	//Para um baud rate = 115200, temos UBRR0 8d = 00000000 00001000
	
	UBRR0H = 0b00000000; // 000000000 bauld rate higth
	UBRR0L = 0b01100111; //9600 bits/s
	
	UCSR0A = 0b01000000; //TXC0 = 1 (zera esse flag) , U2x0 = 0 (velocidade normal), MPCM0 = 0 (desabilita modo multiprocessador)   
	                                                                                                                                                                                                                                                                                                                            
	UCSR0B = 0b00011000; //desabilita interrupção recepçãp (RXCIe0= 0), transmissão (TXCIE0 = 0)
						//e buffer vaxio (UDRIE0=0), habilita receptor USART RXEN0 =1
						//(RxD torna-se uma entrada), habilita transmissor TXEN0 =1
						//(TxD torna-se uma saída), seleciona 8 bits de dados (UCSZ2 =0).
	UCSR0C = 0b00000110; //habilita o modo assincrono ( UMSEL01/00=00), desabilita paridade (UPM01/00=00),
						//seleciona um bit de stop (USBS0 = 0 ), seleciona 8 bits de  dados (UCSZ1/0 =11) e 
						//sem polaridade (UCPOL0 = 0 - modo assincrono).
	
   
    while (1) 
    {
		for(cont=0; UDR0 =='\n' || cont<30; cont++)
		{
			while ((UCSR0A & 0x80) != 0x80){} // Espera a recepção de dados. bit 7 verifica se ha dados para serem lidos 
											 // Rx é zerado apos a leitura de UDR0
			//data = UDR0; //armazena os dados recebidos em data.
			invertido[cont]= UDR0;
			if (invertido[cont]=='\n'){break;}
			
		}
		
		cont = strlen(invertido);
		
		for(;cont>=0;cont--)
		{
			while ((UCSR0A & 0x20) != 0x20){} //Verifica se UDR0 pode receber novos dados para Tx. bit 5
			
			UDR0= invertido[cont];
			
			while ((UCSR0A & 0x40) != 0x40 ){} // Verifica se os dados já foram "transmitidos".
			
			UCSR0A = 0x40; //Zera TXC0 (bit6)
			
			
		}
			
    }
}

