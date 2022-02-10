#ifndef _SYSCFG_H_
#define _SYSCFG_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(RMPCR3, unsigned char,  //0x0           0x00            SYSCFG remap control register 3
    SPI1_REMAP2         , 1,    //0             0               SPI1 remapping (80-pin packages only)
                                //                                              MIS0    MOSI    SCK     NSS
                                //                                      0       PB7     PB6     PB5     PB4
                                //                                      1       PF0     PF1     PF2     PF3
    USART3TR_REMAP      , 1,    //1             0               USART3_TX and USART3_RX remapping
                                //                                              TX      RX
                                //                                      0       PG1     PG0
                                //                                      1       PF0     PF1
    USART3CK_REMAP      , 1,    //2             0               USART3_CK remapping (80-pin)                    0: PG2, 1: PF2        
    TIM3_CH1_REMAP      , 1,    //3             0               TIM3 channel 1 remapping (80-pin)               0: PB1, 1: PI0        
    TIM3_CH2_REMAP      , 1,    //4             0               TIM3 channel 2 remapping (80-pin)               0: PD0, 1: PI3
    CCO_REMAP           , 1,    //5             0               Configurable clock output remapping             0: PC4, 1: PE2
    TIM2_CH1_REMAP      , 1,    //6             0               TIM2 channel 1 remapping (20-pin low-density)   0: PB0, 1: PC5
    TIM2_CH2_REMAP      , 1);   //7             0               TIM2 channel 2 remapping (20-pin low-density)   0: PB2, 1: PC6
  
  BUNION(RMPCR1, unsigned char,  //0x1           0x00            SYSCFG remap control register 1
    ADC1DMA_REMAP       , 2,    //0-1           0               ADC1 DMA channel remapping
    TIM4DMA_REMAP       , 2,    //2-3           0               TIM4 DMA channel remapping
    USART1TR_REMAP      , 2,    //4-5           0               USART1_TX and USART1_RX remapping
                                //                                              TX      RX
                                //                                      0       PC3     PC2
                                //                                      1       PA2     PA3
                                //                                      2       PC5     PC6      
    USART1CK_REMAP      , 1,    //6             0               USART1_CK remapping:    0: PC4, 1: PA0      
    SPI1_REMAP1         , 1);   //7             0               SPI1 remapping:
                                //                                              MIS0    MOSI    SCK     NSS
                                //                                      0       PB7     PB6     PB5     PB4
                                //                                      1       PA2     PA3     PC6     PC5
  BUNION(RMPCR2, unsigned char,  //0x2           0x00            SYSCFG remap control register 2
    ADC1TRIG_REMAP      , 1,    //0             0               ADC1 trigger remapping  0: PA6, 1: PD0
    TIM2TRIG_REMAP      , 1,    //1             0               TIM2 trigger remapping: 0: PB3, 1: PA4
    TIM3TRIG_REMAP1     , 1,    //2             0               TIM3 trigger remapping: 0: PD1, 1: PA5
    TIM2TRIGLSE_REMAP   , 1,    //3             0               TIM2TRIGLSE_REMAP
    TIM3TRIGLSE_REMAP   , 1,    //4             0               TIM3 trigger controlled by LSE
    SPI2_REMAP          , 1,    //5             0               SPI2 remapping:
                                //                                              MIS0    MOSI    SCK     NSS
                                //                                      0       PG7     PG6     PG5     PG4
                                //                                      1       PI3     PI2     PI1     PI0                          
    TIM3TRIG_REMAP2     , 1,    //6             0               TIM3 trigger remapping
    TIM23BKIN_REMAP     , 1);   //7             0               TIM2 break input and TIM3 break input remapping
                                //                                              TIM2_BKIN       TIM3_BKIN
                                //                                      0       PA4             PA5
                                //                                      1       PG0             PG1     (64-80-pin)
} SYSCFG_TypeDef;
extern __no_init volatile SYSCFG_TypeDef SYSCFG;

#endif