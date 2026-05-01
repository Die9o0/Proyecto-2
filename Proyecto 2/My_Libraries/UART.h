/*
 * UART.h
 *
 * Created: 28/04/2026 01:20:42
 *  Author: Diego
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#define doble 1
#define simple 0
#define multi 1
#define single 0
#define activado 1
#define desactivado 0


void initUART(uint8_t speed, uint8_t multiple_p, uint8_t INT_TX, uint8_t INT_RX, uint8_t INT_UDR0, uint8_t recibir, uint8_t transmitir);
void writeChar(char caracter);
void writeString(char* string);


#endif /* UART_H_ */