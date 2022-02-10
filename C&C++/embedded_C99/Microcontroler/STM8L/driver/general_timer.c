#include <general_timer.h>

#ifdef GENERAL_TIMER_DIRECT
  extern __no_init volatile GENERAL_TIMER_TypeDef GENERAL_TIMER_DIRECT;
  #define GENERAL_TIMER_MASK    GENERAL_TIMER_DIRECT
#else
  #define GENERAL_TIMER_MASK    (*TIMER)
#endif

#ifdef GENERAL_TIMER_DIRECT
void GENERAL_TIMER_Init(unsigned char Prescale, unsigned short ReloadValue)
#else
void GENERAL_TIMER_Init(volatile GENERAL_TIMER_TypeDef* TIMER, unsigned char Prescale, unsigned short ReloadValue)
#endif
{
  GENERAL_TIMER_MASK.CR1.REG = 0;
  GENERAL_TIMER_MASK.CNTR.REGS.HIGH = 0; GENERAL_TIMER_MASK.CNTR.REGS.LOW = 0;
  GENERAL_TIMER_MASK.PSCR.REG = Prescale;
  GENERAL_TIMER_MASK.ARR.REGS.HIGH = ReloadValue >> 8;
  GENERAL_TIMER_MASK.ARR.REGS.LOW = ReloadValue;
  GENERAL_TIMER_MASK.CR1.REG = BIT7 | BIT0;
}
#ifdef GENERAL_TIMER_DIRECT
void GENERAL_TIMER_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
#else
void GENERAL_TIMER_GeneratePWM(volatile GENERAL_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
#endif
{
  static const unsigned char cn_ref[3][2] = {{0x03, 0x30}, {0x01, 0x10}, {0xF0, 0x0F},};
  Channel &= BIT1;
  (&GENERAL_TIMER_MASK.CCR1.REGS.HIGH)[Channel] = Duty >> 8;
  (&GENERAL_TIMER_MASK.CCR1.REGS.HIGH)[Channel + 1] = Duty;
  (&GENERAL_TIMER_MASK.CCMR1.REG)[Channel >>= 1] = BIT6 | BIT5 | BIT3;
  GENERAL_TIMER_MASK.CCER.REG &= cn_ref[2][Channel];
  GENERAL_TIMER_MASK.CCER.REG |= cn_ref[IDLE_IsHigh][Channel];
  GENERAL_TIMER_MASK.BKR.BITS.MOE = 1;
}