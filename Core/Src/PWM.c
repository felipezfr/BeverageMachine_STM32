/*
 * PWM.c
 *
 *  Created on: Dec 5, 2020
 *      Author: ipizf
 */
#include "PWM.h"

/**
  * @brief Aciona o PWM da bomba, rampa de subida a 0.2s e decida a 0.25s
  * @retval
  */
void pwmBomba()
{
      int i = 0;

      for (i = 0; i <= MAX_DUTY_CYCLE_VALUE; i++)
      {
            TIM2->CCR1 = i;
            HAL_Delay(1);
      }
      for (i = MAX_DUTY_CYCLE_VALUE; i >= 0; i--)
      {
            TIM2->CCR1 = i;
            HAL_Delay(1);
      }
}
