#include "I2C.h"
#include "stm32f407xx.h"

int init_i2c(I2C_TypeDef* i2c){
	if(i2c == I2C1){
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;      // enable clock
	}
	else{
		return -1;
	}
	i2c->CR1 |= (1 << I2C_CR1_SWRST_Pos);   	// reset i2c
	i2c->CR1 &= ~(1 << I2C_CR1_SWRST_Pos);  	// normal operation
	
	i2c->CR2 |= (16U << I2C_CR2_FREQ_Pos);  	// 2 Mhz <= X <=  50Mhz
	i2c->CCR &= ~(1 << I2C_CCR_FS_Pos);     	// 0 = stanard mode
	i2c->CCR |= (80U<<I2C_CCR_CCR_Pos);     	// CCR=Thigh/TPCLK1=0.5*(1/100kHz)/(1/16MHz)=80
	i2c->TRISE |= (17<<I2C_TRISE_TRISE_Pos);	// raise time
	
	return 0;
}

void i2c_start(I2C_TypeDef* i2c){
	i2c->CR1 |= (1 << I2C_CR1_PE_Pos);          // Peripheral enable
	i2c->CR1 |= (1 << I2C_CR1_ACK_Pos);         // enable ack 
	i2c->CR1 |= (1 << I2C_CR1_START_Pos);
	while(!(i2c->SR1 & I2C_SR1_SB));
}

void i2c_stop(I2C_TypeDef* i2c){
	i2c->CR1 |= (1<<I2C_CR1_STOP_Pos);
}

int init_i2c_gpio(GPIO_TypeDef* gpio,int pin){
	if(gpio == GPIOB){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	}
	else{
		return -1;
	}
	for(int i = 0;i <= 1;i++){
		gpio -> MODER &= ~(0b11 << (2*(pin + i)));   
		gpio -> MODER |= (0b10 << (2*(pin + i)));   // AF MODE
	}
	
	gpio -> OTYPER |= ((1 << GPIO_OTYPER_OT6_Pos) | (1 << GPIO_OTYPER_OT7_Pos));    	// open drain
	gpio -> PUPDR |= ~((3U << GPIO_PUPDR_PUPD6_Pos) | (3U << GPIO_PUPDR_PUPD7_Pos));    // no pull up pull down
	
	gpio -> AFR[0] |= (4U << GPIO_AFRL_AFSEL6_Pos);   // AF4 = i2c
	gpio -> AFR[0] |= (4U << GPIO_AFRL_AFSEL7_Pos);
	
	return 0;
}

void i2c_write(I2C_TypeDef* i2c,uint8_t data) {
	while(!(i2c->SR1 & I2C_SR1_TXE));
    i2c->DR = data; 
    while (!(i2c->SR1 & I2C_SR1_BTF)); 
}