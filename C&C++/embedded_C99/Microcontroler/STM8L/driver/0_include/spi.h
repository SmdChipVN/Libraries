#ifndef _SPI_H_
#define _SPI_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned char,     //0x0           0x00            SPI control register 1
    CPHA                , 1,    //0             0               
    CPOL                , 1,    //1             0               
    MSTR                , 1,    //2             0               Master selection
    BR                  , 3,    //3:5           0               Baud rate control: F_SPI = F_SYS/2^(BR + 1)
    SPE                 , 1,    //6             0               SPI enable
    LSBFIRST            , 1);   //7             0               Frame format
  BUNION(CR2, unsigned char,     //0x1           0x00            SPI control register 2
    SSI                 , 1,    //0             0               Internal slave select
    SSM                 , 1,    //1             0               Software slave management
    RXONLY              , 1,    //2             0               Receive only
    _Reserved           , 1,
    CRCNEXT             , 1,    //4             0               Transmit CRC next
    CRCEN               , 1,    //5             0               Hardware CRC calculation enable
    BDOE                , 1,    //6             0               Input/Output enable in bidirectional mode
    BDM                 , 1);   //7             0               Bidirectional data mode enable
  BUNION(ICR, unsigned char,     //0x2           0x00            SPI interrupt control register
    RXDMAEN             , 1,    //0             0               Rx Buffer DMA Enable
    TXDMAEN             , 1,    //1             0               Tx Buffer DMA Enable
    _Reserved           , 2,
    WKIE                , 1,    //4             0               Wakeup interrupt enable
    ERRIE               , 1,    //5             0               Error interrupt enable
    RXIE                , 1,    //6             0               RX buffer not empty interrupt enable
    TXIE                , 1);   //7             0               Tx buffer empty interrupt enable
  BUNION(SR, unsigned char,      //0x3           0x02            SPI status register
    RXNE                , 1,    //0             0               Receive buffer not empty
    TXE                 , 1,    //1             1               Transmit buffer empty
    _Reserved           , 1,
    WKUP                , 1,    //3             0               Wakeup flag
    CRCERR              , 1,    //4             0               CRC error flag
    MODF                , 1,    //5             0               Mode fault
    OVR                 , 1,    //6             0               Overrun flag
    BSY                 , 1);   //7             0               Busy flag
  unsigned char DR;             //0x4           0x00            SPI data register
  unsigned char CRCPR;          //0x5           0x07            SPI CRC polynomial register
  unsigned char RXCRCR;         //0x6           0x00            SPI Rx CRC register
  unsigned char TXCRCR;         //0x7           0x00            SPI Tx CRC register
} SPI_TypeDef;

/*
  Must enable clock for SPI first
  CLK.PCKENR1.BITS.SPI1 = 1;
*/
void SPI_Begin(volatile SPI_TypeDef* SPI);
unsigned char SPI_WriteByte(volatile SPI_TypeDef* SPI, unsigned char Data);

#endif