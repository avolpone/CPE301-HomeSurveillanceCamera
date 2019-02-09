#define F_CPU 16000000UL
	#define BAUD 9600
#include <avr/io.h>
#include <stdlib.h>
#include <util/setbaud.h>
#include "ioe.h"

void UART_init()
{	
	DDRD |= (1<<PORTD1);	
	DDRD &= ~(1<<PORTD0);		

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
	UCSR0A &= ~(1<<U2X0);

	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);		
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	

	UART_putStr("\033[H\033[2J");
}

unsigned char UART_getChar()
{
	while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

void UART_putChar(unsigned char data)
{
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void UART_putStr(char *output)
{
    char i = 0;
    while(*(output + i) != '\0'){
        UART_putChar(*(output + i));
        i++;
    }
}

void scanm(unsigned char* buffer)
	{
		int i = 0;
		while(buffer[i] != '\n'){
			buffer[i] = UART_getChar();
			if (buffer[i]=='\r')
				break;
			UART_putChar(buffer[i]);
			i++;
		}
		buffer[i] = '\0';
	}