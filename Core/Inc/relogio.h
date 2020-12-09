/*
 * relogio.h
 *
 *  Created on: Dec 2, 2020
 *      Author: ipizf
 */

#ifndef INC_RELOGIO_H_
#define INC_RELOGIO_H_

#include "stm32f1xx_hal.h"
#include "capsulas.h"
#include "lcd16x2.h"
#include <stdio.h>

void relogio(Receita capSelected);
void contarRelogio(void);

#endif /* INC_RELOGIO_H_ */
