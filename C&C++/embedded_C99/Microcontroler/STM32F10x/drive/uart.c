#include <uart.h>
#include <bitband.h>
#include <common.h>

void UART_Init(volatile UART_TypeDef* UART, unsigned int F_UART, unsigned int Baudrate)
{  
  F_UART *= 1000;
  UART->CR1.BITS.UE = 0;
  F_UART >>= 4;
  UART->BRR.BITS.MANTISSA = F_UART / Baudrate;
  F_UART %= Baudrate;
  UART->BRR.BITS.FRACTION = (F_UART << 4) / Baudrate;
  UART->CR1.REG |= BIT13 | BIT3 | BIT2;
}

void UART_WriteBytes(volatile UART_TypeDef* UART, const unsigned char* Data, unsigned int Length)
{
  UART_BITBAND_TypeDef* UART_BITBAND = (UART_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)UART, 0);
  for (unsigned int i = 0; i < Length; i++)
  {
    while (!UART_BITBAND->SR.TXE);
    UART->DR = Data[i];
  }
}