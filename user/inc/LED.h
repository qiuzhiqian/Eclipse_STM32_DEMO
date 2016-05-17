#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"

#define LED1(n)	GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)n)
#define LED2(n)	GPIO_WriteBit(GPIOF,GPIO_Pin_7,(BitAction)n)
#define LED3(n)	GPIO_WriteBit(GPIOF,GPIO_Pin_8,(BitAction)n)

#define READ_LED1()	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define READ_LED2()	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)
#define READ_LED3()	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)

void LED_Configuration(void);
void LED_Flash(void);

#endif
