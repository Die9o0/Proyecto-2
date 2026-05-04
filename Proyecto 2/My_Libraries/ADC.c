/*
 * ADC.c
 *
 * Created: 2/05/2026 00:35:20
 *  Author: Diego
 */ 

#include "ADC.h"

void initADC (uint8_t referencia, uint8_t justificacion, uint8_t MUXADC, uint8_t auto_trigger, uint8_t INT_ADC, uint8_t prescaler, uint8_t trigger)
{
	ADCSRA |= (1<<ADEN);
	switch (referencia)
	{
		case AREF:
		ADMUX &= ~((1<<REFS1)|(1<<REFS0));
		break;
		case AVCC:
		ADMUX &= ~((1<<REFS1)|(1<<REFS0));
		ADMUX |= (1<<REFS0);
		break;
		case interno:
		ADMUX &= ~((1<<REFS1)|(1<<REFS0));
		ADMUX |= (1<<REFS0)|(1<<REFS1);
		break;
		default:
		ADMUX &= ~((1<<REFS1)|(1<<REFS0));
		ADMUX |= (1<<REFS0);
		break;
	}
	if (justificacion==derecha)
	{
		ADMUX &= ~(1<<ADLAR);
	}
	else
	{
		ADMUX |= (1<<ADLAR);
	}
	switch (MUXADC)
	{
		case 0:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		break;
		case 1:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX0);
		break;
		case 2:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX1);
		break;
		case 3:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX1)|(1<<MUX0);
		break;
		case 4:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2);
		break;
		case 5:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX0);
		break;
		case 6:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX1);
		break;
		case 7:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		break;
		case 8:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX3);
		break;
		case VBG:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX3)|(1<<MUX2)|(1<<MUX1);
		break;
		case GND:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		break;
		default:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		break;
	}
	if (auto_trigger==activado)
	{
		ADCSRA |= (1<<ADATE);
	} 
	else
	{
		ADCSRA &= ~(1<<ADATE);
	}
	if (INT_ADC==activado)
	{
		ADCSRA |= (1<<ADIF);
	} 
	else
	{
		ADCSRA &= ~(1<<ADIF);
	}
	switch (prescaler)
	{
	case 2:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	break;
	case 4:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS1);
	break;
	case 8:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS1)|(1<<ADPS0);
	break;
	case 16:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS2);
	break;
	case 32:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
	break;
	case 64:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
	break;
	case 128:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	break;
	default:
	ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADCSRA |= (1<<ADPS2);
	break;
	}
	switch (trigger)
	{
		case free_running:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		break;
		case comparator:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS0);
		break;
		case ext_int:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS1);
		break;
		case TMR0_compare_match_A:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS1)|(1<<ADTS0);
		break;
		case TMR0_ovf:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS2);
		break;
		case TMR1_compare_match_B:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS2)|(1<<ADTS0);
		break;
		case TMR1_ovf:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS2)|(1<<ADTS1);
		break;
		case TMR1_capture:
		ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
		ADCSRB |= (1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0);
		break;
	}
	ADCSRA |=(1<<ADSC);
}