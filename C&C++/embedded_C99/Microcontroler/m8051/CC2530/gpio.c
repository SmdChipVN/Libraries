#include <gpio.h>

void GPIO_Mode0(unsigned char Pin, GPIO_MODE Mode)
{
  if (Mode == GPIO_MODE_PERIPHERAL_PIN)
    P0_SEL.REG |= Pin;
  else
  {
    P0_SEL.REG &= ~Pin;
    if (Mode & 0x04)
      P0_DAT.REG |= Pin;
    else
      P0_DAT.REG &= ~Pin;
    if (Mode & 0x08)
      P0_DIR.REG |= Pin;
    else
      P0_DIR.REG &= ~Pin;
    if (Mode & 0x02)
      P0_INP.REG |= Pin;
    else
      P0_INP.REG &= ~Pin;
    if (Mode & 0x01)
      P0_IEN.REG |= Pin;
    else
      P0_IEN.REG &= ~Pin;
  }
}
void GPIO_Mode1(unsigned char Pin, GPIO_MODE Mode)
{
  if (Mode == GPIO_MODE_PERIPHERAL_PIN)
    P1_SEL.REG |= Pin;
  else
  {
    P1_SEL.REG &= ~Pin;
    if (Mode & 0x04)
      P0_DAT.REG |= Pin;
    else
      P1_DAT.REG &= ~Pin;
    if (Mode & 0x08)
      P1_DIR.REG |= Pin;
    else
      P1_DIR.REG &= ~Pin;
    if (Mode & 0x02)
      P1_INP.REG |= Pin;
    else
      P1_INP.REG &= ~Pin;
    if (Mode & 0x01)
      P1_IEN.REG |= Pin;
    else
      P1_IEN.REG &= ~Pin;
  }
}
void GPIO_Mode2(unsigned char Pin, GPIO_MODE Mode)
{
  if (Mode == GPIO_MODE_PERIPHERAL_PIN)
    P2_SEL.REG |= Pin;
  else
  {
    P2_SEL.REG &= ~Pin;
    if (Mode & 0x04)
      P2_DAT.REG |= Pin;
    else
      P2_DAT.REG &= ~Pin;
    if (Mode & 0x08)
      P2_DIR.REG |= Pin;
    else
      P2_DIR.REG &= ~Pin;
    if (Mode & 0x02)
      P2_INP.REG |= Pin;
    else
      P2_INP.REG &= ~Pin;
    if (Mode & 0x01)
      P2_IEN.REG |= Pin;
    else
      P2_IEN.REG &= ~Pin;
  }
}