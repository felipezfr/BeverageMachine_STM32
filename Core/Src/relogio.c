/*
 * relogio.c
 *
 *  Created on: Dec 2, 2020
 *      Author: ipizf
 */


#include "relogio.h"


int hor = 0;
int min = 0;
int seg = 0;

int segAnt = -1;

static long long previousTime = 0;

/**
  * @brief Exibe tela do relogio
  * @retval
  */
void relogio(Receita capSelected)
{
	char text[20];

	if (seg != segAnt)
	{ //Atualiza o display somente apos mudar os segundos
		segAnt = seg;

		lcd_clear();
		sprintf(text, "Relogio");
		lcd_set_cursor(0, 0);
		lcd_write_string(text);
		lcd_set_cursor(1, 0);
		sprintf(text, "%02d:%02d:%02d", hor, min, seg);
		lcd_write_string(text);

		if (capSelected.tipoCapsula != SEM_CAPSULA)
		{
			sprintf(text, "CAP");

			lcd_set_cursor(1, 13);
			lcd_write_string(text);
		}
	}
}

/**
  * @brief Incrementa a contagem do relogio a cada 1 segundo;
  * @retval
  */
void contarRelogio()
{
	//HAL_Delay(1000);

	if ((HAL_GetTick() - previousTime) >= 1000)
	{
		previousTime = HAL_GetTick();
		seg++;
		if (seg > 59)
		{
			seg = 0;
			min++;
		}
		if (min > 59)
		{
			min = 0;
			hor++;
		}
		if (hor > 23)
		{
			hor = 0;
		}
	}
}
