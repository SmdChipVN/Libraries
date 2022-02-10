#include <uart.h>

void UART2_4_Init(volatile UART_2_4_TypeDef* UART, const UARTInit_TypeDef* UARTInit)
{
  unsigned short baud_value = 160000 / UARTInit->Baudrate;
  UART->BRR.REGS.r1 = ((baud_value >> 8) & 0xF0) | (baud_value & 0x0F);
  UART->BRR.REGS.r0 = (baud_value >> 4) & 0xFF;  
  UART->CR1.REG = 0;
  UART->CR2.REG = UARTInit->Mode.REG;
}
void UART2_4_WriteByte(volatile UART_2_4_TypeDef* UART, unsigned char Data)
{
  while (!UART->SR.BITS.TXE);
  UART->DR = Data;
}
void UART2_4_WriteBytes(volatile UART_2_4_TypeDef* UART, unsigned char* Data, unsigned char Length)
{
  while (Length--)
    UART2_4_WriteByte(UART, *Data++);
}