/*
 * PWM1B.c
 *
 * Created: 3/05/2026 21:01:31
 *  Author: Diego
 */ 
#include "PWM1B.h"
void PWM1B(uint8_t modo, int prescaler, uint8_t invert)
{
	DDRB |= (1<<DDB2); //Enciende el puerto correspondiente
	if (invert == invertido) //Configura si está o no invertido
	{
		TCCR1A &= ~((1<<COM1A0) | (1<<COM1A1));
		TCCR1A |= (1<<COM1A0) | (1<<COM1A1);
		} else {
		TCCR1A &= ~((1<<COM1A0) | (1<<COM1A1));
		TCCR1A |= (1<<COM1A1); //De forma predeterminada está en no invertido
	}
	switch (modo) //Configura el modo
	{
		case phase_correct_8:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1A |= (1<<WGM10);
		break;
		case phase_correct_9:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1A |= (1<<WGM11);
		break;
		case phase_correct_10:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		break;
		case fast_8:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM12);
		TCCR1A |= (1<<WGM10);
		break;
		case fast_9:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM12);
		TCCR1A |= (1<<WGM11);
		break;
		case fast_10:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM12);
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		break;
		case phase_frequency_I:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13);
		break;
		case phase_frequency_O:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13);
		TCCR1A |= (1<<WGM10);
		break;
		case phase_correct_I:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13);
		TCCR1A |= (1<<WGM11);
		break;
		case phase_correct_O:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13);
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		break;
		case fast_I:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13)|(1<<WGM12);
		TCCR1A |= (1<<WGM11);
		break;
		case fast_O:
		TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
		TCCR1B &= ~((1<<WGM13) | (1<<WGM12));
		TCCR1B |= (1<<WGM13)|(1<<WGM12);
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		break;
	}
	switch (prescaler) {	//Configura el prescaler
		case 8:
		TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
		TCCR1B |= (1<<CS11);
		break;
		case 64:
		TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
		TCCR1B |= (1<<CS11) | (1<<CS10);
		break;
		case 256:
		TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
		TCCR1B |= (1<<CS12);
		break;
		case 1024:
		TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
		TCCR1B |= (1<<CS12) | (1<<CS10);
		break;
		default:
		TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
		TCCR1B |= (1<<CS10);	//Prescaler de 1 predeterminado
		break;
	}
}