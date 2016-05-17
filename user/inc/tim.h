#ifndef __TIM_H
#define __TIM_H
#include "stm32f10x.h"

void TIM1_Configuration(u16 per,u16 psc);
void TIM2_Configuration(u16 per,u16 psc);
void TIM2_IRQHandler(void);
void Delay_Servers(u32 *delaypar,u32 delayval,void (*delayexe)(void));

#endif
