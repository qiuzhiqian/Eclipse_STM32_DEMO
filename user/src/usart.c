#include "usart.h"
#include "stdio.h"
#include "stm32f10x.h"
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

void USART2_Configuration(u32 bdrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

	//USART1-----bd=115200
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;											//串口输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;												//串口输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=bdrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure);

	USART_Cmd(USART2,ENABLE);																		//串口使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

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

void USART3_IRQHandler(void)
{
	u8 ch;
	if(USART_GetITStatus(USART3,USART_IT_RXNE))			//接收中断
	{
		ch=USART_ReceiveData(USART3);
		if(Rx3.RxFlag==0)
		{
			Rx3.StaFlag=1;
			Rx3.RxCount=0;
		}
		Rx3.RxBuff[Rx3.RxCount]=ch;

		Rx3.RxCount++;
		Rx3.RxDelay=10;
	}
	if(USART_GetITStatus(USART3,USART_IT_RXNE))			//发送中断
	{

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

void USART3_SendChar(u8 ch)
{
	USART_SendData(USART3,ch);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
	USART_ClearFlag(USART3,USART_FLAG_TC);
}

void USART3_SendNChar(u8 *str,u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART3,*(str+i));
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
		USART_ClearFlag(USART3,USART_FLAG_TC);
	}
}

void Clear_Buff(u8 *str,u16 len)
{
	u8 i;
	for(i=0;i<len;i++)		*(str+i)=0;
}

int _write(int file, char* ptr, int len)
{
	int i=0;
	int cnt=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1,*ptr);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		ptr++;
		cnt++;
	}
	return cnt;
}
