#include "stm32f10x.h"

#include "led.h"
#include "tim.h"
#include "usart.h"

void NVIC_Configuration(u8 num);

int main(void)
{
    NVIC_Configuration(1);
    LED_Configuration();
    USART1_Configuration(115200);
    TIM2_Configuration(1000,72);

  while(1)
  {
    LED_Flash();

  }
}

void NVIC_Configuration(u8 num)
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_1);
}
