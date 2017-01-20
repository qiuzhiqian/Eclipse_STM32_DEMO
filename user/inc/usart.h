#ifndef __USART_H
#define __USART_H
#include <stdio.h>
#include "stm32f10x.h"

typedef struct
{
	u8 	RxBuff[200];
	u8  RxOldCount;
	u8 	RxCount;
	u8 	RxFlag;
	u8  StaFlag;
	u16	RxDelay;
} USART_Rx;

void USART1_Configuration(u32 bdrate);
void UART5_Configuration(u32 bdrate);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void UART5_IRQHandler(void);
int fputc(int ch,FILE *f);

void USART1_SendChar(u8 ch);
void USART1_SendNChar(u8 *str,u8 len);
void USART2_SendChar(u8 ch);
void USART2_SendNChar(u8 *str,u8 len);
void UART5_SendData(u8 ch);
void UART5_SendNData(u8 *str,u16 len);
void UART5_SendString(u8 *str);

void Clear_Buff(u8 *str,u16 len);

int My_printf(const char *format,...);

#endif
