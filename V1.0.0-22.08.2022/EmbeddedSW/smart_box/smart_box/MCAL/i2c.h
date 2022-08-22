/*
 * i2c.h
 *
 * Created: 7/21/2022 9:04:42 PM
 *  Author: Muhammad_Ali
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/delay.h>

void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t v_i2cData_u8);
uint8_t I2C_Read(uint8_t v_ackOption_u8);


#endif /* I2C_H_ */