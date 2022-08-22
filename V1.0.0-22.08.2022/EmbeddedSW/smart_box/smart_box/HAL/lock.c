/*
 * lock.c
 *
 * Created: 8/15/2022 1:55:11 PM
 *  Author: Muhammad_Ali
 */ 

#include "lock.h"

void Lock_Init(gpioPin_t pin){
	GPIO_PinInit(pin,OUTPUT);
}
void Lock_Open(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_HIGH);
}
void Lock_Close(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_LOW);
}

uint8_t Lock_EspRead(gpioPin_t pin){
	return GPIO_PinRead(pin);
}