/*
 * fan.c
 *
 * Created: 8/15/2022 1:54:59 PM
 *  Author: Muhammad_Ali
 */ 

#include "gpio.h"

void Fan_Init(gpioPin_t pin){
	GPIO_PinInit(pin,OUTPUT);
}
void Fan_ON(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_HIGH);
}
void Fan_OFF(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_LOW);
}