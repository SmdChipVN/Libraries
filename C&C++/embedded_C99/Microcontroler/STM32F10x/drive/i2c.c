#include <i2c.h>

void I2C1_EV_IRQHandler()
{
  
}
void I2C1_ER_IRQHandler()
{
  
}
void I2C2_EV_IRQHandler()
{
  
}
void I2C2_ER_IRQHandler()
{
  
}
//====================================================================================================================================================
void I2C_Init(volatile I2C_TypeDef* I2C, unsigned int EdgeTime)
{
  I2C->CR1.REG = BIT15;
  
  I2C->CCR.BITS.CCR = EdgeTime;
  I2C->CR2.BITS.FREQ = 36;
  
  I2C->CR1.REG = BIT10;
}

void I2C_Perform(I2CTask_TypeDef* I2CTask)
{
  
}