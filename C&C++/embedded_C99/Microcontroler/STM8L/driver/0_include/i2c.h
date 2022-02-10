#ifndef _I2C_H_
#define _I2C_H_

#define I2C_WriteByte(Data)     I2C.DR=Data
#define I2C_START()             I2C.CR2.BITS.START=1
#define I2C_NSTART()            I2C.CR2.BITS.START=0
#define I2C_STOP()              I2C.CR2.BITS.STOP=1
#define I2C_NSTOP()             I2C.CR2.BITS.STOP=0
#define I2C_ACK()               I2C.CR2.BITS.ACK=1
#define I2C_NACK()              I2C.CR2.BITS.ACK=0

typedef struct
{
  unsigned char IsMasterMode;
  unsigned char Speed;
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char USING_ADDRESS_ZERO  : 1;
      unsigned char Address             : 7;
    } BITS;
  } SlaveAddress;                               //care only when I2C1 in slave mode  
} I2CInit_TypeDef;
void I2C_Init(const I2CInit_TypeDef* Info);
//for slave mode
__weak void I2C_WeakupRequest();
__weak void I2C_WriteRequest(unsigned char Data);
__weak void I2C_ReadRequest();
__weak void I2C_StartRequest(unsigned char IsReadRequest);
__weak void I2C_StopRequest();
//for master mode
void I2C_WriteBytes(unsigned char SlaveAddress, unsigned char* Data, unsigned short Length);
void I2C_ReadBytes(unsigned char SlaveAddress, unsigned char* Buffer, unsigned short Length);
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned char,     //0x0           0x00            Control register 1
    PE                  , 1,    //0             0               Peripheral enable
    SMBUS               , 1,    //1             0               SMBus mode: 0: I2C mode, 1: SMBus mode
    _reserved           , 1,
    SMBTYPE             , 1,    //3             0               SMBus type: 0: SMBus Device
    ENARP               , 1,    //4             0               ARP enable
    ENPEC               , 1,    //5             0               PEC enable
    ENGC                , 1,    //6             0               General call enable: 0: General call disabled. Address 0x00 is NACKed.
    NO_STRECTH          , 1);   //7             0               Clock stretching disable
  BUNION(CR2, unsigned char,     //0x1           0x00            Control register 2
    START               , 1,    //0             0               Start generation
    STOP                , 1,    //1             0               Stop generation
    ACK                 , 1,    //2             0               Acknowledge enable
    POS                 , 1,    //3             0               Acknowledge position (for data reception)
    PEC                 , 1,    //4             0               Packet error checking
    ALERT               , 1,    //5             0               SMBus alert
    _reserved           , 1,
    SWRST               , 1);   //7             0               Software reset  
  BUNION(FREQR, unsigned char,   //0x2           0x00            Frequency register
    FREQ                , 6,    //0:5           0               Peripheral clock frequency
    _reserved           , 2);
  BUNION(OARL, unsigned char,    //0x3           0x00            Own address register LSB
    ADD0                , 1,    //0             0               Interface address: bit 0 of mode 10 bit addr
    ADD                 , 7);   //1:7           0               Interface address  
  BUNION(OARH, unsigned char,    //0x4           0x00            Own address register MSB
    _reserved0          , 1,
    ADD1                , 2,    //1-2           0               Interface address: bit 8-9 of mode 10 bit addr
    _reserved1          , 3,
    ADDCONF             , 1,    //6             0               Address mode configuration, must always be written as ‘1’
    ADDMODE             , 1);   //7             0               Addressing mode (Slave mode) (7 bit or 10 bit)
  BUNION(OAR2, unsigned char,    //0x5           0x00            Own address register 2
    ENDUAL              , 1,    //0             0               Dual addressing mode enable
    ADD2                , 7);   //1:7           0               bit 7-1 of address in Dual addressing mode
  unsigned char DR;             //0x6           0x00            Data register
  BUNION(SR1, unsigned char const,//0x7          0x00            Status register 1 
    SB                  , 1,    //0             0               Start bit (Master mode)
    ADDR                , 1,    //1             0               Address sent (master mode)/matched (slave mode)
    BTF                 , 1,    //2             0               Byte transfer finished
    ADD10               , 1,    //3             0               10-bit header sent (Master mode)
    STOPF               , 1,    //4             0               Stop detection (Slave mode)
    _reserved           , 1,
    RXNE                , 1,    //6             0               Data register not empty (receivers)
    TXE                 , 1);   //7             0               Data register empty (transmitters)  
  BUNION(SR2, unsigned char,     //0x8           0x00            Status register 2 
    BERR                , 1,    //0             0               Bus error 
    ARLO                , 1,    //1             0               Arbitration lost (master mode) 
    AF                  , 1,    //2             0               Acknowledge failure. 
    OVR                 , 1,    //3             0               Overrun/underrun 
    PECERR              , 1,    //4             0               PEC Error in reception 
    WUFH                , 1,    //5             0               Wakeup from Halt
    TIMEOUT             , 1,    //6             0               Timeout or Tlow error
    SMBALERT            , 1);   //7             0               SMBus alert
  BUNION(SR3, unsigned char const,//0x9          0x00            Status register 3 
    MSL                 , 1,    //0             0               Master/Slave
    BUSY                , 1,    //1             0               Bus busy
    TRA                 , 1,    //2             0               Transmitter/Receiver
    _reserved           , 1,
    GENCALL             , 1,    //4             0               General call header (Slave mode) 
    SMBDEFAULT          , 1,    //
    SMBHOST             , 1,    //
    DUALF               , 1);   //7             0               Dual flag (Slave mode)
  BUNION(ITR, unsigned char,     //0xA           0x00            Interrupt and DMA register
    ITERREN             , 1,    //0             0               Error interrupt enable
    ITEVTEN             , 1,    //1             0               Event interrupt enable
    ITBUFEN             , 1,    //2             0               Buffer interrupt enable
    DMAEN               , 1,    //3             0               DMA requests enable
    LAST                , 1,    //4             0               DMA last transfer
    _reserved           , 3);
  BRUNION_16x8(CCR, , LOW, HIGH, //0xB-0xC       0x000B          Clock control register
      b7_0              , 8,    //              0x0B
      b11_8             , 4,    //              0               Clock control register
      _reserved         , 2,
      DUTY              , 1,    //6             0               Fast mode duty cycle 
      FS                , 1);   //7             0               I2C master mode selection (fast)
  BUNION(TRISER, unsigned char,  //0xD           0x02            TRISE register
    TRISE               , 6,    //0:5           2               Maximum rise time in Fast/Standard mode (Master mode)
    _reserved           , 2);
  unsigned char PEC;            //0xE           0x00            Packet error checking register
} I2C_TypeDef;
extern __no_init volatile I2C_TypeDef I2C;

#endif