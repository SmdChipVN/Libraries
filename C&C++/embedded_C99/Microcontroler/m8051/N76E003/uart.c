#include <n76e003_regsmap.h>
#include <tim_3.h>

void UART0_Init(unsigned int Baudrate)
{
  TIM3_Init();
  T3CON.BITS.BRCK = 1;  
  SCON.REG = BIT6;
}

void UART0_WriteByte(unsigned char Data)
{
  SBUF = Data;
  while (!SCON.BITS.TI);
  SCON.BITS.TI = 0;
}

void UART0_WriteBytes(const unsigned char* Data, unsigned short Length)
{
  while (Length--)
    UART0_WriteByte(*Data++);
}