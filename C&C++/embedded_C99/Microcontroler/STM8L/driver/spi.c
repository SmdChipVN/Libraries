#include <spi.h>

void SPI_Begin(volatile SPI_TypeDef* SPI)
{
  SPI->CR2.REG = BIT0 | BIT1;
  SPI->CR1.REG = BIT2 | BIT6;
}

unsigned char SPI_WriteByte(volatile SPI_TypeDef* SPI, unsigned char Data)
{  
  SPI->DR = Data;
  while (!SPI->SR.BITS.TXE);
  while (!SPI->SR.BITS.RXNE);
  return SPI->DR;
}