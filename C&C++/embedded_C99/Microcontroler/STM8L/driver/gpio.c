#include <gpio.h>

void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned char PIN, GPIO_MODE Mode)
{
  //DDR
  if (Mode & (0x01 << 2))
    GPIO->DDR.REG |= PIN;
  else
    GPIO->DDR.REG &= ~PIN;
  //CR1
  if (Mode & (0x01 << 1))
    GPIO->CR1.REG |= PIN;
  else
    GPIO->CR1.REG &= ~PIN;
  //CR2
  if (Mode & (0x01 << 0))
    GPIO->CR2.REG |= PIN;
  else
    GPIO->CR2.REG &= ~PIN;
}