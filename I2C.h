#ifndef _I2C_H_
#define _I2C_H_
#include "stm32f407xx.h"

int init_i2c(I2C_TypeDef* i2c);
int init_i2c_gpio(GPIO_TypeDef* gpio,int pin);
void i2c_start(I2C_TypeDef* i2c);
void i2c_stop(I2C_TypeDef* i2c);
void i2c_write(I2C_TypeDef* i2c,uint8_t data);

#endif