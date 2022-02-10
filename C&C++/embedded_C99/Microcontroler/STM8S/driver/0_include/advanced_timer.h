#ifndef _ADVANCE_TIMER_H_
#define _ADVANCE_TIMER_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef union
{
  BUNION(OUTPUT, unsigned char,                 //              0x00            
    CCS                                 , 2,    //0-1           0               Capture/compare selection
    OCFE                                , 1,    //2             0               Output compare fast enable
    OCPE                                , 1,    //3             0               Output compare preload enable
    OCM                                 , 3,    //4:6           0               Output compare mode
    OCCE                                , 1);   //7             0               Output compare clear enable
  BUNION(INPUT, unsigned char,                  //              0x00
    CCS                                 , 2,    //0-1           0               Capture/compare selection
    ICPSC                               , 2,    //2-3           0               Input capture prescaler
    ICF                                 , 4);   //4:7           0               Input capture filter
} ADVANCE_TIMER_CCMR_TypeDef;                   //                              Capture/compare mode register
typedef struct
{
  BUNION(CR1, unsigned char,                    //              0x00            Control register 1
    CEN                                 , 1,    //0             0               Counter enable
    UDIS                                , 1,    //1             0               Update disable
    URS                                 , 1,    //2             0               Update request source
    OPM                                 , 1,    //3             0               One-pulse mode
    DIR                                 , 1,    //4             0               Direction
    CMS                                 , 2,    //5-6           0               Center-aligned mode selection
    ARPE                                , 1);   //7             0               Auto-reload preload enable
  BUNION(CR2, unsigned char,                    //              0x00            Control register 2
    CCPC                                , 1,    //0             0               Capture/compare preloaded control
    _reserved                           , 1,
    COMS                                , 1,    //2             0               Capture/compare control update selection
    _reserved1                          , 1,
    MMS                                 , 3,    //4:6           0               Master mode selection
    _reserved2                          , 1);
  BUNION(SMCR, unsigned char,                   //              0x00            Slave mode control register
    SMS                                 , 3,    //0:2           0               Clock/trigger/slave mode selection
    _reserved                           , 1,
    TS                                  , 3,    //4:6           0               Trigger selection
    MSM                                 , 1);   //7             0               Master/slave mode
  BUNION(ETR, unsigned char,                    //              0x00            External trigger register
    EFT                                 , 4,    //0:3           0               External trigger filter
    ETPS                                , 2,    //4-5           0               External trigger prescaler
    ECE                                 , 1,    //6             0               External clock enable
    ETP                                 , 1);   //7             0               External trigger polarity
  BUNION(IER, unsigned char,                    //              0x00            Interrupt enable register
    UIE                                 , 1,    //0             0               Update interrupt enable
    CC1IE                               , 1,    //1             0               Capture/compare x interrupt enable
    CC2IE                               , 1,    //2             0
    CC3IE                               , 1,    //3             0
    CC4IE                               , 1,    //4             0
    COMIE                               , 1,    //5             0               Commutation interrupt enable
    TIE                                 , 1,    //6             0               Trigger interrupt enable
    BIE                                 , 1);   //7             0               Break interrupt enable
  BUNION(SR1, unsigned char,                    //              0x00            Status register 1
    UIF                                 , 1,    //0             0               Update interrupt flag
    CC1IF                               , 1,    //1             0               Capture/compare x interrupt flag
    CC2IF                               , 1,    //2             0
    CC3IF                               , 1,    //3             0
    CC4IF                               , 1,    //4             0
    COMIF                               , 1,    //5             0               Commutation interrupt flag
    TIF                                 , 1,    //6             0               Trigger interrupt flag
    BIF                                 , 1);   //7             0               Break interrupt flag
  BUNION(SR2, unsigned char,                    //              0x00            Status register 2
    _reserved                           , 1,
    CC1OF                               , 1,    //1             0               Capture/compare x overcapture flag
    CC2OF                               , 1,    //2             0
    CC3OF                               , 1,    //3             0
    CC4IF                               , 1,    //4             0
    _reserved1                          , 3);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    CC1G                                , 1,    //1             0               Capture/compare x generation
    CC2G                                , 1,    //2             0               
    CC3G                                , 1,    //3             0               
    CC4G                                , 1,    //4             0               
    COMG                                , 1,    //5             0               Commutation generation
    TIG                                 , 1,    //6             0               Trigger generation
    BIG                                 , 1);   //7             0               Break generation
  ADVANCE_TIMER_CCMR_TypeDef CCMR1, CCMR2, CCMR3, CCMR4;
  BUNION(CCER1, unsigned char,                  //              0x00            Capture/compare enable register
    CC1E                                , 1,    //0             0               Capture/compare x output enable
    CC1P                                , 1,    //1             0               Capture/compare x output polarity
    CC1NE                               , 1,    //2             0               Capture/compare x complementary output enable
    CC1NP                               , 1,    //3             0               Capture/compare x complementary output polarity
    CC2E                                , 1,    //4             0
    CC2P                                , 1,    //5             0
    CC2NE                               , 1,    //6             0
    CC2NP                               , 1);   //7             0               Capture/compare 2 complementary output polarity
  BUNION(CCER2, unsigned char,                  //              0x00
    CC3E                                , 1,    //0             0
    CC3P                                , 1,    //1             0
    CC3NE                               , 1,    //2             0
    CC3NP                               , 1,    //3             0
    CC4E                                , 1,    //4             0
    CC4P                                , 1,    //5             0
    _reserved       , 2);
  RUNION_16x8(CNTR,, HIGH, LOW);                //              0x0000          Counter
  RUNION_16x8(PSCR,, HIGH, LOW);                //              0x0000          Prescaler register
  RUNION_16x8(ARR,, HIGH, LOW);                 //              0xFFFF          Auto-reload register
  unsigned char RCR;                            //              0x00              
  RUNION_16x8(,, HIGH, LOW)                     //              0x0000          Capture/compare register
    CCR1, CCR2, CCR3, CCR4;
  BUNION(BKR, unsigned char,                    //              0x00            Status register 1
    LOCK                                , 2,    //0-1           0               Lock configuration
    OSSI                                , 1,    //2             0               Off state selection for idle mode
    OSSR                                , 1,    //3             0               Off state selection for Run mode
    BKE                                 , 1,    //4             0               Break enable
    BKP                                 , 1,    //5             0               Break polarity
    AOE                                 , 1,    //6             0               Automatic output enable
    MOE                                 , 1);   //7             0               Main output enable
  unsigned char DTR;                            //              0x00            Deadtime register
  BUNION(OISR, unsigned char,                   //              0x00            Output idle state register
    OIS1                                , 1,    //0             0               Output idle state (OC output)
    OIS1N                               , 1,    //1             0               Output idle state (OCN output)
    OIS2                                , 1,    //2             0               
    OIS2N                               , 1,    //3             0
    OIS3                                , 1,    //4             0               
    OIS3N                               , 1,    //5             0               
    OIS4                                , 1,    //6             0               
    _reserved                           , 1);
} ADVANCED_TIMER_TypeDef;
//==============================================================================================================================================================
/*
+) NOTE:
  -asm("RIM") to enable global interrupt
  -IRQ function must clear flag
*/
#define ADVANCED_TIMER_EnableInterrupt(TIMER)    (TIMER)->IER.BITS.UIE=1
#define ADVANCED_TIMER_DisableInterrupt(TIMER)   (TIMER)->IER.BITS.UIE=0
//==============================================================================================================================================================
/*
+) NOTE:
  -CLK.PCKENR must enable
+) Timer overflow:
    (2^Prescale / F_TIMER) * (ReloadValue + 1) (ms)    //F_TIMER: KHz
*/
void ADVANCED_TIMER_Init(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned short Prescale, unsigned short ReloadValue);
//==============================================================================================================================================================
/*
+) NOTE:
  -GPIO as OUTPUT
  -Option byte to remap channel pin
*/
void ADVANCED_TIMER_GeneratePWM(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);


#endif