#include <advanced_timer.h>

#ifdef ADVANCED_TIMER_DIRECT
  extern __no_init volatile ADVANCED_TIMER_TypeDef ADVANCED_TIMER_DIRECT;
  #define ADVANCED_TIMER_MASK   ADVANCED_TIMER_DIRECT
#else
  #define ADVANCED_TIMER_MASK   (*TIMER)
#endif
#ifdef ADVANCED_TIMER_DIRECT
void ADVANCED_TIMER_Init(unsigned short Prescale, unsigned short ReloadValue)
#else
void ADVANCED_TIMER_Init(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned short Prescale, unsigned short ReloadValue)
#endif
{
  ADVANCED_TIMER_MASK.CR1.REG = 0;
  ADVANCED_TIMER_MASK.PSCR.REGS.HIGH = Prescale >> 8;
  ADVANCED_TIMER_MASK.PSCR.REGS.LOW = Prescale;
  ADVANCED_TIMER_MASK.ARR.REGS.HIGH = ReloadValue >> 8;
  ADVANCED_TIMER_MASK.ARR.REGS.LOW = ReloadValue;
  ADVANCED_TIMER_MASK.CR1.REG = BIT7 | BIT0;
}
#ifdef ADVANCED_TIMER_DIRECT
void ADVANCED_TIMER_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
#else
void ADVANCED_TIMER_GeneratePWM(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh)
#endif
{
  static const unsigned char cn_ref[3][2] = {{0x03, 0x30}, {0x01, 0x10}, {0xF0, 0x0F},};
  Channel--;
  unsigned char index = Channel << 1;
  (&ADVANCED_TIMER_MASK.CCR1.REGS.HIGH)[index] = Duty >> 8;
  (&ADVANCED_TIMER_MASK.CCR1.REGS.HIGH)[index + 1] = Duty;
  (&ADVANCED_TIMER_MASK.CCMR1.REG)[Channel] = BIT6 | BIT5 | BIT3;
  index = Channel > 1;
  Channel &= 1;  
  (&ADVANCED_TIMER_MASK.CCER1.REG)[index] &= cn_ref[2][Channel];
  (&ADVANCED_TIMER_MASK.CCER1.REG)[index] |= cn_ref[IDLE_IsHigh][Channel];
  ADVANCED_TIMER_MASK.BKR.BITS.MOE = 1;
}