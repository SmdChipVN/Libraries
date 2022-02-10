#ifndef _UART_H_
#define _UART_H_

void UART0_Init(unsigned int Baudrate);
void UART0_WriteByte(unsigned char Data);
void UART0_WriteBytes(const unsigned char* Data, unsigned short Length);

#endif