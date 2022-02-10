#ifndef _GENERAL_TIMER_H_
#define _GENERAL_TIMER_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef union
{  
  unsigned char REG;
  BSTRUCT(OUTPUT, unsigned char,
    CCS                 , 2,    //0-1           0               Capture/compare selection
    OCFE                , 1,    //2             0               Output compare fast enable
    OCPE                , 1,    //3             0               Output compare preload enable
    OCM                 , 3,    //4:6           0               Output compare mode
    _reserved           , 1);
  BSTRUCT(INPUT, unsigned char,
    CCS                 , 2,    //0-1           0               Capture/compare selection
    ICPSC               , 2,    //2-3           0               Input capture prescaler
    ICF                 , 4);   //4:7           0               Input capture filter
} CCMR_GP_TypeDef;              //              0x00            Capture/compare mode register
typedef struct
{
  BUNION(CR1, unsigned char,     //0x0           0x00            Control register 1
    CEN                 , 1,    //0             0               Counter enable
    UDIS                , 1,    //1             0               Update disable
    URS                 , 1,    //2             0               Update request source
    OPM                 , 1,    //3             0               One-pulse mode      
    DIR                 , 1,    //4             0               Direction: 0: up-counter
    CMS                 , 2,    //5-6           0               Center-aligned mode selection
    ARPE                , 1);   //7             0               Auto-reload preload enable
  BUNION(CR2, unsigned char,     //0x1           0x00            Control register 2
    _reserved           , 3,
    CCDS                , 1,    //3             0               Capture/compare DMA selection
    MMS                 , 3,    //4:6           0               Master mode selection
    TI1S                , 1);   //7             0               TI1 (digital filter input) selection
  BUNION(SMCR, unsigned char,    //0x2           0x00            Slave mode control register
    SMS                 , 3,    //0:2           0               Clock/trigger/slave mode selection
    _reserved           , 1,
    TS                  , 3,    //4:6           0               Trigger selection
    MSM                 , 1);   //7             0               Master/slave mode
  BUNION(ETR, unsigned char,     //0x3           0x00            External trigger register
    EFT                 , 4,    //0:3           0               External trigger filter
    ETPS                , 2,    //4-5           0               External trigger prescaler
    ECE                 , 1,    //6             0               External clock enable
    ETP                 , 1);   //7             0               External trigger polarity
  BUNION(DER, unsigned char,     //0x4           0x00            DMA request enable register
    UDE                 , 1,    //0             0               Update DMA request enable
    CC1DE               , 1,    //1             0               Capture/compare 1 DMA request enable
    CC2DE               , 1,    //2             0               Capture/compare 2 DMA request enable
    _reserved           , 5);
  BUNION(IER, unsigned char,     //0x5           0x00            Interrupt enable register
    UIE                 , 1,    //0             0               Update interrupt enable
    CC1IE               , 1,    //1             0               Capture/compare 1 interrupt enable
    CC2IE               , 1,    //2             0               Capture/compare 2 interrupt enable
    _reserved           , 3,
    TIE                 , 1,    //6             0               Trigger interrupt enable
    BIE                 , 1);   //7             0               Break interrupt enable
  BUNION(SR1, unsigned char,     //0x6           0x00            Status register 1
    UIF                 , 1,    //0             0               Update interrupt flag
    CC1IF               , 1,    //1             0               Capture/compare 1 interrupt flag
    CC2IF               , 1,    //2             0               Capture/compare 2 interrupt flag
    _reserved           , 3,
    TIF                 , 1,    //6             0               Trigger interrupt flag
    BIF                 , 1);   //7             0               Break interrupt flag
  BUNION(SR2, unsigned char,     //0x7           0x00            Status register 2
    _reserved           , 1,
    CC1OF               , 1,    //1             0               Capture/compare 1 overcapture flag
    CC2OF               , 1,    //2             0               Capture/compare 2 overcapture flag
    _reserved1          , 5);
  BUNION(EGR, unsigned char,     //0x8           0x00            Status register 2
    UG                  , 1,    //0             0               Update generation
    CC1G                , 1,    //1             0               Capture/compare 1 generation
    CC2G                , 1,    //2             0               Capture/compare 2 generation
    _reserved           , 3,
    TG                  , 1,    //6             0               Trigger generation
    BG                  , 1);   //7             0               Break generation
  CCMR_GP_TypeDef CCMR1;        //0x9
  CCMR_GP_TypeDef CCMR2;        //0xA
  BUNION(CCER, unsigned char,    //0xB           0x00            Capture/compare enable register
    CC1E                , 1,    //0             0               Capture/compare 1 output enable
    CC1P                , 1,    //1             0               Capture/compare 1 output polarity
    _reserved           , 2,
    CC2E                , 1,    //4             0               Capture/compare 2 output enable
    CC2P                , 1,    //5             0               Capture/compare 2 output polarity
    _reserved1          , 2);
  RUNION_16x8(CNTR, ,       //0xC-0xD       0x0000          Counter  
                  HIGH, LOW);
  BUNION(PSCR, unsigned char,    //0xE           0x00            Prescaler
    PSC                 , 3,
    _reserved           , 5);
  RUNION_16x8(ARR, ,        //0xF-0x10      0xFFFF          Auto-reload register  
                  HIGH, LOW);
  RUNION_16x8(CCR1, ,       //0x11-0x12     0x0000          Capture/compare register 1
                  HIGH, LOW);
  RUNION_16x8(CCR2, ,       //0x13-0x14     0x0000          Capture/compare register 2
                  HIGH, LOW);
  BUNION(BKR, unsigned char,     //0x15          0x00            Break register
    LOCK                , 2,    //0-1           0               Lock configuration
    OSSI                , 1,    //2             0               Off state selection for idle mode
    _reserved           , 1,
    BKE                 , 1,    //4             0               Break enable
    BKP                 , 1,    //5             0               Break polarity
    AOE                 , 1,    //6             0               Automatic output enable
    MOE                 , 1);   //7             0               Main output enable
  BUNION(OISR, unsigned char,    //0x16          0x00            Output idle state register
    OIS1                , 1,    //0             0               Output idle state 1 (OC1 output)
    _reserved           , 1,
    OIS2                , 1,    //2             0               Output idle state 2 (OC2 output)
    _reserved1          , 5);
} GENERAL_TIMER_TypeDef;

//======================================================================================================================
#include <config.h>
/*
+) NOTE:
  -IRQ function must clear flag
*/
#define GENERAL_TIMER_EnableInterrupt(TIMER)    BASE_TIMER_EnableInterrupt(TIMER)
#define GENERAL_TIMER_DisableInterrupt(TIMER)   BASE_TIMER_DisableInterrupt(TIMER)
//======================================================================================================================
#define GENERAL_TIMER_EnableDMA(TIMER)          BASE_TIMER_EnableDMA(TIMER)
#define GENERAL_TIMER_DisableDMA(TIMER)         BASE_TIMER_DisableDMA(TIMER)
//======================================================================================================================
/*
+) Timer overflow:
      ReloadValue / (F_TIMER / 2^Prescale) (ms)    //F_TIMER: KHz
*/
#ifdef GENERAL_TIMER_DIRECT
  void GENERAL_TIMER_Init(unsigned char Prescale, unsigned short ReloadValue);
#else
  void GENERAL_TIMER_Init(volatile GENERAL_TIMER_TypeDef* TIMER, unsigned char Prescale, unsigned short ReloadValue);
#endif
//======================================================================================================================
/*
+) NOTE:
  -GPIO as OUTPUT_PUSHPULL
  -SYSCFG to remap channel pin
  -if (Channel & BIT6) -> Channel
  -if (Channel & BIT7) -> ChannelN
*/
#ifdef GENERAL_TIMER_DIRECT
  void GENERAL_TIMER_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
#else
  void GENERAL_TIMER_GeneratePWM(volatile GENERAL_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
#endif

#endif