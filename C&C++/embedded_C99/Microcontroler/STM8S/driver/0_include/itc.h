#ifndef _ITC_H_
#define _ITC_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef BRUNION_16x8(ITC_EXTI_TypeDef,,         //                              external interrupt sensitivity bits  
  CR1, CR2,                                     //              0x0000
  
  GPIOA                                 , 2,    //0-1           0               PORT A:
                                                //                                      0: LOW_LEVEL
                                                //                                      1: RISING
                                                //                                      2: FAILING
                                                //                                      3: CHANGE_STATE
  GPIOB                                 , 2,    //2-3           0
  GPIOC                                 , 2,    //4-5           0
  GPIOD                                 , 2,    //6-7           0
  GPIOE                                 , 2,    //0-1           0
  TL                                    , 1,    //2             0               Top level interrupt sensitivity
  _reserved                             , 5);
typedef union
{
  xRSTRUCT(REGS, unsigned char,
    r, 0, 7,);
  BSTRUCT(BITS, unsigned char,
    _reserved                           , 2,    //0-1           1               External Top level Interrupt
                                                //                                      2: Level 0 (main) (Lowest)
                                                //                                      1: Level 1
                                                //                                      0: Level 2
                                                //                                      3: Level 3 (software priority disabled)
    FLASH                               , 2,    //2-3           1               FLASH end of programing / write attempted to protected page interrupt
    DMA1_01                             , 2,    //4-5           1               DMA1 channels 0/1 half transaction/transaction complete interrupt
    DMA1_23                             , 2,    //6-7           1               DMA1 channels 2/3 half transaction/transaction complete interrupt    
    RTC                                 , 2,    //0-1           1               RTC alarm A / wakeup / tamper 1 / tamper 2 / tamper 3
    PVD                                 , 2,    //2-3           1               PVD interrupt
    EXTIB                               , 2,    //4-5           1               External interrupt port B
    EXTID                               , 2,    //6-7           1               External interrupt port D    
    EXTI0                               , 2,    //0-1           1               External interrupt 0
    EXTI1                               , 2,    //2-3           1               External interrupt 1
    EXTI2                               , 2,    //4-5           1               External interrupt 2
    EXTI3                               , 2,    //6-7           1               External interrupt 3    
    EXTI4                               , 2,    //0-1           1               External interrupt 4
    EXTI5                               , 2,    //2-3           1               External interrupt 5
    EXTI6                               , 2,    //4-5           1               External interrupt 6
    EXTI7                               , 2,    //6-7           1               External interrupt 7    
    _reserved0                          , 2,
    CLK                                 , 2,    //2-3           1               CLK system clock switch / CSS interrupt
    ADC1                                , 2,    //4-5           1               ACD1 end of conversion / analog watchdog / overrun interrupt
    TIM2                                , 2,    //6-7           1               TIM2 update / overflow / trigger / break interrupt    
    TIM2_C                              , 2,    //0-1           1               TIM2 Capture / Compare interrupt
    TIM3                                , 2,    //2-3           1               TIM3 Update / Overflow / Trigger / Break interrupt
    TIM3_C                              , 2,    //4-5           1               TIM3 Capture / Compare interrupt
    RI                                  , 2,    //6-7           1               RI trigger interrupt    
    _reserved1                          , 2,
    TIM4                                , 2,    //2-3           1               TIM4 update / overflow / trigger interrupt
    SPI1                                , 2,    //4-5           1               SPI1 TX buffer empty / RX buffer not empty / error / wakeup interrupt
    USART1_TX                           , 2,    //6-7           1               USART1 transmit data register empty / transmission complete interrupt    
    USART1_RX                           , 2,    //0-1           1               USART1 received data ready / overrun error / idle line detected / parity error / global error interrupt
    I2C1                                , 2,    //2-3           1               I2C1 interrupt
    _reserved2                          , 4);
} ITC_SPR_TypeDef;                              //                              Software priority register x, It is forbidden to write 10 (priority level 0)          //memory map: 0x7F70

#endif