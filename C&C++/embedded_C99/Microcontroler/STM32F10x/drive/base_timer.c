#include <basic_timer.h>
#include <general_timer.h>
#include <advanced_timer.h>
#include <common.h>
#include <bitband.h>

void BASE_TIMER_Init(volatile void* TIMER, unsigned int Prescale, unsigned int ReloadValue)
{
  ((BASIC_TIMER_TypeDef*)TIMER)->CR1.REG = 0;
  ((BASIC_TIMER_TypeDef*)TIMER)->CNT = 0;
  ((BASIC_TIMER_TypeDef*)TIMER)->ARR = ReloadValue;
  ((BASIC_TIMER_TypeDef*)TIMER)->PSC = Prescale;
  ((BASIC_TIMER_TypeDef*)TIMER)->CR1.REG = BIT7 | BIT0;
}

void BASE_TIMER_GeneratePWM(volatile void* TIMER, unsigned int Channel, unsigned int Duty, unsigned int IDLE_IsHigh)
{  
  static const unsigned short cn_ref[3][2] = {{0x0068, 0x6800}, {0x0078, 0x7800}, {0xFF00, 0x00FF},};
  GENERAL_TIMER_BITBAND_TypeDef* GENERAL_TIMER_BITBAND = (GENERAL_TIMER_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)TIMER, 0);
  unsigned int channel = Channel >> 6;
  unsigned int channel_N = Channel >> 7;  
  Channel = (Channel - 1) & ~(BIT7 | BIT6);
  ((BASIC_TIMER_TypeDef*)TIMER)->CR1.REG = 0;
  ((BASIC_TIMER_TypeDef*)TIMER)->CNT = 0;
  ((BASIC_TIMER_TypeDef*)TIMER)->EGR.REG = 1;  
  *(((unsigned int*)&((GENERAL_TIMER_TypeDef*)TIMER)->CCR1) + Channel) = Duty;
  unsigned int* reg = ((GENERAL_TIMER_TypeDef*)TIMER)->CCMR.OUTPUT.REGS + (Channel >> 1);
  *reg &= cn_ref[2][Channel];
  *reg |= cn_ref[IDLE_IsHigh][Channel];
  Channel <<= 2;
  ((unsigned int*)(&GENERAL_TIMER_BITBAND->CCER.CC1E))[Channel] = channel;
  ((unsigned int*)(&((ADVANCED_TIMER_BITBAND_TypeDef*)GENERAL_TIMER_BITBAND)->CCER.CC1NE))[Channel] = channel_N;
  ((ADVANCED_TIMER_BITBAND_TypeDef*)GENERAL_TIMER_BITBAND)->BDTR.MOE = 1;  
  ((BASIC_TIMER_TypeDef*)TIMER)->CR1.REG = BIT7 | BIT0;  
}