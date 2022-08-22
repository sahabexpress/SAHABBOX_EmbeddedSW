/*
 * gps.h
 *
 * Created: 7/22/2022 6:22:36 PM
 *  Author: Muhammad_Ali
 */ 


#ifndef GPS_H_
#define GPS_H_
#include "uart.h"
#include "gpio.h"

#define GPS_CHANNEL    UART0_TX_PE1_RX_PE0
#define GPS_ENABLE     PORTA_PIN2

void GPS_Init(UartChannel_t channel,uint16_t baud_rate,uint32_t cpu_clock);
void GPS_Longitude(uint8_t Longitude[12]);
void GPS_Latitude(uint8_t Latitude[12]);

uint8_t GPS_ReceivedDataFlag();
void GPS_ReceivedDataFlagClear();

void GPS_Enable(gpioPin_t pin);
void GPS_Disable(gpioPin_t pin);
#endif /* GPS_H_ */