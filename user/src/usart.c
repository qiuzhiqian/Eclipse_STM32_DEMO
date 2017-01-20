#include "usart.h"
#include "stdio.h"
#include "stm32f10x.h"

#include <stdio.h>
#include <stdarg.h>

USART_Rx Rx1,Rx2,Rx3;

void USART1_Configuration(u32 bdrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1,ENABLE);

	//USART1-----bd=115200
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;											//串口输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;												//串口输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=bdrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);

	USART_Cmd(USART1,ENABLE);																		//串口使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

}

void UART5_Configuration(u32 bdrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bdrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //发送和接受使能
	USART_Init(UART5, &USART_InitStructure);                                       //初始化串口2
	USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);                                  //接收中断使能
	USART_Cmd(UART5, ENABLE);                                                      //使能时串口2
	//USART_ClearITPendingBit(UART5, USART_IT_TC);                                   //清除中断TC位

	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;	         //串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	         //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           	 //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);                              //根据指定的参数初始化VIC寄存器

}

void USART1_IRQHandler(void)
{
	u8 ch;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))			//接收中断
	{
		ch=USART_ReceiveData(USART1);
		if(Rx1.StaFlag==0)
		{
			Rx1.StaFlag=1;
			Rx1.RxCount=0;
		}
		Rx1.RxBuff[Rx1.RxCount]=ch;

		Rx1.RxCount++;
		Rx1.RxDelay=10;
	}
	if(USART_GetITStatus(USART1,USART_IT_TC))			//发送中断
	{

	}
}

void USART2_IRQHandler(void)
{
	u8 ch;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))			//接收中断
	{
		ch=USART_ReceiveData(USART2);
		if(Rx2.StaFlag==0)
		{
			Rx2.StaFlag=1;
			Rx2.RxCount=0;
		}
		Rx2.RxBuff[Rx2.RxCount]=ch;

		Rx2.RxCount++;
		Rx2.RxDelay=10;
	}
	if(USART_GetITStatus(USART2,USART_IT_TC))			//发送中断
	{

	}
}

//UASRT2的中断函数
void UART5_IRQHandler(void)                	//串口1中断服务程序
{
	//u8 Res;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
	else if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
	{
		USART_ClearITPendingBit(UART5, USART_IT_TC);
	}
}

void USART1_SendChar(u8 ch)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_ClearFlag(USART1,USART_FLAG_TC);
}

void USART1_SendNChar(u8 *str,u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1,*(str+i));
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_ClearFlag(USART1,USART_FLAG_TC);
	}
}

void USART2_SendChar(u8 ch)
{
	USART_SendData(USART2,ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	USART_ClearFlag(USART2,USART_FLAG_TC);
}

void USART2_SendNChar(u8 *str,u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2,*(str+i));
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		USART_ClearFlag(USART2,USART_FLAG_TC);
	}
}

void UART5_SendNData(u8 *str,u16 len)
{
 	unsigned int i = 0;
	for(i = 0;i < len;i++)
	{
		USART_SendData(UART5,*str);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
		str++;
	}
}

void UART5_SendData(u8 ch)
{
	USART_SendData(UART5,ch);
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
}

void UART5_SendString(u8 *str)
{
	while(*str)
	{
		USART_SendData(UART5,*str);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
		str++;
	}
}

void Clear_Buff(u8 *str,u16 len)
{
	u8 i;
	for(i=0;i<len;i++)		*(str+i)=0;
}

int __io_putchar(int ch)
{
	USART_SendData(UART5,(unsigned char)ch);
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET);
	return ch;
}

static char stdbuff[512];
int My_printf(const char *format,...)
{
	int n;
	va_list ap;
	va_start(ap,format);

	n=vsprintf(stdbuff,format,ap);

	va_end(ap);

	UART5_SendNData(stdbuff,n);

	return n;
}
