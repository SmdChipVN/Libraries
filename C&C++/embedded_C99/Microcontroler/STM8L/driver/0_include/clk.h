#ifndef _CLOCK_H_
#define _CLOCK_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CKDIVR, unsigned char,  //0             0x03            System clock divider register
    CKM                 , 3,    //0:2           3               System clock prescaler: F_SYS = F_CLK / 2^CKM
    _reserved           , 5);
  BUNION(RTCR, unsigned char,    //1             0x00            Clock RTC register
    const RTCSWBSY      , 1,    //0             0               The system is busy during a RTC clock change
    RTCSEL              , 4,    //1:4           0               Configurable RTC clock source selection
    RTCDIV              , 3);   //5:7           0               Clock RTC prescaler 
  BUNION(ICKCR, unsigned char,   //2             0x11            Internal clock register
    HSION               , 1,    //0             1               High-speed internal RC oscillator ON
    const HSIRDY        , 1,    //1             0               High-speed internal oscillator ready
    LSION               , 1,    //2             0               Low speed internal RC oscillator enable
    const LSIRDY        , 1,    //3             0               Low speed internal oscillator ready
    SAHALT              , 1,    //4             1               Slow HALT/Active-halt mode
    FHWU                , 1,    //5             0               Fast wakeup from Halt/Active-halt modes
    BEEPAHALT           , 1,    //6             0               BEEP clock Halt/Active-halt mode
    _reserved           , 1);
  BUNION(PCKENR1, unsigned char, //3             0x00            Peripheral clock enable 1
    TIM2                , 1,    //0             0
    TIM3                , 1,    //1             0
    TIM4                , 1,    //2             0
    I2C1                , 1,    //3             0
    SPI1                , 1,    //4             0
    UART1               , 1,    //5             0
    BEEP                , 1,    //6             0
    DAC                 , 1);   //7             0
  BUNION(PCKENR2, unsigned char, //4             0x80            Peripheral clock enable 2
    ADC1                , 1,    //0             0
    TIM1                , 1,    //1             0
    RTC                 , 1,    //2             0
    LCD                 , 1,    //3             0
    DMA1                , 1,    //4             0
    COMP1_COMP2         , 1,    //5             0
    _reserved           , 1,
    BootROM             , 1);   //7             1  
  BUNION(CCOR, unsigned char,    //5             0x00            Configurable clock output register
    const CCOSWBSY      , 1,    //0             0               Configurable clock output switch busy
    CCOSEL              , 4,    //1:4           0               Configurable clock output selection
    CCODIV              , 3);   //5:7           0               Configurable clock output prescaler  
  BUNION(ECKCR, unsigned char,   //6             0x00            External clock register
    HSEON               , 1,    //0             0               High-speed external crystal oscillator enable
    const HSERDY        , 1,    //1             0               High-speed external crystal oscillator ready
    LSEON               , 1,    //2             0               Low speed external crystal oscillator enable
    const LSERDY        , 1,    //3             0               Low speed external crystal oscillator ready
    HSEBYP              , 1,    //4             0               High-speed external clock bypass
    LSEBYP              , 1,    //5             0               Low speed external clock bypass
    _reserved           , 2);
  unsigned char const SCSR;     //7             0x01            System clock status register
  unsigned char SWR;            //8             0x01            System clock switch register  
  BUNION(SWCR, unsigned char,    //9             0x00            Switch control register
    SWBSY               , 1,    //0             0               Switch busy
    SWEN                , 1,    //1             0               Switch start/stop
    SWIEN               , 1,    //2             0               Clock switch interrupt enable
    SWIF                , 1,    //3             0               Clock switch interrupt flag
    _reserved           , 4);
  BUNION(CSSR, unsigned char,    //10            0x00            Clock security system register
    CSSEN               , 1,    //0             0               Clock security system enable
    const AUX           , 1,    //1             0               Auxiliary oscillator connected to system clock
    CSSDIE              , 1,    //2             0               Clock security system detection interrupt enable
    CSSD                , 1,    //3             0               Clock security system detection
    CSSDGON             , 1,    //5             0               CSS deglitcher system
    _reserved           , 3);
  BUNION(CBEEPR, unsigned char,  //11            0x00            Clock BEEP register
    const BEEPSWBSY     , 1,    //0             0               System busy during BEEP clock change
    CLKBEEPSEL          , 2,    //1-2           0               Configurable BEEP clock source selection
    _reserved           , 5);
  unsigned char const HSICALR;  //12            0x--            HSI calibration register
  unsigned char HSITRIMR;       //13            0x00            HSI clock calibration trimming register
  unsigned char HSIUNLCKR;      //14            0x00            HSI unlock register
  BUNION(REGCSR, unsigned char,  //15            0xB9            Main regulator control status register
    const REGREADY      , 1,    //0             1               Main regulator ready
    REGOFF              , 1,    //1             0               Main regulator OFF
    const HSIPD         , 1,    //2             0               HSI power-down
    const LSIPD         , 1,    //3             1               LSI power-down
    const HSEPD         , 1,    //4             0               HSE power-down
    const LSEPD         , 1,    //5             1               LSE power-down
    const EEBUSY        , 1,    //6             0               Flash program memory and Data EEPROM busy
    const EEREADY       , 1);   //7             1               Flash program memory and Data EEPROM ready
  BUNION(PCKENR3, unsigned char, //16            0x00            Peripheral clock enable
    AES                 , 1,    //0             0
    TIM5                , 1,    //1             0
    SPI2                , 1,    //2             0
    UART2               , 1,    //3             0
    UART3               , 1,    //4             0
    CSS_LSE             , 1,    //5             0
    _reserved           , 2);
} CLK_TypeDef;
extern __no_init volatile CLK_TypeDef CLK;

#endif