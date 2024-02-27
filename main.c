#include "stm32f407xx.h"
#include "I2C.h"
#include "lcd.h"
#include "helper_functions.h"
#include "stdio.h"
#include "string.h"

#define i2c I2C1
#define i2c_gpio GPIOB
#define i2c_pin 6
#define Slave_address_lcd 0x27

int main(void){
	if(init_i2c(i2c) != 0){
		return -1;
	}
	
	if(init_i2c_gpio(i2c_gpio,i2c_pin) != 0){
		return -1;
	}

	i2c_start(i2c);

	uint8_t tempAddress = 0;
	tempAddress = (Slave_address_lcd<<1);		// Make space on the 0th bit for R/W
	tempAddress &= ~(1<<0);						// Clear 0th bit for write

	i2c->DR = tempAddress; 
	while(!(i2c->SR1 & I2C_SR1_ADDR));
	uint8_t temp = i2c->SR1 | i2c->SR2;  // read SR1 and SR2 to clear the ADDR bit
	
	//  ACK 
	while((I2C1->SR1 & I2C_SR1_AF)){
		delay_without_interrupt(2000);
		return -1;
	}
	
	lcd_init(i2c);
	delay_without_interrupt(3000);
	lcd_GotoXY(3,1);
	delay_without_interrupt(3000);
	char lcd_string[20] = "hello";
	lcd_send_string(lcd_string);
	delay_without_interrupt(3000);
	lcd_GotoXY(3,0);
	delay_without_interrupt(3000);
    strcpy(lcd_string, "stm32");
	lcd_send_string(lcd_string);


	return 0;
}
