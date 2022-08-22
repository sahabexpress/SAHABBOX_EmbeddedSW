/*
 * esp.h
 *
 * Created: 8/15/2022 2:22:42 PM
 *  Author: Muhammad_Ali
 */ 

#include "i2c.h"

#ifndef ESP_H_
#define ESP_H_

void ESP_CommunicationInit(void);
void ESP_CommunicationWriteByte(uint8_t byte);
void ESP_CommunicationWriteArray(uint8_t arr[] , uint8_t size);

#endif /* ESP_H_ */