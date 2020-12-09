/*
 * heartBeat.c
 *
 *  Created on: 4 de dez de 2020
 *      Author: ipizf
 */

#include "heartBeat.h"

static long long previousTime = 0;

/**
  * @brief Pisca o led onboard a cada 300ms
  * @retval
  */
void heartBeat()
{

	if ((HAL_GetTick() - previousTime) >= 300)
	{
		previousTime = HAL_GetTick();

		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
}
