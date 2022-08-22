/*
 * e18_e80nk.c
 *
 * Created: 7/27/2022 6:08:57 PM
 *  Author: Muhammad_Ali
 */ 

#include "e18_e80nk.h"

static uint8_t state = 0;
void E18E80NK_InterruptHandler(void){
	state = 1;
}

void E18E80NK_Init(gpioPin_t pin){
	GPIO_PinInit(pin,INPUT);
}
void E18E80NK_InitInterrupt(gpioExternalInterrupt_t pin){
	 GPIO_PinInitInterrupt(pin,FALLING_EDGE,E18E80NK_InterruptHandler);
}
uint8_t E18E80NK_ReadPolling(gpioPin_t pin){
	if(GPIO_PinRead(pin)) return 0;
	else return 1;
}
uint8_t E18E80NK_ReadInterrupt(){
	uint8_t temp = state;
	state = 0;
	return temp;
}

void E18E80NK_Enable(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_HIGH);
}
void E18E80NK_Disable(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_LOW);
}