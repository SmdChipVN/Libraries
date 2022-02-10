#include <common.h>
#include <spi.h>

void SPI_Init(volatile SPI_TypeDef* SPI, SPIInit_TypeDef* SPIInit)
{
  if (!SPIInit)
  {
    SPIInit = &((SPIInit_TypeDef){
      .Mode = {.BITS = {.Phase = 0, .Polarity = 0, .IsMaster = 1, .Baudrate_Div = 2, .IsLowBitFirst = 0, .IsFrame16Bit = 0, .IsHalfDuplex = 0, }},
      .DMA = {.BITS = {.Rx = 0, .Tx = 0, }},
      .Interrupt = {.BITS = {.Error = 0, .Rx_NotEmpty = 0, .Tx_Empty = 0, }},
    });
  }
  if (SPIInit->Mode.BITS.IsMaster)
    SPIInit->REG |= BIT14 | BIT9 | BIT18;
  else if (SPIInit->Mode.BITS.IsHalfDuplex)
    SPIInit->REG |= BIT10;
  SPI->CR2.REG = SPIInit->Interrupt.REG | SPIInit->DMA.REG;
  SPI->CR1.REG = SPIInit->REG | BIT6;  
}

void SPI_Write(volatile SPI_TypeDef* SPI, unsigned int Data)
{
  SPI->DR = Data;
  while (!SPI->SR.BITS.TXE);
}
unsigned int SPI_Read(volatile SPI_TypeDef* SPI)
{
  while (!SPI->SR.BITS.RXNE);
  return SPI->DR;
}
unsigned int SPI_WriteRead(volatile SPI_TypeDef* SPI, unsigned int Data)
{
  SPI_Write(SPI, Data);
  return SPI_Read(SPI);
}

void SPI_Writes(volatile SPI_TypeDef* SPI, void* Data, unsigned int Length)
{
  unsigned int index;
  if (SPI->CR1.BITS.DFF)
  {
    for (index = 0; index < Length; index++)
    {
      SPI->DR = ((unsigned short*)Data)[index];
      while (!SPI->SR.BITS.TXE);
    }
  }
  else
  {
    for (index = 0; index < Length; index++)
    {
      SPI->DR = ((unsigned char*)Data)[index];
      while (!SPI->SR.BITS.TXE);
    }
  }
}
/*NOTE: pause spi bus (by interrupt, usb,...) maybe get wrong rx data*/
void SPI_Reads(volatile SPI_TypeDef* SPI, void* Contain, unsigned int Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }  
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  if (SPI->CR1.BITS.DFF)
  {
    unsigned int index;
    for (index = 0; index < Length; index++)
    {
      SPI->DR = index;
      while (!SPI->SR.BITS.TXE);
      ((unsigned short*)Contain)[index] = SPI->DR;
    }
  }
  else
  {
    unsigned int index;
    for (index = 0; index < Length; index++)
    {
      SPI->DR = (unsigned char)index;
      while (!SPI->SR.BITS.TXE);
      ((unsigned char*)Contain)[index] = SPI->DR;
    }
  }
}
void SPI_WriteReads(volatile SPI_TypeDef* SPI, void* Contain, unsigned int Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }
  if (SPI->CR1.BITS.DFF)
  {
    unsigned int index;
    for (index = 0; index < Length; index++)
    {
      SPI->DR = index;
      while (!SPI->SR.BITS.TXE);
      while (!SPI->SR.BITS.RXNE);
      ((unsigned short*)Contain)[index] = SPI->DR;
    }
  }
  else
  {
    unsigned int index;
    for (index = 0; index < Length; index++)
    {
      SPI->DR = (unsigned char)index;
      while (!SPI->SR.BITS.TXE);
      while (!SPI->SR.BITS.RXNE);
      ((unsigned char*)Contain)[index] = SPI->DR;
    }
  }
}


