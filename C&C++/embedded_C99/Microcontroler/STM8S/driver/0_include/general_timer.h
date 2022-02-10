#ifndef _GENERAL_TIMER_H_
#define _GENERAL_TIMER_H_

#include <stm8s_product.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef union
{
  BUNION(OUTPUT, unsigned char,                 //              0x00            
    CCS                                 , 2,    //0-1           0               Capture/compare selection
    _reserved                           , 1,
    OCPE                                , 1,    //3             0               Output compare preload enable
    OCM                                 , 3,    //4:6           0               Output compare mode
    _reserved1                          , 1);
  BUNION(INPUT, unsigned char,                  //              0x00
    CCS                                 , 2,    //0-1           0               Capture/compare selection
    ICPSC                               , 2,    //2-3           0               Input capture prescaler
    ICF                                 , 4);   //4:7           0               Input capture filter
} GENERAL_TIMER_CCMR_TypeDef;                   //                              Capture/compare mode register
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
    CC1IE                               , 1,    //1             0               Capture/compare x interrupt enable
    CC2IE                               , 1,    //2             0
    CC3IE                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR1, unsigned char,                    //              0x00            Status register 1
    UIF                                 , 1,    //0             0               Update interrupt flag
    CC1IF                               , 1,    //1             0               Capture/compare x interrupt flag
    CC2IF                               , 1,    //2             0
    CC3IF                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR2, unsigned char,                    //              0x00            Status register 2
    _reserved                           , 1,
    CC1OF                               , 1,    //1             0               Capture/compare x overcapture flag
    CC2OF                               , 1,    //2             0
    CC3OF                               , 1,    //3             0
    _reserved1                          , 4);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    CC1G                                , 1,    //1             0               Capture/compare x generation
    CC2G                                , 1,    //2             0
    CC3G                                , 1,    //3             0
    _reserved                           , 4);
  GENERAL_TIMER_CCMR_TypeDef CCMR1, CCMR2, CCMR3;
  BUNION(CCER1, unsigned char,                  //              0x00            Capture/compare enable register
    CC1E                                , 1,    //0             0               Capture/compare x output enable
    CC1P                                , 1,    //1             0               Capture/compare x output polarity
    _reserved                           , 2,
    CC2E                                , 1,    //4             0
    CC2P                                , 1,    //5             0
    _reserved1                          , 2);
  BUNION(CCER2, unsigned char,                  //              0x00
    CC3E                                , 1,    //0             0
    CC3P                                , 1,    //1             0
    _reserved                           , 6);
  RUNION_16x8(CNTR,, HIGH, LOW);                //              0x0000          Counter: write MS first, read MS first
  unsigned char PSCR;                           //              0x00            Prescaler value (4 bit low)
  RUNION_16x8(ARR,, HIGH, LOW);                 //              0xFFFF          Auto-reload register: write MS first, read MS first
  RUNION_16x8(,, HIGH, LOW)                     //              0x0000          Capture/compare register: write MS first, read MS first
    CCR1, CCR2, CCR3;
} TIM2_TypeDef;
typedef struct
{
  BUNION(CR1, unsigned char,                    //              0x00            Control register 1
    CEN                                 , 1,    //0             0               Counter enable
    UDIS                                , 1,    //1             0               Update disable
    URS                                 , 1,    //2             0               Update request source
    OPM                                 , 1,    //3             0               One-pulse mode
    _reserved                           , 3,        
    ARPE                                , 1);   //7             0               Auto-reload preload enable
  BUNION(IER, unsigned char,                    //              0x00            Interrupt enable register
    UIE                                 , 1,    //0             0               Update interrupt enable
    CC1IE                               , 1,    //1             0               Capture/compare x interrupt enable
    CC2IE                               , 1,    //2             0
    CC3IE                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR1, unsigned char,                    //              0x00            Status register 1
    UIF                                 , 1,    //0             0               Update interrupt flag
    CC1IF                               , 1,    //1             0               Capture/compare x interrupt flag
    CC2IF                               , 1,    //2             0
    CC3IF                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR2, unsigned char,                    //              0x00            Status register 2
    _reserved                           , 1,
    CC1OF                               , 1,    //1             0               Capture/compare x overcapture flag
    CC2OF                               , 1,    //2             0
    CC3OF                               , 1,    //3             0
    _reserved1                          , 4);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    CC1G                                , 1,    //1             0               Capture/compare x generation
    CC2G                                , 1,    //2             0
    CC3G                                , 1,    //3             0
    _reserved                           , 4);
  GENERAL_TIMER_CCMR_TypeDef CCMR1, CCMR2;
  BUNION(CCER1, unsigned char,                  //              0x00            Capture/compare enable register
    CC1E                                , 1,    //0             0               Capture/compare x output enable
    CC1P                                , 1,    //1             0               Capture/compare x output polarity
    _reserved                           , 2,
    CC2E                                , 1,    //4             0
    CC2P                                , 1,    //5             0
    _reserved1                          , 2);
  RUNION_16x8(CNTR,, HIGH, LOW);                //              0x0000          Counter: write MS first, read MS first
  unsigned char PSCR;                           //              0x00            Prescaler value (4 bit low)
  RUNION_16x8(ARR,, HIGH, LOW);                 //              0xFFFF          Auto-reload register: write MS first, read MS first
  RUNION_16x8(,, HIGH, LOW)                     //              0x0000          Capture/compare register: write MS first, read MS first
    CCR1, CCR2;
} TIM3_TypeDef;
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
  BUNION(IER, unsigned char,                    //              0x00            Interrupt enable register
    UIE                                 , 1,    //0             0               Update interrupt enable
    CC1IE                               , 1,    //1             0               Capture/compare x interrupt enable
    CC2IE                               , 1,    //2             0
    CC3IE                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR1, unsigned char,                    //              0x00            Status register 1
    UIF                                 , 1,    //0             0               Update interrupt flag
    CC1IF                               , 1,    //1             0               Capture/compare x interrupt flag
    CC2IF                               , 1,    //2             0
    CC3IF                               , 1,    //3             0
    _reserved                           , 4);
  BUNION(SR2, unsigned char,                    //              0x00            Status register 2
    _reserved                           , 1,
    CC1OF                               , 1,    //1             0               Capture/compare x overcapture flag
    CC2OF                               , 1,    //2             0
    CC3OF                               , 1,    //3             0
    _reserved1                          , 4);
  BUNION(EGR, unsigned char,                    //              0x00            Event generation register
    UG                                  , 1,    //0             0               Update generation
    CC1G                                , 1,    //1             0               Capture/compare x generation
    CC2G                                , 1,    //2             0
    CC3G                                , 1,    //3             0
    _reserved                           , 4);
  GENERAL_TIMER_CCMR_TypeDef CCMR1, CCMR2, CCMR3;
  BUNION(CCER1, unsigned char,                  //              0x00            Capture/compare enable register
    CC1E                                , 1,    //0             0               Capture/compare x output enable
    CC1P                                , 1,    //1             0               Capture/compare x output polarity
    _reserved                           , 2,
    CC2E                                , 1,    //4             0
    CC2P                                , 1,    //5             0
    _reserved1                          , 2);
  BUNION(CCER2, unsigned char,                  //              0x00
    CC3E                                , 1,    //0             0
    CC3P                                , 1,    //1             0
    _reserved                           , 6);
  RUNION_16x8(CNTR,, HIGH, LOW);                //              0x0000          Counter: write MS first, read MS first
  unsigned char PSCR;                           //              0x00            Prescaler value (4 bit low)
  RUNION_16x8(ARR,, HIGH, LOW);                 //              0xFFFF          Auto-reload register: write MS first, read MS first
  RUNION_16x8(,, HIGH, LOW)                     //              0x0000          Capture/compare register: write MS first, read MS first
    CCR1, CCR2, CCR3;
} TIM5_TypeDef;
//==============================================================================================================================================================
/*
+) NOTE:
  -asm("RIM") to enable global interrupt
  -IRQ function must clear flag
*/
#define GENERAL_TIMER_EnableInterrupt(TIMER)    (TIMER)->IER.BITS.UIE=1
#define GENERAL_TIMER_DisableInterrupt(TIMER)   (TIMER)->IER.BITS.UIE=0
//==============================================================================================================================================================
/*
+) NOTE:
  -CLK.PCKENR must enable
+) Timer overflow:
    (2^Prescale / F_TIMER) * (ReloadValue + 1) (ms)    //F_TIMER: KHz
*/
#if (__PRODUCT_LINE__ == 0)
  void GENERAL_TIMER_Init(volatile void* TIMER, unsigned char Prescale, unsigned short ReloadValue);     //for tim2 and tim5, Prescale: 0->15
  #define TIM2_Init(Prescale, ReloadValue)      GENERAL_TIMER_Init(&TIM2, Prescale, ReloadValue)
  #define TIM5_Init(Prescale, ReloadValue)      GENERAL_TIMER_Init(&TIM5, Prescale, ReloadValue)
#else
  void TIM2_Init(unsigned char Prescale, unsigned short ReloadValue);   //Prescale: 0->15
  void TIM5_Init(unsigned char Prescale, unsigned short ReloadValue);   //Prescale: 0->15
#endif
void TIM3_Init(unsigned char Prescale, unsigned short ReloadValue);   //Prescale: 0->15
//==============================================================================================================================================================
/*
+) NOTE:
  -GPIO as OUTPUT
  -Option byte to remap channel pin
*/
#if (__PRODUCT_LINE__ == 0)
  void GENERAL_TIMER_GeneratePWM(volatile void* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
  #define TIM2_GeneratePWM(Channel, Duty, IDLE_IsHigh)          GENERAL_TIMER_GeneratePWM(&TIM2, Channel, Duty, IDLE_IsHigh)
  #define TIM5_GeneratePWM(Channel, Duty, IDLE_IsHigh)          GENERAL_TIMER_GeneratePWM(&TIM5, Channel, Duty, IDLE_IsHigh)
#else
  void TIM2_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
  void TIM5_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);  
#endif
void TIM3_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);

#endif