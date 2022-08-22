/*
* uart.c
*
* Created: 7/21/2022 9:05:13 PM
*  Author: Muhammad_Ali
*/
#include "uart.h"

void UART_Init(UartChannel_t channel,uint16_t baud_rate,uint32_t cpu_clock){
	uint16_t ubrr = cpu_clock/16/baud_rate-1 ;
	/* Set baud rate */
	if(channel == UART0_TX_PE1_RX_PE0){
		UBRR0H = (unsigned char)(ubrr>>8);
		UBRR0L = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* Set frame format: 8data, 1stop bit */
		UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
		}else if(channel == UART1_TX_PD3_RX_PD2){
		UBRR1H = (unsigned char)(ubrr>>8);
		UBRR1L = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		UCSR1B = (1<<RXEN1)|(1<<TXEN1);
		/* Set frame format: 8data, 1stop bit */
		UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
	}
}

void UART_TransmitBlocking( UartChannel_t channel,uint8_t data ){
	if(channel == UART0_TX_PE1_RX_PE0){
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = data;
		}else if(channel == UART1_TX_PD3_RX_PD2){
		while ( !( UCSR1A & (1<<UDRE1)) );
		UDR1 = data;
	}
}

uint8_t UART_ReceiveBlocking( UartChannel_t channel ){
	uint8_t data = 0;
	if(channel == UART0_TX_PE1_RX_PE0){
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) );
		/* Get and return received data from buffer */
		data =  UDR0;
		}else if(channel == UART1_TX_PD3_RX_PD2){
		/* Wait for data to be received */
		while ( !(UCSR1A & (1<<RXC1)) );
		/* Get and return received data from buffer */
		data = UDR1;
	}
	return data;
}



void UART_TransmitNonBlocking( UartChannel_t channel,uint8_t data ){
	if(channel == UART0_TX_PE1_RX_PE0){
		/* Wait for empty transmit buffer */
		if ( !( UCSR0A & (1<<UDRE0)) ){
			UDR0 = data;
		}
		}else if(channel == UART1_TX_PD3_RX_PD2){
		/* Wait for empty transmit buffer */
		if( !( UCSR1A & (1<<UDRE1)) ){
			/* Put data into buffer, sends the data */
			UDR1 = data;
		}
	}
}

uint8_t UART_ReceiveNonBlocking( UartChannel_t channel ){
	uint8_t data = 0;
	if(channel == UART0_TX_PE1_RX_PE0){
		if ( !(UCSR0A & (1<<RXC0)) ){
			data =  UDR0;
		}
		}else if(channel == UART1_TX_PD3_RX_PD2){
		if( !(UCSR1A & (1<<RXC1)) ){
			data = UDR1;
		}
	}
	return data;
}


void UART_TransmitInterrupt( UartChannel_t channel,uint8_t data ){
	if(channel == UART0_TX_PE1_RX_PE0){
		UDR0 = data;
		}else if(channel == UART1_TX_PD3_RX_PD2){
		UDR1 = data;
	}
}

uint8_t UART_ReceiveInterrupt( UartChannel_t channel ){
	uint8_t data =0;
	if(channel == UART0_TX_PE1_RX_PE0){
		data = UDR0;
		}else if(channel == UART1_TX_PD3_RX_PD2){
		data = UDR1;
	}
	return data;
}

void UART_TransmitString(UartChannel_t channel ,uint8_t arr[],uint8_t size){
	int i;
	for(i = 0 ;i<size;i++){
		UART_TransmitBlocking(channel,arr[i]);
	}
}
static void(*UART0_RX_Handler)(void);
static void(*UART0_TX_Handler)(void);
static void(*UART0_UDRE_Handler)(void);
static void(*UART1_RX_Handler)(void);
static void(*UART1_TX_Handler)(void);
static void(*UART1_UDRE_Handler)(void);
void UART_InitInterrupt(UartChannel_t channel,UartInterruptSense_t sense,void(*Interrupt_Handler)(void)){
	SREG |=(1<<7);
	if(channel == UART0_TX_PE1_RX_PE0){
		if(sense == RX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR0B,RXCIE0);
			UART0_RX_Handler = Interrupt_Handler;
			}else if(sense == TX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR0B,TXCIE0);
			UART0_TX_Handler = Interrupt_Handler;
			}else if(sense == UDR_EMPTY_INTERRUPT){
			SET_BIT(UCSR0B,UDRIE0);
			UART0_UDRE_Handler = Interrupt_Handler;
		}
		}else if(channel == UART1_TX_PD3_RX_PD2){
		if(sense == RX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR1B,RXCIE1);
			UART1_RX_Handler = Interrupt_Handler;
			}else if(sense == TX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR1B,TXCIE1);
			UART1_TX_Handler = Interrupt_Handler;
			}else if(sense == UDR_EMPTY_INTERRUPT){
			SET_BIT(UCSR1B,UDRIE1);
			UART1_UDRE_Handler = Interrupt_Handler;
		}
	}
}

void UART_StopInterrupt(UartChannel_t channel,UartInterruptSense_t sense){
	if(channel == UART0_TX_PE1_RX_PE0){
		if(sense == RX_COMPLETE_INTERRUPT){
			CLEAR_BIT(UCSR0B,RXCIE0);
			}else if(sense == TX_COMPLETE_INTERRUPT){
			CLEAR_BIT(UCSR0B,TXCIE0);
			}else if(sense == UDR_EMPTY_INTERRUPT){
			CLEAR_BIT(UCSR0B,UDRIE0);
		}
		}else if(channel == UART1_TX_PD3_RX_PD2){
		if(sense == RX_COMPLETE_INTERRUPT){
			CLEAR_BIT(UCSR1B,RXCIE1);
			}else if(sense == TX_COMPLETE_INTERRUPT){
			CLEAR_BIT(UCSR1B,TXCIE1);
			}else if(sense == UDR_EMPTY_INTERRUPT){
			CLEAR_BIT(UCSR1B,UDRIE1);
		}
	}
}

void UART_EnableInterrupt(UartChannel_t channel,UartInterruptSense_t sense){
	if(channel == UART0_TX_PE1_RX_PE0){
		if(sense == RX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR0B,RXCIE0);
			}else if(sense == TX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR0B,TXCIE0);
			}else if(sense == UDR_EMPTY_INTERRUPT){
			SET_BIT(UCSR0B,UDRIE0);
		}
		}else if(channel == UART1_TX_PD3_RX_PD2){
		if(sense == RX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR1B,RXCIE1);
			}else if(sense == TX_COMPLETE_INTERRUPT){
			SET_BIT(UCSR1B,TXCIE1);
			}else if(sense == UDR_EMPTY_INTERRUPT){
			SET_BIT(UCSR1B,UDRIE1);
		}
	}
}

ISR (USART0_RX_vect){
	UART0_RX_Handler();
}

ISR (USART0_TX_vect){
	UART0_TX_Handler();
}

ISR (USART0_UDRE_vect){
	UART0_UDRE_Handler();
}

ISR (USART1_RX_vect){
	UART1_RX_Handler();
}

ISR (USART1_TX_vect){
	UART0_TX_Handler();
}

ISR (USART1_UDRE_vect){
	UART1_UDRE_Handler();
}