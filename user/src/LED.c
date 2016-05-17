/*
PB0----LED1
PF7----LED2
PF8----LED3
*/
#include "led.h"
#include "stdio.h"
u32 LED_delay=0;
u16 watch_count=0;

void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOF,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	LED1(1);
	//LED2(1);
	//LED3(1);
}

void LED_Flash(void)
{
	if(LED_delay==0)
	{
		LED_delay=500;

		LED1(!(READ_LED1()));
		//USART1_SendChar('A');
		printf("123\n");
		watch_count++;
	}
}
