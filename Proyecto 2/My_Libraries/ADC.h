/*
 * ADC.h
 *
 * Created: 2/05/2026 00:35:06
 *  Author: Diego
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>

#define AREF 0
#define AVCC 1
#define interno 2
#define derecha 1
#define izquierda 0
#define VBG 9
#define GND 10
#define activado 1
#define desactivado 0
#define free_running 0
#define	comparator 1
#define ext_int 2
#define TMR0_compare_match_A 3
#define TMR0_ovf 4
#define TMR1_compare_match_B 5
#define TMR1_ovf 6
#define TMR1_capture 7

void initADC (uint8_t referencia, uint8_t justificacion, uint8_t MUXADC, uint8_t auto_trigger, uint8_t INT_ADC, uint8_t prescaler, uint8_t trigger);

#endif /* ADC_H_ */