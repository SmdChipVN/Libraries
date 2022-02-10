#ifndef _ADVANCED_TIMER_H_
#define _ADVANCED_TIMER_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef union
{
  unsigned char REG;
  BITS_STRUCT(OUTPUT, unsigned char,
    CCS                 , 2,    //0-1           0               Capture/compare selection
    OCFE                , 1,    //2             0               Output compare fast enable
    OCPE                , 1,    //3             0               Output compare preload enable
    OCM                 , 3,    //4:6           0               Output compare mode
    CCCE                , 1);   //7             0               Output compare clear enable
  BITS_STRUCT(INPUT, unsigned char,
    CCS                 , 2,    //0-1           0               Capture/compare selection
    ICPSC               , 2,    //2-3           0               Input capture prescaler
    ICF                 , 4);   //4:7           0               Input capture filter
} CCMR_ADV_TypeDef;             //              0x00            Capture/compare mode register
typedef struct
{
  UNION(CR1, unsigned char,     //0x0           0x00            Control register 1
    CEN                 , 1,    //0             0               Counter enable
    UDIS                , 1,    //1             0               Update disable
    URS                 , 1,    //2             0               Update request source
    OPM                 , 1,    //3             0               One-pulse mode      
    DIR                 , 1,    //4             0               Direction: 0: up-counter
    CMS                 , 2,    //5-6           0               Center-aligned mode selection
    ARPE                , 1);   //7             0               Auto-reload preload enable  
  UNION(CR2, unsigned char,     //0x1           0x00            Control register 2
    CCPC                , 1,    //0             0               Capture/compare preloaded control
    _Reserved           , 1,
    COMS                , 1,    //2             0               Capture/compare control update selection
    CCDS                , 1,    //3             0               Capture/compare DMA selection
    MMS                 , 3,    //4:6           0               Master mode selection
    TI1S                , 1);   //7             0               TI1 (digital filter input) selection
  UNION(SMCR, unsigned char,    //0x2           0x00            Slave mode control register
    SMS                 , 3,    //0:2           0               Clock/trigger/slave mode selection
    OCCS                , 1,    //3             0               OCREFCLR selection
    TS                  , 3,    //4:6           0               Trigger selection
    MSM                 , 1);   //7             0               Master/slave mode
  UNION(ETR, unsigned char,     //0x3           0x00            External trigger register
    EFT                 , 4,    //0:3           0               External trigger filter
    ETPS                , 2,    //4-5           0               External trigger prescaler
    ECE                 , 1,    //6             0               External clock enable
    ETP                 , 1);   //7             0               External trigger polarity  
  UNION(DER, unsigned char,     //0x4           0x00            DMA request enable register
    UDE                 , 1,    //0             0               Update DMA request enable
    CC1DE               , 1,    //1             0               Capture/compare 1 DMA request enable
    CC2DE               , 1,    //2             0               Capture/compare 2 DMA request enable
    CC3DE               , 1,    //3             0               Capture/compare 3 DMA request enable
    CC4DE               , 1,    //4             0               Capture/compare 4 DMA request enable
    COMDE               , 1,    //5             0               Commutation DMA request enable
    _Reserved           , 2);
  UNION(IER, unsigned char,     //0x5           0x00            Interrupt enable register
    UIE                 , 1,    //0             0               Update interrupt enable
    CC1IE               , 1,    //1             0               Capture/compare 1 interrupt enable
    CC2IE               , 1,    //2             0               Capture/compare 2 interrupt enable
    CC3IE               , 1,    //3             0               Capture/compare 3 interrupt enable
    CC4IE               , 1,    //4             0               Capture/compare 4 interrupt enable
    COMIE               , 1,    //5             0               Commutation interrupt enable
    TIE                 , 1,    //6             0               Trigger interrupt enable
    BIE                 , 1);   //7             0               Break interrupt enable  
  UNION(SR1, unsigned char,     //0x6           0x00            Status register 1
    UIF                 , 1,    //0             0               Update interrupt flag
    CC1IF               , 1,    //1             0               Capture/compare 1 interrupt flag
    CC2IF               , 1,    //2             0               Capture/compare 2 interrupt flag
    CC3IF               , 1,    //3             0               Capture/compare 3 interrupt flag
    CC4IF               , 1,    //4             0               Capture/compare 4 interrupt flag
    COMIF               , 1,    //5             0               Commutation interrupt flag
    TIF                 , 1,    //6             0               Trigger interrupt flag
    BIF                 , 1);   //7             0               Break interrupt flag
  UNION(SR2, unsigned char,     //0x7           0x00            Status register 2
    _reserved           , 1,
    CC1OF               , 1,    //1             0               Capture/compare 1 overcapture flag
    CC2OF               , 1,    //2             0               Capture/compare 2 overcapture flag
    CC3OF               , 1,    //3             0               Capture/compare 3 overcapture flag
    CC4OF               , 1,    //4             0               Capture/compare 4 overcapture flag
    _Reserved           , 3);
  UNION(EGR, unsigned char,     //0x8           0x00            Status register 2
    UG                  , 1,    //0             0               Update generation
    CC1G                , 1,    //1             0               Capture/compare 1 generation
    CC2G                , 1,    //2             0               Capture/compare 2 generation
    CC3G                , 1,    //3             0               Capture/compare 3 generation
    CC4G                , 1,    //4             0               Capture/compare 4 generation
    COMG                , 1,    //5             0               Commutation generation
    TG                  , 1,    //6             0               Trigger generation
    BG                  , 1);   //7             0               Break generation
  CCMR_ADV_TypeDef CCMR1;       //0x9           0x00            Capture/compare mode register 1
  CCMR_ADV_TypeDef CCMR2;       //0xA           0x00
  CCMR_ADV_TypeDef CCMR3;       //0xB           0x00
  CCMR_ADV_TypeDef CCMR4;       //0xC           0x00
  UNION(CCER1, unsigned char,   //0xD           0x00            Capture/compare enable register 1
    CC1E                , 1,    //0             0               Capture/compare 1 output enable
    CC1P                , 1,    //1             0               Capture/compare 1 output polarity
    CC1NE               , 1,    //2             0               Capture/compare 1 complementary output enable
    CC1NP               , 1,    //3             0               Capture/compare 1 complementary output polarity
    CC2E                , 1,    //4             0
    CC2P                , 1,    //5             0
    CC2NE               , 1,    //6             0
    CC2NP               , 1);   //7             0
  UNION(CCER2, unsigned char,   //0xE           0x00            Capture/compare enable register 2
    CC3E                , 1,    //0             0
    CC3P                , 1,    //1             0
    CC3NE               , 1,    //2             0
    CC3NP               , 1,    //3             0
    CC4E                , 1,    //4             0
    CC4P                , 1,    //5             0
    _Reserved           , 2);
  REGS_UNION_16x8(CNTR, ,       //0xF-0x10      0x0000          Counter  
                  HIGH, LOW);
  REGS_UNION_16x8(PSCR, ,       //0x11-0x12     0x0000          Prescaler  
                  HIGH, LOW);
  REGS_UNION_16x8(ARR, ,        //0x13-0x14     0xFFFF          Auto-reload register  
                  HIGH, LOW);
  unsigned char RCR;            //0x15          0x00            Repetition counter register
  REGS_UNION_16x8(CCR1, ,       //0x16-0x17     0x0000          Capture/compare register 1
                  HIGH, LOW);
  REGS_UNION_16x8(CCR2, ,       //0x18-0x19     0x0000
                  HIGH, LOW);
  REGS_UNION_16x8(CCR3, ,       //0x1A-0x1B     0x0000
                  HIGH, LOW);
  REGS_UNION_16x8(CCR4, ,       //0x1C-0x1D     0x0000
                  HIGH, LOW);
  UNION(BKR, unsigned char,     //0x1E          0x00            Break register
    LOCK                , 2,    //0-1           0               Lock configuration
    OSSI                , 1,    //2             0               Off state selection for idle mode
    OSSR                , 1,    //3             0               Off state selection for Run mode
    BKE                 , 1,    //4             0               Break enable
    BKP                 , 1,    //5             0               Break polarity
    AOE                 , 1,    //6             0               Automatic output enable
    MOE                 , 1);   //7             0               Main output enable
  unsigned char DTR;            //0x1F          0x00            Deadtime register
  UNION(OISR, unsigned char,    //0x20          0x00            Output idle state register
    OIS1                , 1,    //0             0               Output idle state 1 (OC1 output)
    OIS1N               , 1,    //1             0               Output idle state 1 (OC1N output)
    OIS2                , 1,    //2             0
    OIS2N               , 1,    //3             0
    OIS3                , 1,    //4             0
    OIS3N               , 1,    //5             0
    OIS4                , 1,    //6             0
    _reserved           , 1);
  UNION(DCR1, unsigned char,    //0x21          0x00            DMA control register 1
    DBA                 , 5,    //0:4           0               DMA base address
    _Reserved           , 3);
  UNION(DCR2, unsigned char,    //0x22          0x00            DMA control register 2
    DBL                 , 5,    //0:4           0               DMA burst length
    _Reserved           , 3);
  unsigned char DMAR;           //0x23          0x00            DMA address for burst mode
} ADVANCED_TIMER_TypeDef;

//======================================================================================================================
#include <config.h>
/*
+) NOTE:
  -IRQ function must clear flag
*/
#define ADVANCED_TIMER_EnableInterrupt(TIMER)   BASE_TIMER_EnableInterrupt(TIMER)
#define ADVANCED_TIMER_DisableInterrupt(TIMER)  BASE_TIMER_DisableInterrupt(TIMER)
//======================================================================================================================
#define ADVANCED_TIMER_EnableDMA(TIMER)         BASE_TIMER_EnableDMA(TIMER)
#define ADVANCED_TIMER_DisableDMA(TIMER)        BASE_TIMER_DisableDMA(TIMER)
//======================================================================================================================
/*
+) Timer overflow:
      ReloadValue / (F_TIMER / 2^Prescale) (ms)    //F_TIMER: KHz
*/
#ifdef ADVANCED_TIMER_DIRECT
  void ADVANCED_TIMER_Init(unsigned short Prescale, unsigned short ReloadValue);
#else
  void ADVANCED_TIMER_Init(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned short Prescale, unsigned short ReloadValue);
#endif
//======================================================================================================================
/*
+) NOTE:
  -GPIO as OUTPUT_PUSHPULL
  -SYSCFG to remap channel pin
  -if (Channel & BIT6) -> Channel
  -if (Channel & BIT7) -> ChannelN
*/
#ifdef ADVANCED_TIMER_DIRECT
  void ADVANCED_TIMER_GeneratePWM(unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
#else
  void ADVANCED_TIMER_GeneratePWM(volatile ADVANCED_TIMER_TypeDef* TIMER, unsigned char Channel, unsigned short Duty, unsigned char IDLE_IsHigh);
#endif

#endif