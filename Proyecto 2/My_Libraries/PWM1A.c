/*
 * PWM1A.c
 *
 * Created: 3/05/2026 04:22:12
 *  Author: Diego
 */ 
#include "PWM1A.h"
void PWM1A(uint8_t modo, int prescaler, uint8_t invert)
{
	DDRB |= (1<<DDB1); //Enciende el puerto correspondiente
	if (invert == invertido) //Configura si está o no invertido
	{
		TCCR1A &= ~((1<<COM1B0) | (1<<COM1B1));
		TCCR1A |= (1<<COM1B0) | (1<<COM1B1);
		} else {
		TCCR1A &= ~((1<<COM1B0) | (1<<COM1B1));
		TCCR1A |= (1<<COM1B1); //De forma predeterminada está en no invertido
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