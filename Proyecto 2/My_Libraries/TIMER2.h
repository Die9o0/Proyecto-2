/*
 * TIMER2.h
 *
 * Created: 1/05/2026 00:24:25
 *  Author: Diego
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_
#include <avr/io.h>
#define activado 1
#define desactivado 0
#define CTC 1




void initTIMER2 (uint8_t modo, uint16_t prescaler, uint8_t OCR2A_value, uint8_t OCR2B_value, uint8_t INT_OC2A, uint8_t INT_OC2B, uint8_t INT_OVF);
#endif /* TIMER2_H_ */