#include <advanced_timer.h>
#include <common.h>

void ADVANCED_TIMER_Init(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned short Prescale, unsigned short ReloadValue)
{
  TIMER->ARR.HIGH = ReloadValue >> 8; TIMER->ARR.LOW =  ReloadValue & 0xFF;
  TIMER->PSCR.HIGH = Prescale >> 8; TIMER->PSCR.LOW = Prescale & 0xFF;
  TIMER->EGR.REG = 1;
  TIMER->CR1.REG = BIT0 | BIT7;
}
void ADVANCED_TIMER_GeneratePWM(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
{
  
}