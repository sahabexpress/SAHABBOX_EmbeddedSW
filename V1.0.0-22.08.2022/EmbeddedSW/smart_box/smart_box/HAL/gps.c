/*
 * gps.c
 *
 * Created: 7/22/2022 6:22:52 PM
 *  Author: Muhammad_Ali
 */ 
#include "gps.h"

char buf[100];
volatile char ind=0,flag,stringReceived;
char gpgga[]={'$','G','P','G','G','A'};
static UartChannel_t gps_channel;

void GPS_Handler(void){
	 char ch=UART_ReceiveInterrupt(gps_channel);
	 buf[ind]=ch;
	 
	 ind++;
	 if(ind<7)
	 {
		 if(buf[ind-1] != gpgga[ind-1]){               // $GPGGA
		 ind=0;
		 }
		  
	 }
	 if(ind>=50)
	 stringReceived=1;
}

void GPS_Init(UartChannel_t channel,uint16_t baud_rate,uint32_t cpu_clock){
	 gps_channel = channel;
	UART_Init(channel,baud_rate,cpu_clock);
	UART_InitInterrupt(channel,RX_COMPLETE_INTERRUPT,GPS_Handler);
}
void GPS_Longitude(uint8_t Longitude[12]){
	 for(int i=30;i<43;i++)
	 {
		 Longitude[i-30]=buf[i];
		/* if(i==41)
		 {
			Longitude[i]=' ';
			 i++;
		 }*/
}
}
void GPS_Latitude(uint8_t Latitude[12]){
for(int i=17;i<29;i++){
	Latitude[i-17]=buf[i];
// 	if(i==24){
// 		Latitude[i]= ' ';
// 		i++;
// 	}
}	
}

uint8_t GPS_ReceivedDataFlag(){
	return stringReceived;
}

void GPS_ReceivedDataFlagClear(){
	stringReceived = 0;
}


void GPS_Enable(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_HIGH);
}

void GPS_Disable(gpioPin_t pin){
	GPIO_PinWrite(pin,PIN_LOW);
}