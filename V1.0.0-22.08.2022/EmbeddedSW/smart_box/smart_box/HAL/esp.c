/*
 * esp.c
 *
 * Created: 8/15/2022 2:22:55 PM
 *  Author: Muhammad_Ali
 */ 
#include "esp.h"

void ESP_CommunicationInit(void){
	I2C_Init();
}

void ESP_CommunicationWriteByte(uint8_t byte){
	I2C_Start();
	I2C_Write(byte);
	I2C_Stop();
}

void ESP_CommunicationWriteArray(uint8_t *arr , uint8_t size){
	int i;
	for (i = 0 ; i< size ; i++){
		 ESP_CommunicationWriteByte(arr[i]);
	}
}
