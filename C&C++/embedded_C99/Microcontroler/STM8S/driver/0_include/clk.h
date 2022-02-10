#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(ICKR, unsigned char,                   //              0x01            Internal clock register
    HSIEN                               , 1,    //0             1               High speed internal RC oscillator enable
    const HSIRDY                        , 1,    //1             0               High speed internal oscillator ready
    FHWU                                , 1,    //2             0               Fast wakeup from Halt/Active-halt modes
    LSIEN                               , 1,    //3             0               Low speed internal RC oscillator enable
    const LSIRDY                        , 1,    //4             0               Low speed internal oscillator ready
    REGAH                               , 1,    //5             0               Regulator power off in Active-halt mode
    _reserved                           , 2);
  BUNION(ECKR, unsigned char,                   //              0x00            External clock register
    HSEEN                               , 1,    //0             0               High speed external crystal oscillator enable
    const HSERDY                        , 1,    //1             0               High speed external crystal oscillator ready
    _reserved                           , 6);
  unsigned char _reserved;
  unsigned char const CMSR;                     //              0xE1            Clock master status register
  unsigned char SWR;                            //              0xE1            Clock master switch register
  BUNION(SWCR, unsigned char,                   //              0x--            Switch control register
    SWBSY                               , 1,    //0             -               Switch busy
    SWEN                                , 1,    //1             -               Switch start/stop
    SWIEN                               , 1,    //2             -               Clock switch interrupt enable
    SWIF                                , 1,    //3             -               Clock switch interrupt flag
    _reserved                           , 4);
  BUNION(CKDIVR, unsigned char,                 //              0x18            Clock divider register
    CPUDIV                              , 3,    //              0               CPU clock prescaler
    HSIDIV                              , 2,    //              3               High speed internal clock prescaler
    _reserved                           , 3);
  BUNION(PCKENR1, unsigned char,                //              0xFF            Peripheral clock gating register 1
    I2C                                 , 1,    //0             1
    SPI                                 , 1,    //1             1
    _reserved                           , 1,    //2             1
    UART1                               , 1,    //3             1
    TIM4_TIM6                           , 1,    //4             1
    TIM2_TIM5                           , 1,    //5             1
    TIM3                                , 1,    //6             1
    TIM1                                , 1);   //7             1
  BUNION(CSSR, unsigned char,                   //              0x00            Clock security system register
    CSSEN                               , 1,    //0             0               Clock security system enable
    const AUX                           , 1,    //1             0               Auxiliary oscillator connected to master clock
    CSSDIE                              , 1,    //2             0               Clock security system detection interrupt enable
    CSSD                                , 1,    //3             0               Clock security system detection
    _reserved                           , 4);
  BUNION(CCOR, unsigned char,                   //              0x00            Configurable clock output register
    CCOEN                               , 1,    //0             0               Configurable clock output enable
    CCOSEL                              , 4,    //1:4           0               Configurable clock output selection
    const CCORDY                        , 1,    //5             0               Configurable clock output ready
    const CCOBSY                        , 1,    //6             0               Configurable clock output busy
    _reserved                           , 1);
  BUNION(PCKENR2, unsigned char,                //              0xFF            Peripheral clock gating register 2
    _reserved                           , 2,
    AWU                                 , 1,    //2             1
    ADC                                 , 1,    //3             1
    _reserved1                          , 3,
    CAN                                 , 1);   //7             1
  unsigned char _reserved1;
  BUNION(HSITRIMR, unsigned char,               //              0x00            HSI clock calibration trimming register
    HSITRIM                             , 3,    //              0               HSI trimming value
    _reserved                           , 5);
  BUNION(SWIMCCR, unsigned char,                //              0x00            SWIM clock control register
    SWIMCLK                             , 1,    //1             0               SWIM clock divider
    _reserved                           , 7);
} CLK_TypeDef;

#endif