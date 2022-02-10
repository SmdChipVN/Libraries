#ifndef _RI_H_
#define _RI_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef BRUNION_24x8(IOCH_TypeDef, ,
  r1, r2, r3,
    CH1                 , 1,    //0
    CH4                 , 1,    //1
    CH7                 , 1,    //2
    CH10                , 1,    //3
    CH13                , 1,    //4
    CH16                , 1,    //5
    CH19                , 1,    //6
    CH22                , 1,    //7

    CH2                 , 1,    //0
    CH5                 , 1,    //1
    CH8                 , 1,    //2
    CH11                , 1,    //3
    CH14                , 1,    //4
    CH17                , 1,    //5
    CH20                , 1,    //6
    CH23                , 1,    //7

    CH3                 , 1,    //0
    CH6                 , 1,    //1
    CH9                 , 1,    //2
    CH12                , 1,    //3
    CH15                , 1,    //4
    CH18                , 1,    //5
    CH21                , 1,    //6
    CH24                , 1);   //7
typedef BUNION(IOCHx_TypeDef, unsigned char,
  CH29                  , 1,    //0
  CH26                  , 1,    //1
  _reserved             , 4,
  CH27                  , 1,    //6
  CH28                  , 1);   //7
typedef struct
{
  unsigned char _reserved;
  BUNION(ICR1, unsigned char,    //0x1           0x00            Timer input capture routing register 1
    IC2CS               , 5,    //0:4           0               TIM1 Input Capture 2 I/O selection
    _reserved           , 3);
  BUNION(ICR2, unsigned char,    //0x2           0x00            Timer input capture routing register 2
    IC3CS               , 5,    //0:4           0               TIM1 Input Capture 3 I/O selection
    _reserved           , 3);
  IOCH_TypeDef const IOIR;      //0x3:0x5       0x--(3)         I/O input register
  IOCH_TypeDef IOCMR;           //0x6:0x8       0x00(3)         I/O control mode register
  IOCH_TypeDef IOSR;            //0x9:0xB       0x00(3)         I/O switch register
  xBUNION(IOGCR, unsigned char,
    IOM, 1, 4, 2);              //0xC           0xFF            IO group control register
  xBUNION(ASCR1, unsigned char,
    b, 0, 7, 1);                //0xD           0x00            Analog switch register 1
  xBUNION(ASCR2, unsigned char,
    b, 8, 10, 1);               //0xE           0x00            Analog switch register 2
  BUNION(RCR, unsigned char,     //0xF           0x00            Resistor control register
    PU_10K              , 1,    //0             0               10k Omh pull-up resistor
    PU_400K             , 1,    //1             0               400k Omh pull-up resistor
    PD_10K              , 1,    //2             0               10k Omh pull-down resistor
    PD_400K             , 1,    //3             0               400k Omh pull-down resistor
    _reserved           , 4);
  unsigned char _reserved1[16];
  BUNION(CR, unsigned char,      //0x20          0x00            Control register  
    TIE                 , 1,    //0             0               Trigger interrupt enable
    TIF                 , 1,    //1             0               Trigger interrupt flag
    AM                  , 1,    //2             0               Acquisition mode
    THALT               , 1,    //3             0               Timer halted mode
    _reserved           , 4);
  IOCH_TypeDef IOMR;            //0x21:0x23     0x00(3)         I/O mask register
  IOCHx_TypeDef IOMRx;          //0x24          0x00
  IOCHx_TypeDef const IOIRx;    //0x25          0x--
  IOCHx_TypeDef IOCMRx;         //0x26          0x00
  IOCHx_TypeDef IOSRx;          //0x27          0x00
} RI_TypeDef;
extern __no_init volatile RI_TypeDef RI;

#endif