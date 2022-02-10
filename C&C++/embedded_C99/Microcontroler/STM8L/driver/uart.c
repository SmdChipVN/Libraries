#include <uart.h>

static const UARTInit_TypeDef uart_default = {
  .Mode = {
    .BITS = {
      .RX = 1,
      .TX = 1,
      .RX_IT = 0,
    },
  },
  //.Baudrate = 96,
  .Baudrate = 576,
};

#ifdef UART_DIRECT
  extern __no_init volatile UART_TypeDef UART_DIRECT;
  #define UART_MASK     UART_DIRECT
#else
  #define UART_MASK     (*UART)
#endif

#ifdef UART_DIRECT
void UART_Init(const UARTInit_TypeDef* UARTInit)
#else
void UART_Init(volatile UART_TypeDef* UART, const UARTInit_TypeDef* UARTInit)
#endif
{  
  if (!UARTInit)
    UARTInit = &uart_default;  
#if (UART_BAUD)
  #if (F_SYS == 16000)
    #if (UART_BAUD == 4000)
      UART_MASK.BRR.REGS.r2 = ((40 >> 8) & 0xF0) | (40 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (40 >> 4) & 0xFF;
    #elif (UART_BAUD == 2000)
      UART_MASK.BRR.REGS.r2 = ((80 >> 8) & 0xF0) | (80 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (80 >> 4) & 0xFF;
    #elif (UART_BAUD == 1152)
      UART_MASK.BRR.REGS.r2 = ((140 >> 8) & 0xF0) | (140 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (140 >> 4) & 0xFF;
    #elif (UART_BAUD == 1000)
      UART_MASK.BRR.REGS.r2 = ((161 >> 8) & 0xF0) | (161 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (161 >> 4) & 0xFF;
    #elif (UART_BAUD == 576)
      UART_MASK.BRR.REGS.r2 = ((280 >> 8) & 0xF0) | (280 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (280 >> 4) & 0xFF;
    #elif (UART_BAUD == 384)
      UART_MASK.BRR.REGS.r2 = ((420 >> 8) & 0xF0) | (420 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (420 >> 4) & 0xFF;
    #elif (UART_BAUD == 192)
      UART_MASK.BRR.REGS.r2 = ((838 >> 8) & 0xF0) | (838 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (838 >> 4) & 0xFF;
    #elif (UART_BAUD == 48)
      UART_MASK.BRR.REGS.r2 = ((3350 >> 8) & 0xF0) | (3350 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (3350 >> 4) & 0xFF;
    #elif (UART_BAUD == 24)
      UART_MASK.BRR.REGS.r2 = ((6690 >> 8) & 0xF0) | (6690 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (6690 >> 4) & 0xFF;
    #elif (UART_BAUD == 12)
      UART_MASK.BRR.REGS.r2 = ((13390 >> 8) & 0xF0) | (13390 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (13390 >> 4) & 0xFF;
    #else
      UART_MASK.BRR.REGS.r2 = ((1672 >> 8) & 0xF0) | (1672 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (1672 >> 4) & 0xFF;
    #endif
  #elif (F_SYS == 8000)
    #if (UART_BAUD == 4000)
      UART_MASK.BRR.REGS.r2 = ((20 >> 8) & 0xF0) | (20 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (20 >> 4) & 0xFF;
    #elif (UART_BAUD == 2000)
      UART_MASK.BRR.REGS.r2 = ((40 >> 8) & 0xF0) | (40 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (40 >> 4) & 0xFF;
    #elif (UART_BAUD == 1152)
      UART_MASK.BRR.REGS.r2 = ((70 >> 8) & 0xF0) | (70 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (70 >> 4) & 0xFF;
    #elif (UART_BAUD == 1000)
      UART_MASK.BRR.REGS.r2 = ((80 >> 8) & 0xF0) | (80 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (80 >> 4) & 0xFF;
    #elif (UART_BAUD == 576)
      UART_MASK.BRR.REGS.r2 = ((140 >> 8) & 0xF0) | (140 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (140 >> 4) & 0xFF;
    #elif (UART_BAUD == 384)
      UART_MASK.BRR.REGS.r2 = ((209 >> 8) & 0xF0) | (209 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (209 >> 4) & 0xFF;
    #elif (UART_BAUD == 192)
      UART_MASK.BRR.REGS.r2 = ((420 >> 8) & 0xF0) | (420 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (420 >> 4) & 0xFF;
    #elif (UART_BAUD == 48)
      UART_MASK.BRR.REGS.r2 = ((1672 >> 8) & 0xF0) | (1672 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (1672 >> 4) & 0xFF;
    #elif (UART_BAUD == 24)
      UART_MASK.BRR.REGS.r2 = ((3350 >> 8) & 0xF0) | (3350 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (3350 >> 4) & 0xFF;
    #elif (UART_BAUD == 12)
      UART_MASK.BRR.REGS.r2 = ((6690 >> 8) & 0xF0) | (6690 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (6690 >> 4) & 0xFF;
    #else
      UART_MASK.BRR.REGS.r2 = ((838 >> 8) & 0xF0) | (838 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (838 >> 4) & 0xFF;
    #endif
  #elif (F_SYS == 4000)
    #if (UART_BAUD == 2000)
      UART_MASK.BRR.REGS.r2 = ((20 >> 8) & 0xF0) | (20 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (20 >> 4) & 0xFF;
    #elif (UART_BAUD == 1152)
      UART_MASK.BRR.REGS.r2 = ((35 >> 8) & 0xF0) | (35 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (35 >> 4) & 0xFF;
    #elif (UART_BAUD == 1000)
      UART_MASK.BRR.REGS.r2 = ((40 >> 8) & 0xF0) | (40 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (40 >> 4) & 0xFF;
    #elif (UART_BAUD == 576)
      UART_MASK.BRR.REGS.r2 = ((70 >> 8) & 0xF0) | (70 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (70 >> 4) & 0xFF;
    #elif (UART_BAUD == 384)
      UART_MASK.BRR.REGS.r2 = ((104 >> 8) & 0xF0) | (104 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (104 >> 4) & 0xFF;
    #elif (UART_BAUD == 192)
      UART_MASK.BRR.REGS.r2 = ((209 >> 8) & 0xF0) | (209 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (209 >> 4) & 0xFF;
    #elif (UART_BAUD == 48)
      UART_MASK.BRR.REGS.r2 = ((838 >> 8) & 0xF0) | (838 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (838 >> 4) & 0xFF;
    #elif (UART_BAUD == 24)
      UART_MASK.BRR.REGS.r2 = ((1672 >> 8) & 0xF0) | (1672 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (1672 >> 4) & 0xFF;
    #elif (UART_BAUD == 12)
      UART_MASK.BRR.REGS.r2 = ((3340 >> 8) & 0xF0) | (3340 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (3340 >> 4) & 0xFF;
    #else
      UART_MASK.BRR.REGS.r2 = ((420 >> 8) & 0xF0) | (420 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (420 >> 4) & 0xFF;
    #endif
  #elif (F_SYS == 2000)
    #if (UART_BAUD == 1000)
      UART_MASK.BRR.REGS.r2 = ((20 >> 8) & 0xF0) | (20 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (20 >> 4) & 0xFF;
    #elif (UART_BAUD == 576)
      UART_MASK.BRR.REGS.r2 = ((35 >> 8) & 0xF0) | (35 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (35 >> 4) & 0xFF;
    #elif (UART_BAUD == 384)
      UART_MASK.BRR.REGS.r2 = ((52 >> 8) & 0xF0) | (52 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (52 >> 4) & 0xFF;
    #elif (UART_BAUD == 192)
      UART_MASK.BRR.REGS.r2 = ((104 >> 8) & 0xF0) | (104 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (104 >> 4) & 0xFF;
    #elif (UART_BAUD == 48)
      UART_MASK.BRR.REGS.r2 = ((420 >> 8) & 0xF0) | (420 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (420 >> 4) & 0xFF;
    #elif (UART_BAUD == 24)
      UART_MASK.BRR.REGS.r2 = ((838 >> 8) & 0xF0) | (838 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (838 >> 4) & 0xFF;
    #elif (UART_BAUD == 12)
      UART_MASK.BRR.REGS.r2 = ((1672 >> 8) & 0xF0) | (1672 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (1672 >> 4) & 0xFF;
    #else
      UART_MASK.BRR.REGS.r2 = ((209 >> 8) & 0xF0) | (209 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (209 >> 4) & 0xFF;
    #endif
  #elif (F_SYS == 1000)
    #if (UART_BAUD == 384)
      UART_MASK.BRR.REGS.r2 = ((26 >> 8) & 0xF0) | (26 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (26 >> 4) & 0xFF;
    #elif (UART_BAUD == 192)
      UART_MASK.BRR.REGS.r2 = ((52 >> 8) & 0xF0) | (52 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (52 >> 4) & 0xFF;
    #elif (UART_BAUD == 48)
      UART_MASK.BRR.REGS.r2 = ((209 >> 8) & 0xF0) | (209 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (209 >> 4) & 0xFF;
    #elif (UART_BAUD == 24)
      UART_MASK.BRR.REGS.r2 = ((420 >> 8) & 0xF0) | (420 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (420 >> 4) & 0xFF;
    #elif (UART_BAUD == 12)
      UART_MASK.BRR.REGS.r2 = ((838 >> 8) & 0xF0) | (838 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (833 >> 4) & 0xFF;
    #else
      UART_MASK.BRR.REGS.r2 = ((104 >> 8) & 0xF0) | (104 & 0x0F);
      UART_MASK.BRR.REGS.r1 = (104 >> 4) & 0xFF;
    #endif
  #else
  {
    unsigned long baud;
    baud = UARTInit->Baudrate;
    baud = ((unsigned long)F_SYS * 10 + baud - 1) / baud;
    UART_MASK.BRR.REGS.r2 = ((baud >> 8) & 0xF0) | (baud & 0x0F);
    UART_MASK.BRR.REGS.r1 = baud >> 4;
  }
  #endif
#else
{
  unsigned long baud;
  baud = UARTInit->Baudrate;
  baud = ((unsigned long)F_SYS * 10 + baud - 1) / baud;
  UART_MASK.BRR.REGS.r2 = ((baud >> 8) & 0xF0) | (baud & 0x0F);
  UART_MASK.BRR.REGS.r1 = baud >> 4;
}
#endif
  UART_MASK.CR2.REG = UARTInit->Mode.REG;
}

#ifdef UART_DIRECT
void UART_WriteByte(unsigned char Data)
#else
void UART_WriteByte(volatile UART_TypeDef* UART, unsigned char Data)
#endif
{
  while (!UART_MASK.SR.BITS.TXE);
  UART_MASK.DR = Data;
}

#ifdef UART_DIRECT
void UART_WriteBytes(const unsigned char* Data, unsigned short Length)
#else
void UART_WriteBytes(volatile UART_TypeDef* UART, const unsigned char* Data, unsigned short Length)
#endif
{
  while (Length--)
  {
    while (!UART_MASK.SR.BITS.TXE);
    UART_MASK.DR = *Data++;
  }
}