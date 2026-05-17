/*
 * EEPROM.h
 *
 * Created: 11/05/2026 00:17:46
 *  Author: Diego
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#define borrar 0
#define escribir 1
#define borrar_escribir 2
#define activado 1
#define desactivado 0

void initEEPROM(uint8_t modo, uint8_t EEPROM_INT);
void EEPROMWrite (uint16_t direccion, uint8_t dato);
uint8_t EEPROMRead (uint16_t direccion);

#endif /* EEPROM_H_ */