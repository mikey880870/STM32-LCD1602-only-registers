#ifndef _LCD_H_
#define _LCD_H_
#include "stm32f407xx.h"

void lcd_send_cmd(I2C_TypeDef* i2c,int cmd);
void lcd_send_data(I2C_TypeDef* i2c,int cmd);
void lcd_init(I2C_TypeDef* i2c);
void lcd_send_string (char *str);
void lcd_GotoXY(int column, int line);
void lcd_clear(I2C_TypeDef* i2c);

#endif
