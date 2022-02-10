#ifndef _DMA_H_
#define _DMA_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(CR, unsigned char,      //0x0           0x00            DMA channel configuration register
    EN                  , 1,    //0             0               Channel enable
    TCIE                , 1,    //1             0               Transaction complete interrupt enable
    HTIE                , 1,    //2             0               Half-transaction interrupt enable
    DIR                 , 1,    //3             0               Data transfer direction
    CIRC                , 1,    //4             0               Circular buffer mode (Auto-reload mode)
    MINCDEC             , 1,    //5             0               Memory increment/decrement mode
    C3MEM               , 1,    //6             0               Memory transfer enabled (only channel 3)
    _reserved           , 1);
  BUNION(SPR, unsigned char,     //0x1           0x00            DMA channel status & priority register
    _reserved           , 1,
    TCIF                , 1,    //1             0               Transaction complete interrupt flag
    HTIF                , 1,    //2             0               Half transaction interrupt flag
    TSIZE               , 1,    //3             0               Transfer size: 0: 8-bit, 1: 16-bits
    PL                  , 2,    //4-5           0               Channel priority level
    const PEND          , 1,    //6             0               Channel pending
    const BUSY          , 1);   //7             0               Channel busy
  unsigned char NDTR;           //0x2           0x00            DMA number of data to transfer register  
  union
  {
    unsigned short REG;
    RSTRUCT(REGS, unsigned char, HIGH, LOW);
  } PAR;                        //0x2-0x3       0x0000          DMA peripheral address | DMA channel3's memory 1 address
  BUNION(C3M0EAR, unsigned char, //0x4           0x00            DMA channel 3 memory 0 extended address register (only for channel 3)
    M0A16               , 1,    //0             0               Memory 0 address pointer 16
    _reserved           , 7);
  union
  {
    unsigned short REG;
    RSTRUCT(REGS, unsigned char, HIGH, LOW);
  } M0AR;                       //0x5-0x6       0x0000          DMA memory 0 address
} DMA_Channel_TypeDef;
typedef struct
{
  BUNION(GCSR, unsigned char,    //0x0           0x00            DMA global configuration & status register
    GEN                 , 1,    //0             0               Global enable
    GB                  , 1,    //1             0               Global busy
    TO                  , 6);   //2:7           0               Timeout
  BUNION(GIR1, unsigned char,    //0x1           0x00            DMA global interrupt register 1
    const IFC0          , 1,    //0             0               Interrupt flag channel 0
    const IFC1          , 1,    //1             0               Interrupt flag channel 1
    const IFC2          , 1,    //2             0               Interrupt flag channel 2
    const IFC3          , 1,    //3             0               Interrupt flag channel 3
    _reserved           , 4);
  unsigned char _reserved[3];
  DMA_Channel_TypeDef Channel_0;
  unsigned char _reserved1[2];
  DMA_Channel_TypeDef Channel_1;
  unsigned char _reserved2[2];
  DMA_Channel_TypeDef Channel_2;
  unsigned char _reserved3[2];
  DMA_Channel_TypeDef Channel_3;
} DMA_TypeDef;
extern __no_init volatile DMA_TypeDef DMA1;

#define DMA_ADC1_EOC0   DMA1.Channel_0
#define DMA_AES_IN      DMA1.Channel_0
#define DMA_I2C_RX      DMA1.Channel_0
#define DMA_TIM2_CC1    DMA1.Channel_0
#define DMA_TIM3_U      DMA1.Channel_0
#define DMA_TIM1_CC3    DMA1.Channel_0
#define DMA_UART2_TX    DMA1.Channel_0
#define DMA_SPI2_RX     DMA1.Channel_0
#define DMA_TIM5_U      DMA1.Channel_0
#define DMA_TIM4_U0     DMA1.Channel_0

#define DMA_ADC1_EOC1   DMA1.Channel_1
#define DMA_SPI1_RX     DMA1.Channel_1
#define DMA_UART1_TX    DMA1.Channel_1
#define DMA_DAC_CH2TRIG DMA1.Channel_1
#define DMA_TIM2_U      DMA1.Channel_1
#define DMA_TIM3_CC1    DMA1.Channel_1
#define DMA_TIM1_CC4    DMA1.Channel_1
#define DMA_UART3_TX    DMA1.Channel_1
#define DMA_TIM4_U1     DMA1.Channel_1

#define DMA_SPI1_TX     DMA1.Channel_2
#define DMA_UART1_RX    DMA1.Channel_2
#define DMA_TIM3_CC2    DMA1.Channel_2
#define DMA_TIM1_U      DMA1.Channel_2
#define DMA_TIM1_CC1    DMA1.Channel_2
#define DMA_TIM1_COM    DMA1.Channel_2
#define DMA_UART3_RX    DMA1.Channel_2
#define DMA_TIM5_CC1    DMA1.Channel_2
#define DMA_TIM4_U2     DMA1.Channel_2

#define DMA_ADC1_EOC3   DMA1.Channel_3
#define DMA_AES_OUT     DMA1.Channel_3
#define DMA_I2C_TX      DMA1.Channel_3
#define DMA_DAC_CH1TRIG DMA1.Channel_3
#define DMA_TIM2_CC2    DMA1.Channel_3
#define DMA_TIM1_CC2    DMA1.Channel_3
#define DMA_UART2_RX    DMA1.Channel_3
#define DMA_SPI2_TX     DMA1.Channel_3
#define DMA_TIM5_CC2    DMA1.Channel_3
#define DMA_TIM4_U3     DMA1.Channel_3
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <config.h>
typedef struct
{
  BRUNION_16x8(Mode, , r1, r2,
      _reserved         , 3,
      IsReadFromMem     , 1,    //3             1
      IsCircleMode      , 1,    //4             0
      Mem_IsIncrement   , 1,    //5             1
      MemTransfer       , 1,    //6             1               Only for channel 3
      _reserved1        , 1,
      
      _reserved2        , 3,
      Size              , 1,    //3             0               2^Size (byte)
      Priority          , 2,    //4-5           0
      _reserved3        , 2);
  BUNION(Interrupt, unsigned char,
        _reserved       , 1,
        Trans_Complete  , 1,    //1             0
        Trans_Half      , 1,    //2             0
        _reserved1      , 5);
} DMAInit_TypeDef;
/*Example:
CLK.PCKENR2.BITS.DMA1 = 1;
DMAInit_TypeDef DMAInit = {
  .Mode = {.BITS = {.IsReadFromMem = 1, .IsCircleMode = 0, .Mem_IsIncrement = 1, .MemTransfer = 1, .Size = 0, .Priority = 0, },},
  .Interrupt = {.BITS = {.Trans_Complete = 0, .Trans_Half = 0, }, }
};
DMA_Init(&DMAInit);

+NOTE:
  -DMA_Transfer with channel 0-1-2: MemPointer range: 0->0x03FF (meaning only ram range)
*/
#ifdef DMA_DIRECT
  void DMA_Init(const DMAInit_TypeDef* DMAInit);
  unsigned char DMA_Transfer(const volatile void* MemPointer, const volatile void* PeriPointer, unsigned char Length);  //return 0 if dma_channel is busy
#else
  void DMA_Init(volatile DMA_Channel_TypeDef* DMA_Channel, const DMAInit_TypeDef* DMAInit);
  unsigned char DMA_Transfer(volatile DMA_Channel_TypeDef* DMAChannel, const volatile void* MemPointer, const volatile void* PeriPointer, unsigned char Length);
#endif

#endif