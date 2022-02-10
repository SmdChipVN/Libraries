#include <general_timer.h>
#include <common.h>

#if (__PRODUCT_LINE__ == 0)
  void GENERAL_TIMER_Init(volatile void* TIMER, unsigned char Prescale, unsigned short ReloadValue)
  {
    ((volatile TIM2_TypeDef*)TIMER)->ARR.HIGH = ReloadValue >> 8;
    ((volatile TIM2_TypeDef*)TIMER)->ARR.LOW =  ReloadValue & 0xFF;
    ((volatile TIM2_TypeDef*)TIMER)->PSCR = Prescale;
    ((volatile TIM2_TypeDef*)TIMER)->EGR.REG = 1;
    ((volatile TIM2_TypeDef*)TIMER)->CR1.REG = BIT0 | BIT7;
  }
#else
  void TIM2_Init(unsigned char Prescale, unsigned short ReloadValue)
  {
    extern __no_init volatile TIM2_TypeDef TIM2;
    TIM2.ARR.HIGH = ReloadValue >> 8;
    TIM2.ARR.LOW =  ReloadValue & 0xFF;
    TIM2.PSCR = Prescale;
    TIM2.EGR.REG = 1;
    TIM2.CR1.REG = BIT0 | BIT7;
  }
  void TIM5_Init(unsigned char Prescale, unsigned short ReloadValue)
  {
    extern __no_init volatile TIM5_TypeDef TIM5;
    TIM5.ARR.HIGH = ReloadValue >> 8;
    TIM5.ARR.LOW =  ReloadValue & 0xFF;
    TIM5.PSCR = Prescale;
    TIM5.EGR.REG = 1;
    TIM5.CR1.REG = BIT0 | BIT7;
  }
#endif
void TIM3_Init(unsigned char Prescale, unsigned short ReloadValue)
{
  extern __no_init volatile TIM3_TypeDef TIM3;
  TIM3.ARR.HIGH = ReloadValue >> 8;
  TIM3.ARR.LOW =  ReloadValue & 0xFF;
  TIM3.PSCR = Prescale;
  TIM3.EGR.REG = 1;
  TIM3.CR1.REG = BIT0 | BIT7;
}
//==============================================================================================================================================================
#if (__PRODUCT_LINE__ == 0)
  void GENERAL_TIMER_GeneratePWM(volatile void* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
  {
    ((volatile TIM2_TypeDef*)TIMER)->CR1.BITS.CEN = 0;
    ((unsigned char*)&((volatile TIM2_TypeDef*)TIMER)->CCMR1.OUTPUT.REG)[Channel - 1] = BIT6 | BIT5 | BIT3;
    switch (Channel)
    {
      case 1:
        ((volatile TIM2_TypeDef*)TIMER)->CCER1.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        ((volatile TIM2_TypeDef*)TIMER)->CCR1.HIGH = Duty >> 8;
        ((volatile TIM2_TypeDef*)TIMER)->CCR1.LOW = Duty & 0xFF;
        break;
      case 2:
        ((volatile TIM2_TypeDef*)TIMER)->CCER1.REG = BIT4 | (IDLE_IsHigh ? BIT5 : 0);
        ((volatile TIM2_TypeDef*)TIMER)->CCR2.HIGH = Duty >> 8;
        ((volatile TIM2_TypeDef*)TIMER)->CCR2.LOW = Duty & 0xFF;
        break;
      case 3:
        ((volatile TIM2_TypeDef*)TIMER)->CCER2.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        ((volatile TIM2_TypeDef*)TIMER)->CCR3.HIGH = Duty >> 8;
        ((volatile TIM2_TypeDef*)TIMER)->CCR3.LOW = Duty & 0xFF;
        break;
    }
    ((volatile TIM2_TypeDef*)TIMER)->EGR.REG = 1;
    ((volatile TIM2_TypeDef*)TIMER)->CR1.BITS.CEN = 1;
  }
#else
  void TIM2_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
  {
    extern __no_init volatile TIM2_TypeDef TIM2;
    TIM2.CR1.BITS.CEN = 0;
    ((unsigned char*)&TIM2.CCMR1.OUTPUT.REG)[Channel - 1] = BIT6 | BIT5 | BIT3;
    switch (Channel)
    {
      case 1:
        TIM2.CCER1.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        TIM2.CCR1.HIGH = Duty >> 8;
        TIM2.CCR1.LOW = Duty & 0xFF;
        break;
      case 2:
        TIM2.CCER1.REG = BIT4 | (IDLE_IsHigh ? BIT5 : 0);
        TIM2.CCR2.HIGH = Duty >> 8;
        TIM2.CCR2.LOW = Duty & 0xFF;
      case 3:
        TIM2.CCER2.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        TIM2.CCR3.HIGH = Duty >> 8;
        TIM2.CCR3.LOW = Duty & 0xFF;
        break;
    }
    TIM2.EGR.REG = 1;
    TIM2.CR1.BITS.CEN = 1;
  }
  void TIM5_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
  {
    extern __no_init volatile TIM5_TypeDef TIM5;
    TIM5.CR1.BITS.CEN = 0;
    ((unsigned char*)&TIM5.CCMR1.OUTPUT.REG)[Channel - 1] = BIT6 | BIT5 | BIT3;
    switch (Channel)
    {
      case 1:
        TIM5.CCER1.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        TIM5.CCR1.HIGH = Duty >> 8;
        TIM5.CCR1.LOW = Duty & 0xFF;
        break;
      case 2:
        TIM5.CCER1.REG = BIT4 | (IDLE_IsHigh ? BIT5 : 0);
        TIM5.CCR2.HIGH = Duty >> 8;
        TIM5.CCR2.LOW = Duty & 0xFF;
        break;
      case 3:
        TIM5.CCER2.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
        TIM5.CCR3.HIGH = Duty >> 8;
        TIM5.CCR3.LOW = Duty & 0xFF;
        break; 
    }
    TIM5.EGR.REG = 1;
    TIM5.CR1.BITS.CEN = 1;
  }
#endif
void TIM3_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
{
  extern __no_init volatile TIM3_TypeDef TIM3;
  TIM3.CR1.BITS.CEN = 0;
  ((unsigned char*)&TIM3.CCMR1.OUTPUT.REG)[Channel - 1] = BIT6 | BIT5 | BIT3;
  switch (Channel)
  {
    case 1:
      TIM3.CCER1.REG = BIT0 | (IDLE_IsHigh ? BIT1 : 0);
      TIM3.CCR1.HIGH = Duty >> 8;
      TIM3.CCR1.LOW = Duty & 0xFF;
      break;
    case 2:
      TIM3.CCER1.REG = BIT4 | (IDLE_IsHigh ? BIT5 : 0);
      TIM3.CCR2.HIGH = Duty >> 8;
      TIM3.CCR2.LOW = Duty & 0xFF;
      break;
  }
  TIM3.EGR.REG = 1;
  TIM3.CR1.BITS.CEN = 1;
}