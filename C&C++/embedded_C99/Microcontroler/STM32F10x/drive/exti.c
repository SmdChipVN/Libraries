#include <exti.h>

static void _config(volatile unsigned int* reg, volatile unsigned int* rise_reg, unsigned int pin, unsigned int mode)
{
#define fall_reg        rise_reg[1]
  if (mode)
  {
    *reg |= pin;
    if (mode & EXTI_MODE_RISING)
      *rise_reg |= pin;
    else
      *rise_reg &= ~pin;
    if (mode & EXTI_MODE_FALLING)
      fall_reg |= pin;
    else
      fall_reg &= ~pin;
  }
  else
    *reg &= ~pin;
#undef fall_reg
}

void EXTI_Interrupt(volatile EXTI_TypeDef* EXTI, EXTIName_TypeDef InterruptMask, EXTI_MODE Mode)
{
  _config(&EXTI->IMR.REG, &EXTI->RTSR.REG, InterruptMask.REG, Mode);
}

void EXTI_WeakupEvent(volatile EXTI_TypeDef* EXTI, EXTIName_TypeDef WeakupEventMask, EXTI_MODE Mode)
{
  _config(&EXTI->EMR.REG, &EXTI->RTSR.REG, WeakupEventMask.REG, Mode);
}