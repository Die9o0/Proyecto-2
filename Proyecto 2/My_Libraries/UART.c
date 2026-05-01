/*
 * UART.c
 *
 * Created: 28/04/2026 01:21:01
 *  Author: Diego
 */ 
#include "UART.h"
void writeChar(char caracter)
{
	while (!(UCSR0A & (1<<UDRE0))); //Cuando  esté vacío
	UDR0 = caracter;				//Carga el argumento a UDR0
}
void writeString(char* string)
{
	for (uint8_t i=0; string[i] != '\0'; i++)	//Se ejecuta para cada elemento de una cadena
	{
		writeChar(string[i]);
	}
}
void initUART(uint8_t speed, uint8_t multiple_p, uint8_t INT_TX, uint8_t INT_RX, uint8_t INT_UDR0, uint8_t recibir, uint8_t transmitir)
{
	//Configurar RX (PD0) y TX (PD1)
	DDRD	&= ~(1<<DDD0);
	DDRD	|= (1<<DDD1);
	if (speed == doble)
	{
		UCSR0A |= (1<<U2X0);
	} 
	else
	{
		UCSR0A &= ~(1<<U2X0);
	}
	if (multiple_p == multi)
	{
		UCSR0A |= (1<<MPCM0);
	} 
	else
	{
		UCSR0A &= ~(1<<MPCM0);
	}
	if (INT_RX == activado)
	{
		UCSR0B |= (1<<RXCIE0);
	}
	else
	{
		UCSR0B &= ~(1<<RXCIE0);
	}
	if (INT_TX == activado)
	{
		UCSR0B |= (1<<TXCIE0);
	}
	else
	{
		UCSR0B &= ~(1<<TXCIE0);
	}
	if (INT_UDR0 == activado)
	{
		UCSR0B |= (1<<UDRIE0);
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);
	}
	if (recibir == activado)
	{
		UCSR0B |= (1<<RXEN0);
	}
	else
	{
		UCSR0B &= ~(1<<RXEN0);
	}
	if (transmitir == activado)
	{
		UCSR0B |= (1<<TXEN0);
	}
	else
	{
		UCSR0B &= ~(1<<TXEN0);
	}
}