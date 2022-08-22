/*
* uart.h
*
* Created: 7/21/2022 9:05:32 PM
*  Author: Muhammad_Ali
*/


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hw_types.h"
#define CPU_FREQ  1000000

typedef enum{
	UART0_TX_PE1_RX_PE0,
	UART1_TX_PD3_RX_PD2
}UartChannel_t;

typedef enum{
	RX_COMPLETE_INTERRUPT,
	TX_COMPLETE_INTERRUPT,
	UDR_EMPTY_INTERRUPT,
}UartInterruptSense_t;

void UART_Init(UartChannel_t channel,uint16_t baud_rate,uint32_t cpu_clock);

void UART_TransmitBlocking( UartChannel_t channel,uint8_t data );
uint8_t UART_ReceiveBlocking( UartChannel_t channel );

void UART_TransmitNonBlocking( UartChannel_t channel,uint8_t data );/*not tested*/
uint8_t UART_ReceiveNonBlocking( UartChannel_t channel );/*not tested*/

void UART_InitInterrupt(UartChannel_t channel,UartInterruptSense_t sense,void(*Interrupt_Handler)(void));
uint8_t UART_ReceiveInterrupt( UartChannel_t channel );
void UART_TransmitInterrupt( UartChannel_t channel,uint8_t data );

void UART_EnableInterrupt(UartChannel_t channel,UartInterruptSense_t sense);
void UART_StopInterrupt(UartChannel_t channel,UartInterruptSense_t sense);

void UART_TransmitString(UartChannel_t channel ,uint8_t arr[],uint8_t size);
#endif /* UART_H_ */