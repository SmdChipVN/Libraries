#ifndef _UART_H_
#define _UART_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(SR, unsigned char,     //0x0           0xC0            Status register
    const PE            , 1,    //0             0               Parity error
    const FE            , 1,    //1             0               Framing error
    const NF            , 1,    //2             0               Noise flag
    const OR            , 1,    //3             0               Overrun error
    const IDLE          , 1,    //4             0               IDLE line detected
    const RXNE          , 1,    //5             0               Read data register not empty
    TC                  , 1,    //6             1               Transmission complete
    const TXE           , 1);   //7             1               Transmit data register empty
  unsigned char DR;             //0x1           0x--            Data register
  BRUNION_16x8(BRR, , r1, r2,   //0x2-0x3       0x0000          Baud rate register  
      DIV_11_4          , 8,    //0:7           0
      DIV_3_0           , 4,    //0:3           0
      DIV_15_12         , 4);   //4:7           0
  BUNION(CR1, unsigned char,     //0x4           0x00            Control register 1
    PIEN                , 1,    //0             0               Parity interrupt enable
    PS                  , 1,    //1             0               Parity selection
    PCEN                , 1,    //2             0               Parity control enable
    WAKE                , 1,    //3             0               Wakeup method
    M                   , 1,    //4             0               word length
    USARTD              , 1,    //5             0               USART disable (for low power consumption)
    TX8                 , 1,    //6             0               Transmit data bit 8
    RX8                 , 1);   //7             0               Receive data bit 8
  BUNION(CR2, unsigned char,     //0x5           0x00            Control register 2
    SBK                 , 1,    //0             0               Send break
    RWU                 , 1,    //1             0               Receiver wakeup
    REN                 , 1,    //2             0               Receiver enable
    TEN                 , 1,    //3             0               Transmitter enable
    ILIEN               , 1,    //4             0               IDLE Line interrupt enable
    RIEN                , 1,    //5             0               Receiver interrupt enable
    TCIEN               , 1,    //6             0               Transmission complete interrupt enable
    TIEN                , 1);   //7             0               Transmitter interrupt enable
  BUNION(CR3, unsigned char,     //0x6           0x00            Control register 3
    LBCL                , 1,    //0             0               Last bit clock pulse
    CPHA                , 1,    //1             0               Clock phase
    CPOL                , 1,    //2             0               Clock polarity
    CKEN                , 1,    //3             0               USART_CK pin enable
    STOP                , 2,    //4             0               STOP bits
    _Reserved           , 2);
  BUNION(CR4, unsigned char,     //0x7           0x00            Control register 4
    ADD                 , 4,    //0:3           0               Address of the USART node
    _Reserved           , 4);
  BUNION(CR5, unsigned char,     //0x8           0x00            Control register 5
    EIE                 , 1,    //0             0               Error Interrupt enable
    IREN                , 1,    //1             0               IrDA mode enable
    IRLP                , 1,    //2             0               IrDA Low power
    HDSEL               , 1,    //3             0               Half duplex selection
    NACK                , 1,    //4             0               Smartcard NACK enable
    SCEN                , 1,    //5             0               Smartcard mode enable
    DMAR                , 1,    //6             0               DMA Enable receiver
    DMAT                , 1);   //7             0               DMA Enable transmitter
  unsigned char GTR;            //0x9           0x00            Guard time register
  unsigned char PSCR;           //0xA           0x00            Prescaler register
} UART_TypeDef;
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#define UART_EnableDMA_TX(UART)                 (UART)->CR5.REG |= BIT7
#define UART_DisableDMA_TX(UART)                (UART)->CR5.REG &= ~BIT7
#define UART_EnableDMA_RX(UART)                 (UART)->CR5.REG |= BIT6
#define UART_DisableDMA_RX(UART)                (UART)->CR5.REG &= ~BIT6
//======================================================================================================================
#include <config.h>
typedef struct
{
  BUNION(Mode, unsigned char,    //              0x0C
    _Reserved0          , 2,
    RX                  , 1,    //2             1
    TX                  , 1,    //3             1
    _Reserved1          , 1,
    RX_IT               , 1,    //5             0
    _Reserved2          , 2);
  unsigned short Baudrate;      //              96              (x100 Hz)
} UARTInit_TypeDef;
//======================================================================================================================
/*Example:
CLK.PCKENR1.BITS.UART1 = 1;
UARTInit_TypeDef UARTInit = {
  .Mode = {
    .BITS = {
      .RX = 1,
      .TX = 1,
      .RX_IT = 0,
    },
  },
  .Baudrate = 96,
};
UART_Init(&UARTInit);   //#define UART_DIRECT   UART1
*/
#ifdef UART_DIRECT
  void UART_Init(const UARTInit_TypeDef* UARTInit);
  void UART_WriteByte(unsigned char Data);
  void UART_WriteBytes(const unsigned char* Data, unsigned short Length);
#else
  void UART_Init(volatile UART_TypeDef* UART, const UARTInit_TypeDef* UARTInit);
  void UART_WriteByte(volatile UART_TypeDef* UART, unsigned char Data);
  void UART_WriteBytes(volatile UART_TypeDef* UART, const unsigned char* Data, unsigned short Length);
#endif

#endif