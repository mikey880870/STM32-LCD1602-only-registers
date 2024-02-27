#include "lcd.h"
#include "I2C.h"
#include "stm32f407xx.h"


void lcd_send_cmd(I2C_TypeDef* i2c,int cmd){
	int data_u, data_l;

    data_u = (cmd & 0xF0);
    data_l = ((cmd << 4) & 0xF0);

    i2c_write(i2c,data_u | 0x0C); 
    i2c_write(i2c,data_u | 0x08); 

    i2c_write(i2c,data_l | 0x0C); 
    i2c_write(i2c,data_l | 0x08); 

}

void lcd_send_data(I2C_TypeDef* i2c,int cmd){
	int data_u, data_l;

    data_u = (cmd & 0xF0);
    data_l = ((cmd << 4) & 0xF0);

    i2c_write(i2c,data_u | 0x0D); 
    i2c_write(i2c,data_u | 0x09); 

    i2c_write(i2c,data_l | 0x0D); 
    i2c_write(i2c,data_l | 0x09); 
}

void lcd_init(I2C_TypeDef* i2c){
	lcd_send_cmd (i2c,0x30);
	lcd_send_cmd (i2c,0x30);
	lcd_send_cmd (i2c,0x30);
	lcd_send_cmd (i2c,0x20);  // 4bit mode

	// dislay initialisation
	lcd_send_cmd (i2c,0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	lcd_send_cmd (i2c,0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	lcd_send_cmd (i2c,0x01); // clear display
	lcd_send_cmd (i2c,0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	lcd_send_cmd (i2c,0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_clear(I2C_TypeDef* i2c){
	lcd_send_cmd (i2c,0x01); 	// clear display
}

void lcd_send_string(char *str)
{
    while(*str)
    {
        lcd_send_data(I2C1,*str++);
    }
}

void lcd_GotoXY(int column, int line) {
    lcd_send_cmd(I2C1,(column+(line<<6))|0x80);  // Set DDRAM address with coordinates
}
