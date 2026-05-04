/*
 * TIMER2.c
 *
 * Created: 1/05/2026 00:25:11
 *  Author: Diego
 */ 
#include "TIMER2.h"

void initTIMER2 (uint8_t modo, uint16_t prescaler, uint8_t OCR2A_value, uint8_t OCR2B_value, uint8_t INT_OC2A, uint8_t INT_OC2B, uint8_t INT_OVF)
{
	if (modo == CTC)
	{
		TCCR2A &= ((1<<WGM20)|(1<<WGM21));
		TCCR2B &= (1<<WGM22);
		TCCR2A |= (1<<WGM21);
	} 
	else
	{
		TCCR2A &= ((1<<WGM20)|(1<<WGM21));
		TCCR2B &= (1<<WGM22);
	}
	switch (prescaler)
	{
	case 8:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS21);
	break;
	case 32:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS21)|(1<<CS20);
	break;
	case 64:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS22);
	break;
	case 128:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS22)|(1<<CS20);
	break;
	case 256:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS22)|(1<<CS21);
	break;
	case 1024:
	TCCR2B |= ((1<<CS22)|(1<<CS21)|(1<<CS20));
	break;
	default:
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2B |= (1<<CS20);
	break;
	}
	
	OCR2A = OCR2A_value;
	OCR2B = OCR2B_value;
	if (INT_OC2A == activado)
	{
		TIMSK2 |= (1<<OCIE2A);
	} 
	else
	{
		TIMSK2 &= ~(1<<OCIE2A);
	}
	if (INT_OC2B == activado)
	{
		TIMSK2 |= (1<<OCIE2B);
	}
	else
	{
		TIMSK2 &= ~(1<<OCIE2B);
	}
	if (INT_OVF == activado)
	{
		TIMSK2 |= (1<<TOIE2);
	}
	else
	{
		TIMSK2 &= ~(1<<TOIE2);
	}
}
