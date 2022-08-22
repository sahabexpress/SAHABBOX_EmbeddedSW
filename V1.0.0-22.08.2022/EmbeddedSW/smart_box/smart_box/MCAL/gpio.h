/*
* gpio.h
*
* Created: 7/21/2022 9:03:13 PM
*  Author: Muhammad_Ali
*/


#ifndef GPIO_H_
#define GPIO_H_

#include "hw_types.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum{
	PORTA_PIN0,
	PORTA_PIN1,
	PORTA_PIN2,
	PORTA_PIN3,
	PORTA_PIN4,
	PORTA_PIN5,
	PORTA_PIN6,
	PORTA_PIN7,

	PORTB_PIN0,
	PORTB_PIN1,
	PORTB_PIN2,
	PORTB_PIN3,
	PORTB_PIN4,
	PORTB_PIN5,
	PORTB_PIN6,
	PORTB_PIN7,

	PORTC_PIN0,
	PORTC_PIN1,
	PORTC_PIN2,
	PORTC_PIN3,
	PORTC_PIN4,
	PORTC_PIN5,
	PORTC_PIN6,
	PORTC_PIN7,

	PORTD_PIN0,
	PORTD_PIN1,
	PORTD_PIN2,
	PORTD_PIN3,
	PORTD_PIN4,
	PORTD_PIN5,
	PORTD_PIN6,
	PORTD_PIN7,

	PORTE_PIN0,
	PORTE_PIN1,
	PORTE_PIN2,
	PORTE_PIN3,
	PORTE_PIN4,
	PORTE_PIN5,
	PORTE_PIN6,
	PORTE_PIN7,

	PORTF_PIN0,
	PORTF_PIN1,
	PORTF_PIN2,
	PORTF_PIN3,
	PORTF_PIN4,
	PORTF_PIN5,
	PORTF_PIN6,
	PORTF_PIN7,
}gpioPin_t;

typedef enum{
	INPUT,
	OUTPUT
}gpioPinDir_t;

typedef enum{
	PIN_LOW,
	PIN_HIGH
}gpioPinVal_t;

typedef enum{
	PORTD_PIN0_INT0,
	PORTD_PIN1_INT1,
	PORTD_PIN2_INT2,
	PORTD_PIN3_INT3,

	PORTE_PIN4_INT4,
	PORTE_PIN5_INT5,
	PORTE_PIN6_INT6,
	PORTE_PIN7_INT7,
}gpioExternalInterrupt_t;

typedef enum{
	LOW_LEVEL,
	ANY_LOGICAL_CHANGE, /*for INT4 to INT7 only*/
	FALLING_EDGE,
	RISING_EDGE,
}gpioInterruptSense_t;

void GPIO_PinInit(gpioPin_t pin,gpioPinDir_t dir);
uint8_t GPIO_PinRead(gpioPin_t pin);
void GPIO_PinWrite(gpioPin_t pin ,gpioPinVal_t value);

void GPIO_PinInitInterrupt(gpioExternalInterrupt_t pin,gpioInterruptSense_t sense,void(*interruptHandler)(void));

#endif /* GPIO_H_ */