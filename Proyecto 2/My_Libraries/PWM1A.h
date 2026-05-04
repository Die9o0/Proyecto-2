/*
 * PWM1A.h
 *
 * Created: 3/05/2026 04:22:01
 *  Author: Diego
 */ 

#include <avr/io.h>
#ifndef PWM1A_H_
#define PWM1A_H_
#define fast 1
#define phase_correct 0
#define no_invertido 1
#define invertido 0
#define phase_correct_8 0
#define phase_correct_9 1
#define phase_correct_10 2
#define fast_8 4
#define fast_9 5
#define fast_10 6
#define phase_frequency_I 7
#define phase_frequency_O 8
#define phase_correct_I 9
#define phase_correct_O 10
#define fast_I 11
#define fast_O 12

void PWM1A(uint8_t modo, int prescaler, uint8_t  invert);



#endif /* PWM1A_H_ */