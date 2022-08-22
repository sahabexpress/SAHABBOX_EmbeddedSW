/*
* GPIO.c
*
* Created: 7/21/2022 9:02:46 PM
*  Author: Muhammad_Ali
*/
#include "gpio.h"

static void(*INT0_Interrupt_Handler)(void);
static void(*INT1_Interrupt_Handler)(void);
static void(*INT2_Interrupt_Handler)(void);
static void(*INT3_Interrupt_Handler)(void);
static void(*INT4_Interrupt_Handler)(void);
static void(*INT5_Interrupt_Handler)(void);
static void(*INT6_Interrupt_Handler)(void);
static void(*INT7_Interrupt_Handler)(void);

void GPIO_PinInit(gpioPin_t pin,gpioPinDir_t dir){
	if((pin >= PORTA_PIN0)&&(pin <= PORTA_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRA,pin);
		else CLEAR_BIT(DDRA,pin);
		}else if((pin >= PORTB_PIN0)&&(pin <= PORTB_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRB,pin % PORTB_PIN0);
		else CLEAR_BIT(DDRB,pin % PORTB_PIN0);
		}else if((pin >= PORTC_PIN0)&&(pin <= PORTC_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRC,pin % PORTC_PIN0);
		else CLEAR_BIT(DDRC,pin % PORTC_PIN0);
		}else if((pin >= PORTD_PIN0)&&(pin <= PORTD_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRD,pin % PORTD_PIN0);
		else CLEAR_BIT(DDRD,pin % PORTD_PIN0);
		}else if((pin >= PORTE_PIN0)&&(pin <= PORTE_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRE,pin % PORTE_PIN0);
		else CLEAR_BIT(DDRE,pin % PORTE_PIN0);
		}else if((pin >= PORTF_PIN0)&&(pin <= PORTF_PIN7)){
		if(dir == OUTPUT)SET_BIT(DDRF,pin % PORTF_PIN0);
		else CLEAR_BIT(DDRF,pin % PORTF_PIN0);
	}
}

uint8_t GPIO_PinRead(gpioPin_t pin){
	uint8_t pin_value = 0;
	if((pin >= PORTA_PIN0)&&(pin <= PORTA_PIN7)){
		pin_value = READ_BIT(PINA , pin);
		}else if((pin >= PORTB_PIN0)&&(pin <= PORTB_PIN7)){
		pin_value = READ_BIT(PINB , pin % PORTB_PIN0);
		}else if((pin >= PORTC_PIN0)&&(pin <= PORTC_PIN7)){
		pin_value = READ_BIT(PINC , pin % PORTC_PIN0);
		}else if((pin >= PORTD_PIN0)&&(pin <= PORTD_PIN7)){
		pin_value = READ_BIT(PIND , pin % PORTD_PIN0);
		}else if((pin >= PORTE_PIN0)&&(pin <= PORTE_PIN7)){
		pin_value = READ_BIT(PINE , pin % PORTE_PIN0);
		}else if((pin >= PORTF_PIN0)&&(pin <= PORTF_PIN7)){
		pin_value = READ_BIT(PINF , pin % PORTF_PIN0);
	}
	return pin_value;
}

void GPIO_PinWrite(gpioPin_t pin,gpioPinVal_t value){
	if((pin >= PORTA_PIN0)&&(pin <= PORTA_PIN7)){
		if(value == HIGH)SET_BIT(PORTA,pin);
		else CLEAR_BIT(PORTA,pin);
		}else if((pin >= PORTB_PIN0)&&(pin <= PORTB_PIN7)){
		if(value == HIGH)SET_BIT(PORTB,pin % PORTB_PIN0);
		else CLEAR_BIT(PORTB,pin % PORTB_PIN0);
		}else if((pin >= PORTC_PIN0)&&(pin <= PORTC_PIN7)){
		if(value == HIGH)SET_BIT(PORTC,pin % PORTC_PIN0);
		else CLEAR_BIT(PORTC,pin % PORTC_PIN0);
		}else if((pin >= PORTD_PIN0)&&(pin <= PORTD_PIN7)){
		if(value == HIGH)SET_BIT(PORTD,pin % PORTD_PIN0);
		else CLEAR_BIT(PORTD,pin % PORTD_PIN0);
		}else if((pin >= PORTE_PIN0)&&(pin <= PORTE_PIN7)){
		if(value == HIGH)SET_BIT(PORTE,pin % PORTE_PIN0);
		else CLEAR_BIT(PORTE,pin % PORTE_PIN0);
		}else if((pin >= PORTF_PIN0)&&(pin <= PORTF_PIN7)){
		if(value == HIGH)SET_BIT(PORTF,pin % PORTF_PIN0);
		else CLEAR_BIT(PORTF,pin % PORTF_PIN0);
	}
}

void GPIO_PinInitInterrupt(gpioExternalInterrupt_t pin,gpioInterruptSense_t sense,void(*interruptHandler)(void)){
	SREG	|=(1<<7);
	SET_BIT(EIMSK,pin);
	if (pin == PORTD_PIN0_INT0){
		INT0_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRA,0);
			CLEAR_BIT(EICRA,1);
			}else if(sense == ANY_LOGICAL_CHANGE){
			/*reserved (not applicable)*/
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRA,0);
			SET_BIT(EICRA,1);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRA,0);
			SET_BIT(EICRA,1);
		}
		}else if(pin == PORTD_PIN1_INT1){
		INT1_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRA,2);
			CLEAR_BIT(EICRA,3);
			}else if(sense == ANY_LOGICAL_CHANGE){
			/*reserved (not applicable)*/
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRA,2);
			SET_BIT(EICRA,3);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRA,2);
			SET_BIT(EICRA,3);
		}
		}else if(pin == PORTD_PIN2_INT2){
		INT2_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRA,4);
			CLEAR_BIT(EICRA,5);
			}else if(sense == ANY_LOGICAL_CHANGE){
			/*reserved (not applicable)*/
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRA,4);
			SET_BIT(EICRA,5);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRA,4);
			SET_BIT(EICRA,5);
		}
		}else if(pin == PORTD_PIN3_INT3){
		INT3_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRA,6);
			CLEAR_BIT(EICRA,7);
			}else if(sense == ANY_LOGICAL_CHANGE){
			/*reserved (not applicable)*/
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRA,6);
			SET_BIT(EICRA,7);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRA,6);
			SET_BIT(EICRA,7);
		}
		}else if(pin == PORTE_PIN4_INT4){
		INT4_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRB,0);
			CLEAR_BIT(EICRB,1);
			}else if(sense == ANY_LOGICAL_CHANGE){
			SET_BIT(EICRB,0);
			CLEAR_BIT(EICRB,1);
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRB,0);
			SET_BIT(EICRB,1);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRB,0);
			SET_BIT(EICRB,1);
		}
		}else if(pin == PORTE_PIN5_INT5){
		INT5_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRB,2);
			CLEAR_BIT(EICRB,3);
			}else if(sense == ANY_LOGICAL_CHANGE){
			SET_BIT(EICRB,2);
			CLEAR_BIT(EICRB,3);
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRB,2);
			SET_BIT(EICRB,3);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRB,2);
			SET_BIT(EICRB,3);
		}
		}else if(pin == PORTE_PIN6_INT6){
		INT6_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRB,4);
			CLEAR_BIT(EICRB,5);
			}else if(sense == ANY_LOGICAL_CHANGE){
			SET_BIT(EICRB,4);
			CLEAR_BIT(EICRB,5);
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRB,4);
			SET_BIT(EICRB,5);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRB,4);
			SET_BIT(EICRB,5);
		}
		}else if(pin == PORTE_PIN7_INT7){
		INT7_Interrupt_Handler = interruptHandler;
		if(sense == LOW_LEVEL){
			CLEAR_BIT(EICRB,6);
			CLEAR_BIT(EICRB,7);
			}else if(sense == ANY_LOGICAL_CHANGE){
			SET_BIT(EICRB,6);
			CLEAR_BIT(EICRB,7);
			}else if(sense == FALLING_EDGE){
			CLEAR_BIT(EICRB,6);
			SET_BIT(EICRB,7);
			}else if(sense == RISING_EDGE){
			SET_BIT(EICRB,6);
			SET_BIT(EICRB,7);
		}
	}
}
	ISR (INT0_vect){
		INT0_Interrupt_Handler();
		SET_BIT(EIFR,0);
	}

	ISR (INT1_vect){
		INT1_Interrupt_Handler();
		SET_BIT(EIFR,1);
	}

	ISR (INT2_vect){
		INT2_Interrupt_Handler();
		SET_BIT(EIFR,2);
	}

	ISR (INT3_vect){
		INT3_Interrupt_Handler();
		SET_BIT(EIFR,3);
	}

	ISR (INT4_vect){
		INT4_Interrupt_Handler();
		SET_BIT(EIFR,4);
	}

	ISR (INT5_vect){
		INT5_Interrupt_Handler();
		SET_BIT(EIFR,5);
	}

	ISR (INT6_vect){
		INT6_Interrupt_Handler();
		SET_BIT(EIFR,6);
	}

	ISR (INT7_vect){
		INT7_Interrupt_Handler();
		SET_BIT(EIFR,7);
	}