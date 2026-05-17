/*
 * EEPROM.c
 *
 * Created: 11/05/2026 00:18:11
 *  Author: Diego
 */ 
#include "EEPROM.h"

void initEEPROM(uint8_t modo, uint8_t EEPROM_INT)
{
	switch (modo)
	{
		case borrar:
		EECR &= ~((1<<EEPM1)|(1<<EEPM0));
		EECR |= (1<<EEPM0);
		break;
		case escribir:
		EECR &= ~((1<<EEPM1)|(1<<EEPM0));
		EECR |= (1<<EEPM1);
		break;
		default:
		EECR &= ~((1<<EEPM1)|(1<<EEPM0));
		break;
	}
	if (EEPROM_INT==activado)
	{
		EECR |= (1<<EERIE);
	} 
	else
	{
		EECR &=  ~(1<<EERIE);
	}
}

void EEPROMWrite (uint16_t direccion, uint8_t dato)
{
	while (EECR & (1<<EEPE));
	EEAR = direccion;
	EEDR = dato;
	cli();
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
	sei();
}
uint8_t EEPROMRead (uint16_t direccion)
{
	while (EECR & (1<<EEPE));
	EEAR = direccion;
	EECR |= (1<<EERE);
	return EEDR;
}