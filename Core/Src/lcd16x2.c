/*
 * lcd16x2.c
 *
 *  Created on: Oct 27, 2020
 *      Author: ipizf
 */
#include "lcd16x2.h"


#define RS GPIO_PIN_15
#define EN GPIO_PIN_3 //PORTB
#define D4 GPIO_PIN_9
#define D5 GPIO_PIN_10
#define D6 GPIO_PIN_11
#define D7 GPIO_PIN_12
#define LCD_GPIO_Port GPIOA
#define LCD_GPIO_Port_EN GPIOB

uint8_t character1[8] = { 0x02, 0x04, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x00 };
uint8_t character2[8] = { 0x02, 0x04, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00 };
uint8_t character3[8] = { 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E, 0x04, 0x00 };
uint8_t character4[8] = { 0x1F, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x00 };
uint8_t character5[8] = { 0x1F, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 };

  /**
    * @brief  Escreve um caracter no display
    * @param  data: caracter a ser mostrado
    * @retval None
    */
void lcd_write_data(char data)
{
	HAL_GPIO_WritePin(LCD_GPIO_Port, RS, 1); // rs = 1 dados
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

	HAL_GPIO_WritePin(LCD_GPIO_Port, D7, data & 0x80);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D6, data & 0x40);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D5, data & 0x20);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D4, data & 0x10);

	//Pulso no enable
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 1);
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

	HAL_GPIO_WritePin(LCD_GPIO_Port, D7, data & 0x08);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D6, data & 0x04);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D5, data & 0x02);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D4, data & 0x01);


	//Pulso no enable
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 1);
    HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

    HAL_Delay(2);
}
/**
  * @brief  Mostra no display uma variavel do tipo inteiro
  * @param  data: variavel do tipo inteiro a ser enviada
  * @retval None
  */
void lcd_write_int(int data)
{
	HAL_GPIO_WritePin(LCD_GPIO_Port, RS, 1); // rs = 1 dados
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

	if (data < 10){
			lcd_write_data(data + 0x30);
    }
	else if(data >= 10 && data < 100){
		char ch0 = (data % 10) + 0x30; // convert least significant digit to char
		char ch1 = (data / 10) + 0x30; // convert most significant digit to char

		lcd_write_data(ch1);
		lcd_write_data(ch0);
	}
	else if (data >= 100){
		char ch0 = (data % 10) + 0x30; // convert least significant digit to char
		char ch1 = (data % 100) + 0x30; // ERRADO
		char ch2 = (data / 100) + 0x30; // convert most significant digit to char

		lcd_write_data(ch2);
		lcd_write_data(ch1);
		lcd_write_data(ch0);
	}
}

/**
  * @brief  Envia um camando para o display
  * @param  data: Comando a ser enviado
  * @retval None
  */

void lcd_write_command(char cmd)
{

	HAL_GPIO_WritePin(LCD_GPIO_Port, RS, 0); //rs=0 comandos
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

	HAL_GPIO_WritePin(LCD_GPIO_Port, D7, cmd & 0x80);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D6, cmd & 0x40);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D5, cmd & 0x20);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D4, cmd & 0x10);

	//Pulso no enable
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 1);
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

	HAL_GPIO_WritePin(LCD_GPIO_Port, D7, cmd & 0x08);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D6, cmd & 0x04);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D5, cmd & 0x02);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D4, cmd & 0x01);

	//Pulso no enable
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 1);
    HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

    HAL_Delay(2);
}

/**
  * @brief  Posiciona o cursor do display
  * @param  row: linha
  * @param  col: coluna
  * @retval None
  */
void lcd_set_cursor(char row, char col)
{
	switch (row)
	    {
	        case 0:
	            col |= 0x80;
	            break;
	        case 1:
	            col |= 0xC0;
	            break;
	    }
	lcd_write_command (col);

}

/**
  * @brief  Funcao usada para inicializar o display
  * @param  cmd: comando
  * @retval None
  */
void lcd_write_command_init(char cmd)
{

	HAL_GPIO_WritePin(LCD_GPIO_Port, D7, cmd & 0x80);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D6, cmd & 0x40);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D5, cmd & 0x20);
	HAL_GPIO_WritePin(LCD_GPIO_Port, D4, cmd & 0x10);

	//Pulso no enable
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 1);
	HAL_GPIO_WritePin(LCD_GPIO_Port_EN, EN, 0);

}
/**
  * @brief  Inicia o display
  * @retval None
  */
void lcd_init(void)
{

	HAL_Delay(40);

	lcd_write_command_init(0x30);
	HAL_Delay(5);
	lcd_write_command_init(0x30);
	HAL_Delay(1);
	lcd_write_command_init(0x30);
	HAL_Delay(10);
	lcd_write_command_init(0x20);
	HAL_Delay(10);


	lcd_write_command(0x28);  //4 bits, 2 ou mais linhas
	lcd_write_command(0x08);  // Desliga o display
	//lcd_write_command(0x0E); // Liga o display e cursor
	lcd_write_command(0x0C);   // Desliga o cursor
	lcd_write_command(0x06);   // Cursor para direita quando caracter inserido

/*
	lcd_custom_char(0, character1);
	lcd_custom_char(1, character2);
	lcd_custom_char(2, character3);
	lcd_custom_char(0, character4);
	lcd_custom_char(1, character5);*/

	lcd_write_command(0x01); // Limpa a tela
}

/**
  * @brief  Limpa o display
  * @retval None
  */
void lcd_clear(void)
{
	lcd_write_command(0x01);// Limpa display e cursor em 0x0
}
/**
  * @brief  Escreve uma String no display
  * @param  str: string
  * @retval None
  */
void lcd_write_string(char* str){//Nao deu certo

	while (*str) {
		lcd_write_data(*str);
		str++;
	}

}
