/*
 * lock.h
 *
 * Created: 8/15/2022 1:55:28 PM
 *  Author: Muhammad_Ali
 */ 


#ifndef LOCK_H_
#define LOCK_H_

#include "gpio.h"

#define LOCK_PIN        PORTC_PIN1
#define LOCK_ESP_PIN    PORTE_PIN5 //or  PORTE_PIN6

void Lock_Init(gpioPin_t pin);
void Lock_Open(gpioPin_t pin);
void Lock_Close(gpioPin_t pin);
uint8_t Lock_EspRead(gpioPin_t pin);



#endif /* LOCK_H_ */