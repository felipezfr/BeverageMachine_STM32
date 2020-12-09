/*
 * capsulas.h
 *
 *  Created on: Dec 2, 2020
 *      Author: ipizf
 */

#ifndef INC_CAPSULAS_H_
#define INC_CAPSULAS_H_

#include "stm32f1xx_hal.h"
#include "heartBeat.h"
#include "lcd16x2.h"
#include "teclado.h"
#include "PWM.h"
#include <stdio.h>

#define Y1_PORT GPIOB
#define Y1_PIN GPIO_PIN_9

#define Y2_PORT GPIOB
#define Y2_PIN GPIO_PIN_8

#define Y3_PORT GPIOB
#define Y3_PIN GPIO_PIN_7

#define Y4_PORT GPIOB
#define Y4_PIN GPIO_PIN_6

#define CAPSULA_BIT_0_PORT GPIOA
#define CAPSULA_BIT_0 GPIO_PIN_8

#define CAPSULA_BIT_1_PORT GPIOB
#define CAPSULA_BIT_1 GPIO_PIN_15

#define CAPSULA_BIT_2_PORT GPIOB
#define CAPSULA_BIT_2 GPIO_PIN_14

#define P1_PORT GPIOC
#define P1_PIN GPIO_PIN_14

#define P2_PORT GPIOC
#define P2_PIN GPIO_PIN_15

typedef enum {SEM_CAPSULA, CAPSULA_AGUA, CAPSULA_AGUA_COM_GAS, CAPSULA_CHA_GELADO, CAPSULA_CHA_QUENTE, CAPSULA_REFRIGERANTE} Tipo_CAPSULA;
typedef enum {SEM_AGUA, AGUA_GELADA, AGUA_QUENTE, AGUA_NATURAL} Tipo_AGUA;

typedef struct
{
	Tipo_CAPSULA tipoCapsula;
    Tipo_AGUA tipoAgua;
    char nomeCapsula[16];
    int temperaturaAgua;
    float tempoAgua;
    float tempoCO2;

} Receita;

void iniciarPreparo(Receita CAPSULA);
void heaterPID(int setPoint);
void coolerPID(int setPoint);

Receita lerSensorCapsulas(void);
int capsulaInserida(Receita tipoCapsula);

#endif /* INC_CAPSULAS_H_ */
