/*
 * system.c
 *
 * Created: 8/15/2022 2:48:44 PM
 *  Author: Muhammad_Ali
 */ 
#include "system.h"

char tempArr[4]={0};

uint8_t GPS_LongitudeArr[13];
uint8_t GPS_LatitudeArr[13];

uint8_t IR_status = 0;

uint8_t fan_status = 0;

void System_Init(void){
	ds18b20_Disable(DS18B20_ENABLE);
	
	E18E80NK_Init(E18E80NK_PIN);
	E18E80NK_Disable(E18E80NK_PIN);
	
	ESP_CommunicationInit();
	
	Fan_Init(FAN_PIN);
	Fan_OFF(FAN_PIN);
	
	GPS_Init(GPS_CHANNEL,9600,8000000);
	GPS_Enable(GPS_ENABLE);
	
	Lock_Init(LOCK_PIN);
	Lock_Close(LOCK_PIN);
}

static void System_GetTemperature(){
	double temp = 0;
	ds18b20_Enable(DS18B20_ENABLE);
	temp = ds18b20_gettemp();
	if(temp > TEMP_TO_START_FAN){
		fan_status = 1;
	}else{
		fan_status =0;
	}
	 itoa(temp,tempArr,10);
	ds18b20_Disable(DS18B20_ENABLE);
}

static void System_ReadIR(){
	E18E80NK_Enable(E18E80NK_ENABLE);
	IR_status = E18E80NK_ReadPolling(E18E80NK_PIN);
    E18E80NK_Disable(E18E80NK_ENABLE);
}

static void System_ReadGPS(){
	if(GPS_ReceivedDataFlag()){
		GPS_Disable(GPS_ENABLE);
		GPS_Latitude(GPS_LatitudeArr);
		GPS_Longitude(GPS_LongitudeArr);
		GPS_ReceivedDataFlagClear();
		UART_StopInterrupt(UART0_TX_PE1_RX_PE0,RX_COMPLETE_INTERRUPT);
		System_GetTemperature();
		UART_EnableInterrupt(UART0_TX_PE1_RX_PE0,RX_COMPLETE_INTERRUPT);
		GPS_Enable(GPS_ENABLE);
	}
}

void System_CtrlLock(){
	uint8_t lock_status = 0;
	lock_status = Lock_EspRead(LOCK_ESP_PIN);
	if(lock_status == HIGH){
		Lock_Open(LOCK_PIN);
		System_ReadIR();
	}else{
		Lock_Close(LOCK_PIN);
	}
	
	
}


void System_SmartBox(){

	System_ReadGPS();
	
	GPS_Disable(GPS_ENABLE);
	
	ESP_CommunicationWriteByte('A');
	ESP_CommunicationWriteArray(GPS_LongitudeArr,13);
	ESP_CommunicationWriteByte('B');

	ESP_CommunicationWriteByte('C');
	ESP_CommunicationWriteArray(GPS_LatitudeArr,13);
	ESP_CommunicationWriteByte('D');
	GPS_Enable(GPS_ENABLE);
	
	System_CtrlLock();
	ESP_CommunicationWriteByte('E');
	if(IR_status == HIGH){
		ESP_CommunicationWriteByte('Y');
	}else{
		ESP_CommunicationWriteByte('N');
	}
	ESP_CommunicationWriteByte('F');
	_delay_us(10);
	ESP_CommunicationWriteByte('G');
	ESP_CommunicationWriteArray((uint8_t*)tempArr,4);
	ESP_CommunicationWriteByte('H');
	_delay_us(10);
	
	if(fan_status == HIGH){
		Fan_ON(FAN_PIN);
	}else{
		Fan_OFF(FAN_PIN);
	}
}
