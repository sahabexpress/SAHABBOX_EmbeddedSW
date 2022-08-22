/*
 * fan.h
 *
 * Created: 8/15/2022 1:54:47 PM
 *  Author: Muhammad_Ali
 */ 


#ifndef FAN_H_
#define FAN_H_

#include "gpio.h"

#define FAN_PIN  PORTB_PIN4

void Fan_Init(gpioPin_t pin);
void Fan_ON(gpioPin_t pin);
void Fan_OFF(gpioPin_t pin);



#endif /* FAN_H_ */