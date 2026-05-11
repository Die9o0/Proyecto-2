/*
 * Proyecto_2.c
 *
 * Created: 26/04/26
 * Author: Diego Camey
 * Description: Código para controlar un rover con 2 motores DC y 2 servos mediante señales analógicas, comunicación serial, y EEPROM
 */
/****************************************/
// Encabezado (Libraries)
#include <avr/io.h>
#include <avr/interrupt.h>
#include "My_Libraries/PWM0A.h"
#include "My_Libraries/PWM0B.h"
#include "My_Libraries/PWM1A.h"
#include "My_Libraries/PWM1B.h"
#include "My_Libraries/UART.h"
#include "My_Libraries/ADC.h"

/****************************************/
// Variables y constantes
volatile uint8_t ADC_FLAG;
volatile uint8_t Lect_ADC_1;
volatile uint8_t Lect_ADC_2;
volatile uint8_t Lect_ADC_3;
volatile uint8_t Lect_ADC_4;
volatile uint8_t wait;

/****************************************/
// Function prototypes
void setup();
/****************************************/
// Main Function
int main(void)
{
	
	cli();
	setup();
	sei();
	while (1)
	{
		OCR1A = (2000+(7.84313*Lect_ADC_1));
		OCR1B = (2000+(7.84313*Lect_ADC_2));
		OCR0A = L ect_ADC_3;
		OCR0B = Lect_ADC_4;
	}
}
/****************************************/
// NON-Interrupt subroutines
void setup()
{
	//Sin prescaler, 16MHz
	CLKPR = 0x00;
	initADC(AVCC, izquierda, 7, activado, activado, 16, free_running);
	ICR1 = 39999;
	DDRC = 0x00;
	ADCSRA |=(1<<ADSC);
	PWM0A(fast, 1024, no_invertido);
	PWM0B(fast, 1024, no_invertido);
	PWM1A(fast_I, 8, no_invertido);
	PWM1B(fast_I, 8, no_invertido);
	initUART(simple, single, desactivado, activado, desactivado, activado, activado, 8, asincrono, desactivado, 1, desactivado, 416);
}
/****************************************/
// Interrupt routines
ISR(ADC_vect)
{
	if (wait!=2)
	{
		wait++;
		return;
	}
	switch (ADC_FLAG)
	{
		case 0:
		Lect_ADC_1 = ADCH; //Guarda la lectura
		ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); //Apaga el MUX
		ADMUX |= (1<<MUX2) | (1<<MUX1);		//MUX 6
		break;
		case 1:
		Lect_ADC_2 = ADCH;
		ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); //Apaga el MUX
		ADMUX |= (1<<MUX2) | (1<<MUX0);		//MUX 5
		break;
		case 2:
		Lect_ADC_3 = ADCH;
		ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); //Apaga el MUX
		ADMUX |= (1<<MUX2);					//MUX 4
		break;
		case 3:
		Lect_ADC_4 = ADCH;
		ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); //Apaga el MUX
		ADMUX |= (1<<MUX2)	| (1<<MUX1) | (1<<MUX0); //Enciende mux 7
		break;
	}
	ADC_FLAG ++;	//Aumenta el contador del MUX
	if (ADC_FLAG==4) //Reinicia el contador del MUX
	{
		ADC_FLAG=0;
	}
	wait =0;
}