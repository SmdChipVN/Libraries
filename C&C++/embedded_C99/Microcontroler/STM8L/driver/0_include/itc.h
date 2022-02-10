#ifndef _ITC_H_
#define _ITC_H_

#define SPR_LEVEL_0             0x10            //void main()
#define SPR_LEVEL_1             0x01
#define SPR_LEVEL_2             0x00
#define SPR_LEVEL_3             0x11            //software priority disabled

#define IS_LOW_LEVEL            0x00
#define IS_RISING               0x01
#define IS_FAILING              0x02
#define IS_CHANGE_STATE         0x03

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BRUNION_16x8(IS_PIN, , LOW, HIGH,             //0x0-0x1       0x0000          External interrupt sensitivity bits for pin
               xBITS_B(b, 0, 7, 2));
  BUNION(IS_PORT1, unsigned char,               //0x2           0x00            External interrupt for port
         PB                             , 2,    //0-1           0               Port x external interrupt sensitivity bits
         PD                             , 2,    //2-3           0
         PE                             , 2,    //4-5           0
         PF                             , 2);   //6-7           0
  xBUNION(SR_PIN, unsigned char CLR_1,
          b, 0, 7, 1);                          //0x3           0x00            External interrupt status for pin
  BUNION(SR_PORT, unsigned char,                //0x4           0x00            External interrupt status for port
         PB                             , 1,    //0             0
         PD                             , 1,    //1             0
         PE                             , 1,    //2             0
         PF                             , 1,    //3             0
         PG                             , 1,    //4             0
         PH                             , 1,    //5             0
         _Reserved                      , 2);
  BUNION(CONF_PORT1, unsigned char,             //0x5         0x00            External interrupt port select register
         PB                             , 2,    //0-1           0
         PD                             , 1,    //2-3           0
         PE                             , 1,    //4-5           0
         PFLIS                          , 1,    //6             0
         PFES                           , 1);   //7             0                Port F or port E external interrupt select
//======================================================================================================================
  struct
  {
    BUNION(CR1, unsigned char,                  //0x0           0x00            WFE control register 1
           TIM2_EV0                     , 1,    //0             0               TIM2 interrupt event 0
           TIM2_EV1                     , 1,    //1             0               TIM2 interrupt event 1
           TIM1_EV0                     , 1,    //2             0               TIM1 interrupt event 0
           TIM1_EV1                     , 1,    //3             0               TIM1 interrupt event 1
           EXTI_EV0                     , 1,    //4             0               External interrupt event 0
           EXTI_EV1                     , 1,    //5             0               External interrupt event 1
           EXTI_EV2                     , 1,    //6             0               External interrupt event 2
           EXTI_EV3                     , 1);   //7             0               External interrupt event 3
    BUNION(CR2, unsigned char,                  //0x0           0x00            WFE control register 2
           EXTI_EV4                     , 1,    //0             0               External interrupt event 4
           EXTI_EV5                     , 1,    //1             0               External interrupt event 5
           EXTI_EV6                     , 1,    //2             0               External interrupt event 6
           EXTI_EV7                     , 1,    //3             0               External interrupt event 7
           EXTI_EVB                     , 1,    //4             0               External interrupt event on Port B or Port G
           EXTI_EVD                     , 1,    //5             0               External interrupt event on Port D or Port H
           EXTI_EVE_F                   , 1,    //6             0               External interrupt event on Port E or Port F
           ADC1_COMP_EV                 , 1);   //7             0               
    BUNION(CR3, unsigned char,                  //0x0           0x00            WFE control register 3
           TIM3_EV0                     , 1,    //0             0               TIM3 interrupt event 0
           TIM3_EV1                     , 1,    //1             0               TIM3 interrupt event 1
           TIM4_EV                      , 1,    //2             0               TIM4 interrupt event
           SPI1_EV                      , 1,    //3             0               SPI1Rx and Tx interrupt event
           I2C1_EV                      , 1,    //4             0               I2C1 Rx and Tx interrupt event
           USART1_EV                    , 1,    //5             0               USART1 Rx and Tx interrupt event 
           DMA1CH01_EV                  , 1,    //6             0               DMA1 channel 0 and 1 interrupt event 
           DMA1CH23_EV                  , 1);   //7             0               DMA1 channel 2 and 3 interrupt event    
    BUNION(CR4, unsigned char,                  //0x0           0x00            WFE control register 4
           RTC_CSS_LSE_EV               , 1,    //0             0               “RTC” or “CSS on LSE” interrupt event
           SPI2_EV                      , 1,    //1             0               SPI2 Rx and Tx interrupt event
           USART2_EV                    , 1,    //2             0               USART2 Rx and Tx interrupt event
           USART3_EV                    , 1,    //3             0               USART3 Rx and Tx interrupt event
           TIM5_EV0                     , 1,    //4             0               TIM5 interrupt event 0
           TIM5_EV1                     , 1,    //5             0               TIM5 interrupt event 1
           AES_EV                       , 1,    //6             0               AES interrupt event
           _Reserved                    , 1);
  } WFE;                                        //                              Wait for event enable  
//======================================================================================================================
  BUNION(IS_PORT2, unsigned char,               //0x0           0x00            External interrupt for port extend
         PGIS                           , 2,
         PHIS                           , 2,
         _Reserved                      , 4);
  BUNION(CONF_PORT2, unsigned char,             //0x5         0x00            External interrupt port select register
         PFHIS                          , 1,    //0             0
         PG                             , 2,    //1-2           0
         PH                             , 1,    //3-4           0
         PGBS                           , 1,    //5             0               Port G or port B external interrupt select
         PHDS                           , 1,    //6             0               Port H or port D external interrupt select
         _Reserved                      , 1);
} ITC_EXTI_TypeDef;
extern __no_init volatile ITC_EXTI_TypeDef ITC_EXTI;

typedef union
{
  xRSTRUCT(REGS, unsigned char, r, 0, 7, );
  BSTRUCT(BITS, unsigned char,
          TLI                           , 2,    //0-1           0               External Top level Interrupt
          FLASH                         , 2,    //2-3           0               FLASH end of programing / write attempted to protected page interrupt
          DMA1_01                       , 2,    //4-5           0               DMA1 channels 0/1 half transaction/transaction complete interrupt
          DMA1_23                       , 2,    //6-7           0               DMA1 channels 2/3 half transaction/transaction complete interrupt
    
          RTC                           , 2,    //0-1           0               RTC alarm A / wakeup / tamper 1 / tamper 2 / tamper 3
          PVD                           , 2,    //2-3           0               PVD interrupt
          EXTIB                         , 2,    //4-5           0               External interrupt port B
          EXTID                         , 2,    //6-7           0               External interrupt port D
    
          EXTI0                         , 2,    //0-1           0               External interrupt 0
          EXTI1                         , 2,    //2-3           0               External interrupt 1
          EXTI2                         , 2,    //4-5           0               External interrupt 2
          EXTI3                         , 2,    //6-7           0               External interrupt 3
    
          EXTI4                         , 2,    //0-1           0               External interrupt 4
          EXTI5                         , 2,    //2-3           0               External interrupt 5
          EXTI6                         , 2,    //4-5           0               External interrupt 6
          EXTI7                         , 2,    //6-7           0               External interrupt 7
    
          _Reserved0                    , 2,
          CLK                           , 2,    //2-3           0               CLK system clock switch / CSS interrupt
          ADC1                          , 2,    //4-5           0               ACD1 end of conversion / analog watchdog / overrun interrupt
          TIM2                          , 2,    //6-7           0               TIM2 update / overflow / trigger / break interrupt
    
          TIM2_C                        , 2,    //0-1           0               TIM2 Capture / Compare interrupt
          TIM3                          , 2,    //2-3           0               TIM3 Update / Overflow / Trigger / Break interrupt
          TIM3_C                        , 2,    //4-5           0               TIM3 Capture / Compare interrupt
          RI                            , 2,    //6-7           0               RI trigger interrupt
    
          _Reserved1                    , 2,
          TIM4                          , 2,    //2-3           0               TIM4 update / overflow / trigger interrupt
          SPI1                          , 2,    //4-5           0               SPI1 TX buffer empty / RX buffer not empty / error / wakeup interrupt
          USART1_TX                     , 2,    //6-7           0               USART1 transmit data register empty / transmission complete interrupt
    
          USART1_RX                     , 2,    //2-3           0               USART1 received data ready / overrun error / idle line detected / parity error / global error interrupt
          I2C1                          , 2,    //4-5           0               I2C1 interrupt
          _Reserved2                    , 4);
} ITC_SPR_TypeDef;              //                              Software priority register x, It is forbidden to write 10 (priority level 0)
extern __no_init volatile ITC_SPR_TypeDef ITC_SPR;

#endif