/*
 * teclado.h
 *
 *  Created on: Nov 17, 2020
 *      Author: ipizf
 */

#ifndef INC_TECLADO_H_
#define INC_TECLADO_H_

#include "stm32f1xx_hal.h"

#define cancel_PIN GPIO_PIN_1
#define cancel_PORT GPIOB

#define menuIncremento_PIN GPIO_PIN_0
#define menuIncremento_PORT GPIOB

#define menuDecremento_PIN GPIO_PIN_7
#define menuDecremento_PORT GPIOA

#define confirmar_PIN GPIO_PIN_6
#define confirmar_PORT GPIOA

int ler_teclado();

#endif /* INC_TECLADO_H_ */
