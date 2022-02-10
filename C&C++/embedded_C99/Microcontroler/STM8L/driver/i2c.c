#include <i2c.h>

//slave mode
__weak void I2C_WeakupRequest()
{
  
}
__weak void I2C_WriteRequest(unsigned char Data)
{
  
}
__weak void I2C_ReadRequest()
{
  
}
__weak void I2C_StartRequest(unsigned char IsReadRequest)
{
  
}
__weak void I2C_StopRequest()
{
  
}
//master mode
void I2C_WriteBytes(unsigned char SlaveAddress, unsigned char* Data, unsigned short Length)
{
  
}
void I2C_ReadBytes(unsigned char SlaveAddress, unsigned char* Buffer, unsigned short Length)
{
  
}
//#pragma vector = I2C_IRQn
#pragma vector = 31
static __interrupt void I2C_ISR()
{
  if (I2C.SR2.BITS.WUFH)
  {
    I2C.SR2.REG = 0;
    I2C_WeakupRequest();
  }
  else
  {
    if (I2C.SR1.BITS.ADDR)
      I2C_StartRequest((unsigned char)I2C.SR3.BITS.TRA);
    else if (I2C.SR1.BITS.STOPF)
    {
      I2C.CR2.REG = BIT2;
      I2C_StopRequest();
    }
    else if (I2C.SR1.BITS.RXNE)
      I2C_WriteRequest(I2C.DR);
    else
      I2C_ReadRequest();
  }
}

void I2C_Init(const I2CInit_TypeDef* Info)
{
  //CLK.PCKENR1.BITS.I2C = 1;
  if (Info->IsMasterMode)
  {
    
  }
  else
  {
    I2C.ITR.REG = BIT1 | BIT2;
    I2C.OARL.REG = Info->SlaveAddress.REG;
    I2C.FREQR.REG = 1;                                 //1MHz
    I2C.OARH.REG = BIT6;
    if (Info->SlaveAddress.BITS.USING_ADDRESS_ZERO)
      I2C.CR1.REG = BIT0 | BIT6;
    else
      I2C.CR1.REG = BIT0;
    I2C.CR2.REG = BIT2;    
  }
}