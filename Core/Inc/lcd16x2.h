/*
 * lcd16x2.h
 *
 *  Created on: Oct 27, 2020
 *      Author: ipizf
 */

#ifndef INC_LCD16X2_H_
#define INC_LCD16X2_H_

#include "stm32f1xx_hal.h"

void lcd_init(void);

void lcd_write_data(char data);
void lcd_write_int(int data);
void lcd_write_command(char data);

void lcd_custom_char(char loc,char *msg);

void lcd_set_cursor(char lin, char col);
void lcd_clear(void);
void lcd_write_string(char *str);

#endif /* INC_LCD16X2_H_ */
