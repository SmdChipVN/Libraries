#include <beep.h>
#include <gpio.h>

extern __no_init volatile BEEP_TypeDef BEEP;
extern __no_init volatile GPIO_TypeDef GPIOD;

void BEEP_Init(unsigned short Frequency)
{
  BEEP_SetFrequency(Frequency);
}

void BEEP_SetFrequency(unsigned short Frequency)
{
  BEEP.CSR.REG = BIT6 | 0x1E;
}