#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include "stm32f407xx.h"
int init_led(GPIO_TypeDef* gpio,int LED_pin); 
void set_gpio(GPIO_TypeDef* gpio,int pin);
void reset_gpio(GPIO_TypeDef* gpio,int pin);
void delay_without_interrupt(int msec);
int read_gpio(GPIO_TypeDef* gpio,int pin);

#endif
