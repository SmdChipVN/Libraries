#ifndef _UART_H_
#define _UART_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(SR, unsigned char,                     //              0xC0            Status register
    const PE                            , 1,    //0             0               Parity error
    const FE                            , 1,    //1             0               Framing error
    const NF                            , 1,    //2             0               Noise flag
    const OR                            , 1,    //3             0               Overrun error
    const IDLE                          , 1,    //4             0               IDLE line detected
    RXNE                                , 1,    //5             0               Read data register not empty
    TC                                  , 1,    //6             1               Transmission complete
    const TXE, 1);                              //7             1               Transmit data register empty
  unsigned char DR;                             //              0x--            Data register
  BRUNION_16x8(BRR,,                            //              0x0000          Baud rate register, BRR2 must be programmed before BRR1
    r0, r1,
    
    DIV_11_4                            , 8,
    DIV_15_12                           , 4,
    DIV_3_0                             , 4);
  BUNION(CR1, unsigned char,                    //              0x00            Control register 1
    PIEN                                , 1,    //0             0               Parity interrupt enable
    PS                                  , 1,    //1             0               Parity selection
    PCEN                                , 1,    //2             0               Parity control enable
    WAKE                                , 1,    //3             0               Wakeup method
    M                                   , 1,    //4             0               word length
    UARTD                               , 1,    //5             0               UART Disable (for low power consumption)
    T8                                  , 1,    //6             0               Transmit data bit 8
    R8                                  , 1);   //7             0               Receive Data bit 8
  BUNION(CR2, unsigned char,                    //              0x00            Control register 2
    SBK                                 , 1,    //0             0               Send break
    RWU                                 , 1,    //1             0               Receiver wakeup
    REN                                 , 1,    //2             0               Receiver enable
    TEN                                 , 1,    //3             0               Transmitter enable
    ILIEN                               , 1,    //4             0               IDLE Line interrupt enable
    RIEN                                , 1,    //5             0               Receiver interrupt enable
    TCIEN                               , 1,    //6             0               Transmission complete interrupt enable
    TIEN                                , 1);   //7             0               Transmitter interrupt enable
  BUNION(CR3, unsigned char,                     //              0x00            Control register 3
    LBCL                                , 1,    //0             0               Last bit clock pulse
    CPHA                                , 1,    //1             0               Clock phase
    CPOL                                , 1,    //2             0               Clock polarity
    CKEN                                , 1,    //3             0               Clock enable
    STOP                                , 2,    //4-5           0               STOP bits
    LINEN                               , 1,    //6             0               LIN mode enable
    _reserved                           , 1);
  BUNION(CR4, unsigned char,                    //              0x00            Control register 4
    ADD                                 , 4,    //0:3           0               Address of the UART node
    LBDF                                , 1,    //4             0               LIN Break Detection Flag
    LBDL                                , 1,    //5             0               LIN Break Detection Length
    LBDIEN                              , 1,    //6             0               LIN Break Detection Interrupt Enable
    _reserved                           , 1);
  BUNION(CR5, unsigned char,                    //              0x00            Control register 5
    _reserved                           , 1,
    IREN                                , 1,    //1             0               IrDA mode Enable
    IRLP                                , 1,    //2             0               IrDA Low Power 
    HDSEL                               , 1,    //3             0               Half-Duplex Selection
    const NACK                          , 1,    //4             0               Smartcard NACK enable
    const SCEN                          , 1,    //5             0               Smartcard mode enable
    _reserved1                          , 2);
} BASE_UART_TypeDef;
//==============================================================================================================================================================
typedef struct  
{
  BASE_UART_TypeDef;
  unsigned char GTR;                            //              0x00            Guard time register
  unsigned char PSCR;                           //              0x00            Prescaler register
} UART1_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  BASE_UART_TypeDef;
  BUNION(CR6, unsigned char,                    //              0x00            Control register 6
    LSF                                 , 1,    //0             0               LIN Sync Field
    LHDF                                , 1,    //1             0               LIN Header Detection Flag
    LHDIEN                              , 1,    //2             0               LIN Header Detection Interrupt Enable
    _reserved                           , 1,
    LASE                                , 1,    //4             0               LIN automatic resynchronisation enable
    LSLV                                , 1,    //5             0               LIN Slave Enable
    _reserved1                          , 1,    //
    LDUM                                , 1);   //7             0               LIN Divider Update Method
  unsigned char GTR;                            //              0x00            Guard time register
  unsigned char PSCR;                           //              0x00            Prescaler register
} UART_2_4_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  BASE_UART_TypeDef;
  BUNION(CR6, unsigned char,                    //              0x00            Control register 6
    LSF                                 , 1,    //0             0               LIN Sync Field
    LHDF                                , 1,    //1             0               LIN Header Detection Flag
    LHDIEN                              , 1,    //2             0               LIN Header Detection Interrupt Enable
    _reserved                           , 1,
    LASE                                , 1,    //4             0               LIN automatic resynchronisation enable
    LSLV                                , 1,    //5             0               LIN Slave Enable
    _reserved1                          , 1,
    LDUM                                , 1);   //7             0               LIN Divider Update Method
} UART3_TypeDef;
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
typedef struct
{
  unsigned short Baudrate;                      //              96              9600 -> 96
  BUNION(Mode, unsigned char,
    _reserved                           , 2,
    RX_ENABLE                           , 1,    //2             0
    TX_ENABLE                           , 1,    //3             1
    _reserved1                          , 1,              
    RX_INTERRUPT                        , 1,    //5             0
    _reserved2                          , 2);   //
} UARTInit_TypeDef;
void UART2_4_Init(volatile UART_2_4_TypeDef* UART, const UARTInit_TypeDef* UARTInit);
void UART2_4_WriteByte(volatile UART_2_4_TypeDef* UART, unsigned char Data);
void UART2_4_WriteBytes(volatile UART_2_4_TypeDef* UART, unsigned char* Data, unsigned char Length);

#endif