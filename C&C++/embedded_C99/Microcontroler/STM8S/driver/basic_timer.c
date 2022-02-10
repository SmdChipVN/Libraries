#include <basic_timer.h>
#include <common.h>

#if (__PRODUCT_LINE__ == 0)
  void BASIC_TIMER_Init(volatile void* TIMER, unsigned char Prescale, unsigned char ReloadValue)
  {
    ((volatile TIM4_TypeDef*)TIMER)->ARR = ReloadValue;
    ((volatile TIM4_TypeDef*)TIMER)->PSCR = Prescale;
    ((volatile TIM4_TypeDef*)TIMER)->CR1.REG = BIT7 | BIT0;
  }
#else
  void TIM4_Init(unsigned char Prescale, unsigned char ReloadValue)
  {
    extern __no_init volatile TIM4_TypeDef TIM4;
    TIM4.ARR = ReloadValue;
    TIM4.PSCR = Prescale;
    TIM4.CR1.REG = BIT7 | BIT0;
  }
  void TIM6_Init(unsigned char Prescale, unsigned char ReloadValue)
  {
    extern __no_init volatile TIM4_TypeDef TIM6;
    TIM6.ARR = ReloadValue;
    TIM6.PSCR = Prescale;
    TIM6.CR1.REG = BIT7 | BIT0;
  }
#endif