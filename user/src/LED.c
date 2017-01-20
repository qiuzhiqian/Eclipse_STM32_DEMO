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

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_6;//LED
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //翻转速率50Mhz
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推免输出方式
		GPIO_Init(GPIOC, &GPIO_InitStructure);             //初始化PB8.9.14.15
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
		My_printf("watch_count=%d\n",watch_count);
	}
}
