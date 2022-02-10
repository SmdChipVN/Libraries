#ifndef _BASIC_TIMER_H_
#define _BASIC_TIMER_H_

#include <base_timer.h>
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(CR1, unsigned char,     //0x0           0x00            Control register 1
    CEN                 , 1,    //0             0               Counter enable
    UDIS                , 1,    //1             0               Update disable
    URS                 , 1,    //2             0               Update request source
    OPM                 , 1,    //3             0               One-pulse mode
    _Reserved           , 3,
    ARPE                , 1);   //7             0               Auto-reload preload enable
  BUNION(CR2, unsigned char,     //0x1           0x00            Control register 2
    _Reserved0          , 4,
    MMS                 , 3,    //4:6           0               Master mode selection
    _Reserved1          , 1);
  BUNION(SMCR, unsigned char,    //0x2           0x00            Slave mode control register
    SMS                 , 3,    //0:2           0               Clock/trigger/slave mode selection
    _Reserved           , 1,
    TS                  , 3,    //4:6           0               Trigger selection
    MSM                 , 1);   //7             0               Master/slave mode
  BUNION(DER, unsigned char,     //0x3           0x00            DMA request enable register
    UDE                 , 1,    //0             0               Update DMA request enable
    _Reserved           , 7);
  BUNION(IER, unsigned char,     //0x4           0x00            Interrupt enable register
    UIE                 , 1,    //0             0               Update interrupt enable
    _Reserved0          , 5,
    TIE                 , 1,    //6             0               Trigger interrupt enable
    _Reserved1          , 1);
  BUNION(SR1, unsigned char,     //0x5           0x00            Status register 1
    UIF                 , 1,    //0             0               Update interrupt flag
    _Reserved0          , 5,
    TIF                 , 1,    //6             0               Trigger interrupt flag
    _Reserved1          , 1);
  BUNION(EGR, unsigned char,     //0x6           0x00            Event generation register
    UG                  , 1,    //0             0               Update generation
    _Reserved0          , 5,
    TG                  , 1,    //6             0               Trigger generation
    _Reserved1          , 1);
  unsigned char CNTR;           //0x7           0x00            Counter
  BUNION(PSCR, unsigned char,    //0x8           0x00            Prescaler register
    PSCR                , 4,    //0:3           0               Prescaler value
    _Reserved           , 4);
  unsigned char ARR;            //0x9           0xFF            Auto-reload register
} BASIC_TIMER_TypeDef;
extern __no_init volatile BASIC_TIMER_TypeDef TIM4;

//======================================================================================================================
#include <config.h>
/*
+) NOTE:
  -IRQ function must clear flag
*/
#define BASIC_TIMER_EnableInterrupt(TIMER)      BASE_TIMER_EnableInterrupt(TIMER)
#define BASIC_TIMER_DisableInterrupt(TIMER)     BASE_TIMER_DisableInterrupt(TIMER)
//======================================================================================================================
#define BASIC_TIMER_EnableDMA(TIMER)            BASE_TIMER_EnableDMA(TIMER)
#define BASIC_TIMER_DisableDMA(TIMER)           BASE_TIMER_DisableDMA(TIMER)
//======================================================================================================================
/*
+) Timer overflow:
      ReloadValue / (F_TIMER / 2^Prescale) (ms)    //F_TIMER: KHz, Prescale 4 bit
*/
#ifdef BASIC_TIMER_DIRECT
  void BASIC_TIMER_Init(unsigned char Prescale, unsigned char ReloadValue);
#else
  void BASIC_TIMER_Init(volatile BASIC_TIMER_TypeDef* TIMER, unsigned char Prescale, unsigned char ReloadValue);
#endif

#endif