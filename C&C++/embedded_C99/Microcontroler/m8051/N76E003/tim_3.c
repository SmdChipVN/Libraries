#include <n76e003_regsmap.h>

void TIM3_Init()
{
  RL3 = 0xE6 ; RH3 = 0xFF; 
  T3CON.REG = BIT3;
}