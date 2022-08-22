/*
* hw_types.h
*
* Created: 7/21/2022 9:37:33 PM
*  Author: Muhammad_Ali
*/


#ifndef HW_TYPES_H_
#define HW_TYPES_H_
#include <stdint.h>
#define HIGH 1
#define LOW  0

#define SET_BIT(REG,BIT)   (REG |= (1<<BIT)) 
#define	CLEAR_BIT(REG,BIT) (REG &= ~(1<<BIT))
#define READ_BIT(REG,BIT)  ((REG &(1<<BIT))>>BIT)
static inline void write_bit(uint8_t reg,uint8_t pin, uint8_t value){
	if(value == HIGH){
		reg |= (1<< pin);
		}else if(value == LOW){
		reg &= ~(1<< pin);
	}
}

static inline uint8_t read_bit(uint8_t reg, uint8_t pin){
 uint8_t value = 0;
 value = ((reg & (1<< pin))>>pin);
return value;
}


#endif /* HW_TYPES_H_ */