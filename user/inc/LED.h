#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"

#define LED1(n)	GPIO_WriteBit(GPIOC,GPIO_Pin_0,(BitAction)n)
#define LED2(n)	GPIO_WriteBit(GPIOC,GPIO_Pin_6,(BitAction)n)

#define READ_LED1()	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define READ_LED2()	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)

void LED_Configuration(void);
void LED_Flash(void);

#endif
