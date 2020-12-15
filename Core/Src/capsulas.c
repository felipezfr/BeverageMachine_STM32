/*
 * capsulas.c
 *
 *  Created on: Dec 2, 2020
 *      Author: ipizf
 */
#include "capsulas.h"

Receita CAPSULA_nao_inserida = {SEM_CAPSULA, SEM_AGUA, "", 0, 0, 0};
Receita CAPSULA_agua = {CAPSULA_AGUA, SEM_AGUA, "Escolha a agua", 0, 3.0, 0};
Receita CAPSULA_agua_com_gas = {CAPSULA_AGUA_COM_GAS, AGUA_GELADA, "Agua com gas", 15, 3.0, 1.5};
Receita CAPSULA_cha_gelado = {CAPSULA_CHA_GELADO, AGUA_GELADA, "Cha gelado", 15, 2.7, 0};
Receita CAPSULA_cha_quente = {CAPSULA_CHA_QUENTE, AGUA_QUENTE, "Cha Quente", 60, 2.7, 0};
Receita CAPSULA_refrigerante = {CAPSULA_REFRIGERANTE, AGUA_GELADA, "Refrigerante", 17, 4.0, 2.56};


/**
  * @brief Le o sensor de capsulas
  * @retval retorna a receita equivalente aos pinos
  */
Receita lerSensorCapsulas()
{

  int bit0 = HAL_GPIO_ReadPin(CAPSULA_BIT_0_PORT, CAPSULA_BIT_0);
  int bit1 = HAL_GPIO_ReadPin(CAPSULA_BIT_1_PORT, CAPSULA_BIT_1);
  int bit2 = HAL_GPIO_ReadPin(CAPSULA_BIT_2_PORT, CAPSULA_BIT_2);

  if (bit2 == 0 && bit1 == 0 && bit0 == 0)
  {
    return CAPSULA_nao_inserida;
  }
  if (bit2 == 0 && bit1 == 0 && bit0 == 1)
  {
    return CAPSULA_agua;
  }
  if (bit2 == 0 && bit1 == 1 && bit0 == 0)
  {
    return CAPSULA_agua_com_gas;
  }
  if (bit2 == 0 && bit1 == 1 && bit0 == 1)
  {
    return CAPSULA_cha_gelado;
  }
  if (bit2 == 1 && bit1 == 0 && bit0 == 0)
  {
    return CAPSULA_cha_quente;
    //return CAPSULA_refrigerante;
  }
  if (bit2 == 1 && bit1 == 0 && bit0 == 1)
  {
    return CAPSULA_refrigerante;
  }

  return CAPSULA_nao_inserida;
}

/**
  * @brief Exibe tela de inicio de preparo
  * @retval 1 quando o preparo foi terminado
  * @retval 0 quando o preparo nao foi terminado
  */
int capsulaInserida(Receita CAPSULA)
{

  char text[16];
  char tipoAgua[3][16];

  sprintf(tipoAgua[0], "%s", "Quente  S:Inici");
  sprintf(tipoAgua[1], "%s", "Natural S:Inici");
  sprintf(tipoAgua[2], "%s", "Gelada  S:Inici");

  lcd_clear();
  sprintf(text, "%s", CAPSULA.nomeCapsula);
  lcd_set_cursor(0, 0);
  lcd_write_string(text);

  if (CAPSULA.tipoCapsula == CAPSULA_AGUA)
  {
    sprintf(text, "+/-:MudarTemp");
    lcd_set_cursor(1, 0);
    lcd_write_string(text);
  }
  else
  {
    sprintf(text, "C:canc,S:Inici");
    lcd_set_cursor(1, 0);
    lcd_write_string(text);
  }

  int btn = 0;
  int cont = 0;
  do
  {
    btn = ler_teclado();
    switch (btn)
    {
    case 1: //Volta para o relogio
      return 0;
      break;
    case 2:
      if (CAPSULA.tipoCapsula == CAPSULA_AGUA)//Capsula de agua, usuario seleciona tipo de agua desejada
      {
        lcd_clear();
        sprintf(text, "%s", CAPSULA.nomeCapsula);
        lcd_set_cursor(0, 0);
        lcd_write_string(text);

        sprintf(text, "%s", tipoAgua[cont]);
        lcd_set_cursor(1, 0);
        lcd_write_string(text);

        switch (cont)//Temperatura da agua de acordo com a selecao do usuario
        {
        case 0:
          CAPSULA.temperaturaAgua = 60;
          break;
        case 1:
          CAPSULA.temperaturaAgua = 0;
          break;
        case 2:
          CAPSULA.temperaturaAgua = 15;
          break;

        default:
          break;
        }

        cont--;
        if (cont < 0)//Volta para o primeiro tipo de agua
          cont = 2;
      }

      break;
    case 3:
      if (CAPSULA.tipoCapsula == CAPSULA_AGUA)//Capsula de agua, usuario seleciona tipo de agua desejada
      {
        lcd_clear();
        sprintf(text, "%s", CAPSULA.nomeCapsula);
        lcd_set_cursor(0, 0);
        lcd_write_string(text);
        sprintf(text, "%s", tipoAgua[cont]);
        lcd_set_cursor(1, 0);
        lcd_write_string(text);

        switch (cont)//Temperatura da agua de acordo com a selecao do usuario
        {
        case 0:
          CAPSULA.tipoAgua = AGUA_QUENTE;
          CAPSULA.temperaturaAgua = 60;
          break;
        case 1:
          CAPSULA.tipoAgua = AGUA_NATURAL;
          CAPSULA.temperaturaAgua = 30;
          break;
        case 2:
          CAPSULA.tipoAgua = AGUA_GELADA;
          CAPSULA.temperaturaAgua = 15;
          break;

        default:
          break;
        }

        cont++;
        if (cont > 2)
          cont = 0;
      }

      break;
    case 4:
      iniciarPreparo(CAPSULA);
      return 1;
      break;
    }


    heartBeat();
  } while (btn != 4 || btn != 1);

  return 0;
}

/**
  * @brief Inicia o preparo passando a receita da capsula
  * @retval None
  * @param[in] CAPSULA :Capsula a iniciar preparo
  */
void iniciarPreparo(Receita CAPSULA)
{

  char text[20];

  if (HAL_GPIO_ReadPin(P1_PORT, P1_PIN))
  { //Filtro saturado

    lcd_clear();
    sprintf(text, "ERRO");
    lcd_set_cursor(0, 0);
    lcd_write_string(text);

    sprintf(text, "Filtro saturado");
    lcd_set_cursor(1, 0);
    lcd_write_string(text);

    HAL_Delay(2000);

    return;
  }
  if (HAL_GPIO_ReadPin(P2_PORT, P2_PIN))
  { //Cilindo vazio

    lcd_clear();
    sprintf(text, "ERRO");
    lcd_set_cursor(0, 0);
    lcd_write_string(text);

    sprintf(text, "CO2 vazio");
    lcd_set_cursor(1, 0);
    lcd_write_string(text);

    HAL_Delay(2000);
    return;
  }

  lcd_clear();
  sprintf(text, "Iniciando...");
  lcd_set_cursor(0, 2);
  lcd_write_string(text);

  pwmBomba();

  if (CAPSULA.tipoAgua == AGUA_QUENTE)//Capsula precisa de agua quente, aciona controlador PID
  {
    heaterPID(CAPSULA.temperaturaAgua);
  }
  else if (CAPSULA.tipoAgua == AGUA_GELADA)//Capsula precisa de agua gelada, aciona controlador PID
  {
    coolerPID(CAPSULA.temperaturaAgua);
  }

  sprintf(text, "Misturando");
  lcd_set_cursor(0, 2);
  lcd_write_string(text);
  HAL_Delay(1000);

  lcd_clear();
  if (CAPSULA.tipoAgua == AGUA_QUENTE)//Capsula precisa de agua quente
  {
    sprintf(text, "%s", "Agua quente");
    lcd_set_cursor(0, 0);
    lcd_write_string(text);

    HAL_GPIO_WritePin(Y1_PORT, Y1_PIN, 1);
    HAL_Delay(CAPSULA.tempoAgua * 1000);
    HAL_GPIO_WritePin(Y1_PORT, Y1_PIN, 0);
  }
  else if (CAPSULA.tipoAgua == AGUA_GELADA)//Capsula precisa de agua gelada
  {
    sprintf(text, "%s", "Agua gelada   ");
    lcd_set_cursor(0, 0);
    lcd_write_string(text);
    int done = 0;

    if (CAPSULA.tempoCO2 > 0.0)///Capsula precisa de CO2
    {
      long long previousTimeAgua = HAL_GetTick();//Variavel para controlar o tempo da agua
      long long previousTimeCO2 = HAL_GetTick();//Variavel para controlar o tempo de CO2

      sprintf(text, "CO2");
      lcd_set_cursor(1, 0);
      lcd_write_string(text);

      HAL_GPIO_WritePin(Y2_PORT, Y2_PIN, 1); //Liga saida de agua gelada
      HAL_GPIO_WritePin(Y4_PORT, Y4_PIN, 1); //Liga saida CO2
      do
      {

        if ((HAL_GetTick() - previousTimeAgua) >= CAPSULA.tempoAgua * 1000)//Espera o tempo da agua para desligar a saida
        {
          previousTimeAgua = 2147483647;
          HAL_GPIO_WritePin(Y2_PORT, Y2_PIN, 0);//desliga a saida de agua
          done++;//tempo agua terminado
        }
        if ((HAL_GetTick() - previousTimeCO2) >= CAPSULA.tempoCO2 * 1000)//Espera o tempo de CO2 para desligar a saida
        {
          previousTimeCO2 = 2147483647;
          HAL_GPIO_WritePin(Y4_PORT, Y4_PIN, 0);//desliga a saida de CO2
          done++;//tempo CO2 terminado
        }
        heartBeat();
      } while (done < 2);//Sai do loop quando os dois tempos foram atingidos
    }
    else//Nao precisa de CO2, apenas espera o tempo da agua
    {
      HAL_GPIO_WritePin(Y2_PORT, Y2_PIN, 1);
      HAL_Delay(CAPSULA.tempoAgua * 1000);
      HAL_GPIO_WritePin(Y2_PORT, Y2_PIN, 0);
    }
  }
  else if (CAPSULA.tipoAgua == AGUA_NATURAL) //Capsula precisa de agua natural
  {
    sprintf(text, "%s", "Agua natural ");
    lcd_set_cursor(0, 0);
    lcd_write_string(text);

    HAL_GPIO_WritePin(Y3_PORT, Y3_PIN, 1);
    HAL_Delay(CAPSULA.tempoAgua * 1000);
    HAL_GPIO_WritePin(Y3_PORT, Y3_PIN, 0);
  }

  lcd_clear();
  sprintf(text, "Finalizando...");
  lcd_set_cursor(1, 2);
  lcd_write_string(text);
  HAL_Delay(1000);
  lcd_clear();
  return;
}
