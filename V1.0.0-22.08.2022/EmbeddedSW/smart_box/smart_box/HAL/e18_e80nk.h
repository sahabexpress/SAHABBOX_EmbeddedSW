/*
 * e18_e80nk.h
 *
 * Created: 7/31/2022 11:03:51 AM
 *  Author: Muhammad_Ali
 */ 


#ifndef E18_E80NK_H_
#define E18_E80NK_H_
#include "gpio.h"

#define  E18E80NK_ENABLE    PORTA_PIN1
#define  E18E80NK_PIN       PORTE_PIN4

void E18E80NK_Init(gpioPin_t pin);
void E18E80NK_InitInterrupt(gpioExternalInterrupt_t pin);
uint8_t E18E80NK_ReadPolling(gpioPin_t pin);
uint8_t E18E80NK_ReadInterrupt();

void E18E80NK_Enable(gpioPin_t pin);
void E18E80NK_Disable(gpioPin_t pin);


#endif /* E18_E80NK_H_ */