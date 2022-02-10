#include <n76e003.h>
#include <gpio.h>

void GPIO0_Mode(unsigned char PIN, GPIO_MODE Mode)
{
  if (Mode & 0x01)
    P0M2.REG |= PIN;
  else
    P0M2.REG &= ~PIN;
  if (Mode & 0x02)
    P0M1.REG |= PIN;
  else
    P0M1.REG &= ~PIN;
}
void GPIO1_Mode(unsigned char PIN, GPIO_MODE Mode)
{
  if (Mode & 0x01)
    P1M2.REG |= PIN;
  else
    P1M2.REG &= ~PIN;
  if (Mode & 0x02)
    P1M1.REG |= PIN;
  else
    P1M1.REG &= ~PIN;
}
void GPIO3_Mode(unsigned char PIN, GPIO_MODE Mode)
{
  if (Mode & 0x01)
    P3M2.REG |= PIN;
  else
    P3M2.REG &= ~PIN;
  if (Mode & 0x02)
    P3M1.REG |= PIN;
  else
    P3M1.REG &= ~PIN;
}