#ifndef _TIMER_BASIC_8BIT_H_
#define _TIMER_BASIC_8BIT_H_

#include <stm8s_product.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned char,                    //              0x00            Control register 1
    CEN                                 , 1,    //0             0               Counter enable
    UDIS                                , 1,    //1             0               Update disable
    URS                                 , 1,    //2             0               Update request source
    OPM                                 , 1,    //3             0               One-pulse mode
    _reserved                           , 3,        
    ARPE                                , 1);   //7             0               Auto-reload preload enable
#if (__PRODUCT_LINE__ == 0)
  unsigned char _reserved[2];
#endif
  BUNION(IER, unsigned char,                    //              0x00            Interrupt enable register
    UIE                                 , 1,    //0             0               Update interrupt enable
    _reserved0                          , 5,
    TIE                                 , 1,    //6             0               Trigger interrupt enable
    _reserved1                          , 1);
  BUNION(SR, unsigned char,                     //              0x00            Status register
    UIF                                 , 1,    //0             0               Update interrupt flag
    _reserved0                          , 5,
    TIF                                 , 1,    //6             0               Trigger interrupt flag
    _reserved1                          , 1);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    _reserved0                          , 5,
    TG                                  , 1,    //6             0               Trigger generation
    _reserved1                          , 1);
  unsigned char CNTR;                           //              0x00            Counter
  unsigned char PSCR;                           //              0x00            Prescaler register (3 bit low)
  unsigned char ARR;                            //              0xFF            Auto-reload register
} TIM4_TypeDef;
typedef struct
{
  BUNION(CR1, unsigned char,                    //              0x00            Control register 1
    CEN                                 , 1,    //0             0               Counter enable
    UDIS                                , 1,    //1             0               Update disable
    URS                                 , 1,    //2             0               Update request source
    OPM                                 , 1,    //3             0               One-pulse mode
    _reserved                           , 3,        
    ARPE                                , 1);   //7             0               Auto-reload preload enable
  BUNION(CR2, unsigned char,                    //              0x00            Control register 2
    _reserved0                          , 4,
    MMS                                 , 3,    //4:6           0               Master mode selection
    _reserved1                          , 1);
  BUNION(SMCR, unsigned char,                   //              0x00            Slave mode control register
    SMS                                 , 3,    //0:2           0               Clock/trigger/slave mode selection
    _reserved                           , 1,
    TS                                  , 3,    //4:6           0               Trigger selection
    MSM                                 , 1);   //7             0               Master/slave mode
  BUNION(IER, unsigned char,                    //              0x00            Interrupt enable register
    UIE                                 , 1,    //0             0               Update interrupt enable
    _reserved0                          , 5,
    TIE                                 , 1,    //6             0               Trigger interrupt enable
    _reserved1                          , 1);
  BUNION(SR, unsigned char,                     //              0x00            Status register
    UIF                                 , 1,    //0             0               Update interrupt flag
    _reserved0                          , 5,
    TIF                                 , 1,    //6             0               Trigger interrupt flag
    _reserved1                          , 1);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    _reserved0                          , 5,
    TG                                  , 1,    //6             0               Trigger generation
    _reserved1                          , 1);
  unsigned char CNTR;                           //              0x00            Counter
  unsigned char PSCR;                           //              0x00            Prescaler register (3 bit low)
  unsigned char ARR;                            //              0xFF            Auto-reload register
} TIM6_TypeDef;
//==============================================================================================================================================================
/*
+) NOTE:
  -asm("RIM") to enable global interrupt
  -IRQ function must clear flag
*/
#define BASIC_TIMER_EnableInterrupt(TIMER)    (TIMER)->IER.BITS.UIE=1
#define BASIC_TIMER_DisableInterrupt(TIMER)   (TIMER)->IER.BITS.UIE=0
//==============================================================================================================================================================
/*
+) NOTE:
  -CLK.PCKENR must enable
+) Timer overflow:
    (2^Prescale / F_TIMER) * (ReloadValue + 1) (ms)    //F_TIMER: KHz
*/
#if (__PRODUCT_LINE__ == 0)
  void BASIC_TIMER_Init(volatile void* TIMER, unsigned char Prescale, unsigned char ReloadValue);       //Prescale: 0 -> 7
  #define TIM4_Init(Prescale, ReloadValue)      BASIC_TIMER_Init(&TIM4, Prescale, ReloadValue)
  #define TIM6_Init(Prescale, ReloadValue)      BASIC_TIMER_Init(&TIM6, Prescale, ReloadValue)
#else
  void TIM4_Init(unsigned char Prescale, unsigned char ReloadValue);    //Prescale: 0 -> 7
  void TIM6_Init(unsigned char Prescale, unsigned char ReloadValue);    //Prescale: 0 -> 7
#endif


#endif