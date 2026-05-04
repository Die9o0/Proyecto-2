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
void initUART(uint8_t speed, uint8_t multiple_p, uint8_t INT_TX, uint8_t INT_RX, uint8_t INT_UDR0, uint8_t recibir, uint8_t transmitir, uint8_t character_size, uint8_t modo, uint8_t paridad, uint8_t stop_bit, uint8_t clock_pol, uint16_t BAUD_VALUE)
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
	switch (character_size)
	{
		case 5:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		break;
		case 6:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		UCSR0C |= (1<<UCSZ00);
		break;
		case 7:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		UCSR0C |= (1<<UCSZ01);
		break;
		case 8:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
		break;
		case 9:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		UCSR0B |= (1<<UCSZ02);
		UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
		break;
		default:
		UCSR0B &= ~(1<<UCSZ02);
		UCSR0C &= ~((1<<UCSZ01)|(1<<UCSZ00));
		UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
		break;
	}
	switch (modo)
	{
		case asincrono:
		UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL01));
		break;
		case sincrono:
		UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL00));
		UCSR0C |= (1<<UMSEL00);
		break;
		case master:
		UCSR0C |= ((1<<UMSEL01)|(1<<UMSEL00));
		break;
		default:
		UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL01));
		break;
	}
	switch (paridad)
	{
		case desactivado:
		UCSR0C &= ~((1<<UPM00)|(1<<UPM01));
		break;
		case par:
		UCSR0C &= ~((1<<UPM00)|(1<<UPM01));
		UCSR0C |= (1<<UPM01);
		break;
		case impar:
		UCSR0C |= ((1<<UPM00)|(1<<UPM01));
		break;
		default:
		UCSR0C &= ~((1<<UPM00)|(1<<UPM01));
		break;
	}
	if (stop_bit == 2)
	{
		UCSR0C |= (1<<USBS0);
	} 
	else
	{
		UCSR0C &= ~(1<<USBS0);
	}
	if (clock_pol == bajada)
	{
		UCSR0C &= ~(1<<UCPOL0);
	} 
	else
	{
		UCSR0C |= (1<<UCPOL0);
	}
	UBRR0 = BAUD_VALUE;
}