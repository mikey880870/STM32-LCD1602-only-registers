#include "helper_functions.h"
#include "stm32f407xx.h"

int init_led(GPIO_TypeDef* gpio,int LED_pin){
	if(gpio==GPIOD){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	}
	else{
		return -1;
	} 
	gpio->MODER &= ~(0x11 << (2*LED_pin));
	gpio->MODER |= (0x01 << (2*LED_pin));
	
	return 0;
}

int read_gpio(GPIO_TypeDef* gpio,int pin){
	return (gpio-> IDR >> pin) & 1;       
}

void set_gpio(GPIO_TypeDef* gpio,int pin){
	gpio->BSRR |= (1 << pin);
}

void reset_gpio(GPIO_TypeDef* gpio,int pin){                                                                                                                
	gpio->BSRR |= (1 << (pin + 16));
}

void delay_without_interrupt(int msec){
	int loop_cnt = 500*msec;
	while(loop_cnt){
		loop_cnt--;
	}
	return;
}