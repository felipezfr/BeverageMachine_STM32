/*
 * teclado.c
 *
 *  Created on: Nov 17, 2020
 *      Author: ipizf
 */

#include "teclado.h"

int flagCan = 0;
int flagInc = 0;
int flagDec = 0;
int flagConf = 0;

static long long previousTime = 0;

/**
  * @brief Le as entradas do teclado
  * @retval 0 nenhum botao clicado
  * @retval 1 cancelar
  * @retval 2 menu +
  * @retval 3 menu -
  * @retval 4 confirmar
  *
  */
int ler_teclado()
{

	if ((HAL_GetTick() - previousTime) >= 150)
	{
		previousTime = HAL_GetTick();
		int can = HAL_GPIO_ReadPin(cancel_PORT, cancel_PIN);
		int menuInc = HAL_GPIO_ReadPin(menuIncremento_PORT, menuIncremento_PIN);
		int menuDec = HAL_GPIO_ReadPin(menuDecremento_PORT, menuDecremento_PIN);
		int conf = HAL_GPIO_ReadPin(confirmar_PORT, confirmar_PIN);

		if (can)
		{
			return 1;
		}

		if (menuInc)
		{
			return 2;
		}

		if (menuDec)
		{
			return 3;
		}
		if (conf)
		{
			return 4;
		}

		return 0;
	}
	return 0;
}

	/*
	if(!can){
		flagCan = 1;
	}
	if(can && flagCan){
		flagCan = 0;
		return 1;
	}

	if(!menuInc){
		flagInc = 1;
	}
	if(menuInc && flagInc){
		flagInc = 0;
		return 2;
	}

	if(!menuDec){
		flagDec = 1;
	}
	if(menuDec && flagDec){
		flagDec = 0;
		return 3;
	}

	if(!conf){
			flagConf = 1;
	}
	if(conf && flagConf){
		flagConf = 0;
		return 4;
	}*/

