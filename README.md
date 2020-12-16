# Máquina de bebidas

Firmware de controle para uma máquina de bebidas automática. 


Cápsulas com a bebida desejada são inseridas em um compartimento de mistura. Cada cápsula tem uma sequência binária de 3 bits pré definida. A sequência guarda as instruções de preparo da bebida em questão, quantidade de água, de gás carbônico, temperatura, etc. A máquina pode funcionar como um purificador, refrigerador e gaseificador de água. Avisos no display indicam quando deve ser substituído o filtro de água ou o cilindro de gás carbônico.

# Receitas
000 - Sem capsula

001 - Água (Selecionar Água quente, Água gelada ou Água natural)

010 - Água com gás

011 - Chá Gelado

100 - Chá Quente

101 - Refrigerante


# Botões navegação

Botões de entrada:

S --> Confirmar

I --> Incrementar

D --> Decrementar

C --> Cancelar

Se a capsula inserida for do tipo água, o usuário pode escolher a temperatura da água (quente, gelada ou natural) através dos botões Incrementar e Decrementar citados acima.

# Montagem

![1](https://github.com/felipezfr/BeverageMachine_STM32/blob/main/Fotos/1.jpeg)
![2](https://github.com/felipezfr/BeverageMachine_STM32/blob/main/Fotos/2.jpeg)
![3](https://github.com/felipezfr/BeverageMachine_STM32/blob/main/Fotos/3.jpeg)
![4](https://github.com/felipezfr/BeverageMachine_STM32/blob/main/Fotos/4.jpeg)
