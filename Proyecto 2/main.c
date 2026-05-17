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
#include <stdbool.h>
#include "My_Libraries/PWM0A.h"
#include "My_Libraries/PWM0B.h"
#include "My_Libraries/PWM1A.h"
#include "My_Libraries/PWM1B.h"
#include "My_Libraries/UART.h"
#include "My_Libraries/ADC.h"
#include "My_Libraries/EEPROM.h"

/****************************************/
// Variables y constantes
volatile uint8_t ADC_FLAG;
volatile uint8_t Lect_ADC_1;
volatile uint8_t Lect_ADC_2;
volatile uint8_t Lect_ADC_3;
volatile uint8_t Lect_ADC_4;
volatile uint8_t wait;
volatile uint8_t modo = 0;
volatile uint8_t UART_VAL;
volatile uint8_t MOTOR;
volatile uint8_t N_Byte = 1;
volatile uint8_t Buffer_RX;
bool direccion;

#define control_ADC 0
#define control_EEPROM 1
#define control_SERIAL 2
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
		switch (modo)
		{
			case control_ADC:
			UCSR0B &= ~(1<<TXCIE0);
			PORTB &= ~((1<<PORTB3)|(1<<PORTB4));
			PORTB |= (1<<PORTB3);
			OCR1A = (2000+(7.843*Lect_ADC_1));
			OCR1B = (2000+(7.843*Lect_ADC_2));
			OCR0A = Lect_ADC_3;
			OCR0B = Lect_ADC_4;
			PORTD &= ~((1<<PORTD2)|(1<<PORTD3));
			PORTD |= (1 << (direccion + 2));
			break;
			case control_EEPROM:
			UCSR0B |= (1<<TXCIE0);
			PORTB &= ~((1<<PORTB3)|(1<<PORTB4));
			PORTB |= (1<<PORTB4);
			if (MOTOR == 5)
			{
				switch (UART_VAL)
				{
					case 4:
						OCR1AH = EEPROMRead(0x010);
						OCR1AL = EEPROMRead(0x011);
						OCR1BH = EEPROMRead(0x016);
						OCR1BL = EEPROMRead(0x017);
						OCR0A  = EEPROMRead(0x012);
						OCR0B  = EEPROMRead(0x012);
					break;
					case 8:
						OCR1AH = EEPROMRead(0x014);
						OCR1AL = EEPROMRead(0x015);
						OCR1BH = EEPROMRead(0x010);
						OCR1BL = EEPROMRead(0x011);
						OCR0A  = EEPROMRead(0x012);
						OCR0B  = EEPROMRead(0x012);
					break;
					case 16:
						OCR1AH = EEPROMRead(0x010);
						OCR1AL = EEPROMRead(0x011);
						OCR1BH = EEPROMRead(0x016);
						OCR1BL = EEPROMRead(0x017);
						OCR0A  = EEPROMRead(0x013);
						OCR0B  = EEPROMRead(0x018);
					break;
					case 32:
						OCR1AH = EEPROMRead(0x010);
						OCR1AL = EEPROMRead(0x011);
						OCR1BH = EEPROMRead(0x016);
						OCR1BL = EEPROMRead(0x017);
						OCR0A  = EEPROMRead(0x018);
						OCR0B  = EEPROMRead(0x013);
					break;
				}
			}
			break;
			case control_SERIAL:
			UCSR0B |= (1<<TXCIE0);
			PORTB &= ~((1<<PORTB3)|(1<<PORTB4));
			PORTB |= (1<<PORTB3)|(1<<PORTB4);
			switch (MOTOR)
			{
				case 1:
				OCR1A = ((UART_VAL*11)+2000);
				break;
				case 2:
				OCR1B = ((UART_VAL*11)+2000);
				break;
				case 3:
				OCR0A = UART_VAL;
				break;
				case 4:
				OCR0A = UART_VAL;
				break;
			}
		}
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
	DDRD |= (1<<DDD2)|(1<<DDD3);
	PINC = (1<<PINC0);
	ADCSRA |=(1<<ADSC);
	PWM0A(fast, 1024, no_invertido);
	PWM0B(fast, 1024, no_invertido);
	PWM1A(fast_I, 8, no_invertido);
	PWM1B(fast_I, 8, no_invertido);
	initUART(simple, single, desactivado, activado, desactivado, activado, activado, 8, asincrono, desactivado, 1, desactivado, 416);
	PCICR = (1<<PCIE1);
	PCMSK1 = (1<<PCINT8)|(1<<PCINT9);
	EEPROMWrite(0x010, 0x0F);
	EEPROMWrite(0x011, 0xA0);	//90°
	EEPROMWrite(0x012, 0x00);	
	EEPROMWrite(0x013, 0xFF);
	EEPROMWrite(0x014, 0x0A);
	EEPROMWrite(0x015, 0x28);	//30°
	EEPROMWrite(0x016, 0x07);
	EEPROMWrite(0x017, 0xD0);	//0°
	EEPROMWrite(0X018, 0x80);
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
ISR(USART_RX_vect)
{
	Buffer_RX = UDR0;
	if (N_Byte==1)
	{
		MOTOR = Buffer_RX;
		N_Byte ++;
	} 
	else
	{
		UART_VAL = Buffer_RX;
		N_Byte = 1;
	}
}
ISR (PCINT1_vect)
{
	if (!(PINC&(1<<PINC0)))
	{
		if (modo ==control_SERIAL)
		{
			modo = control_ADC;
		}
		else
		{
			modo ++;
		}
	}
	if (!(PINC&(1<<PINC1)))
	{
		direccion = !direccion;
	}
}