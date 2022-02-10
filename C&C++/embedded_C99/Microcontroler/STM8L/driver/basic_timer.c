#include <basic_timer.h>

#ifdef BASIC_TIMER_DIRECT
  #define BASIC_TIMER_MASK      BASIC_TIMER_DIRECT
#else
  #define BASIC_TIMER_MASK      (*TIMER)
#endif

#ifdef BASIC_TIMER_DIRECT
void BASIC_TIMER_Init(unsigned char Prescale, unsigned char ReloadValue)
#else
void BASIC_TIMER_Init(volatile BASIC_TIMER_TypeDef* TIMER, unsigned char Prescale, unsigned char ReloadValue)
#endif
{
  BASIC_TIMER_MASK.CR1.REG = 0;
  BASIC_TIMER_MASK.CNTR = 0;
  BASIC_TIMER_MASK.ARR = ReloadValue;
  BASIC_TIMER_MASK.PSCR.REG = Prescale;
  BASIC_TIMER_MASK.CR1.REG = BIT7 | BIT2 | BIT0;
}