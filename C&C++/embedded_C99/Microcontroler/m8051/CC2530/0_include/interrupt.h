#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

//                                      |       //Enable        Flag            Description                                   
#define RFERR_IRQv                      0x03    //IEN0.RFERRIE  TCON.RFERRIF    RF core-error situation
#define ADC_IRQv                        0x0B    //IEN0.ADCIE    TCON.ADCIF      ADC end of conversion
#define URX0_IRQv                       0x13    //IEN0.URX0IE   TCON.URX0IF     USART 0 RX complete
#define URX1_IRQv                       0x1B    //IEN0.URX1IE   TCON.URX1IF     USART 1 RX complete
#define ENC_IRQv                        0x23    //IEN0.ENCIE    S0CON.ENCIF     AES encryption or decryption complete
#define ST_IRQv                         0x2B    //IEN0.STIE     IRCON.STIF      Sleep Timer compare
#define P2INT_IRQv                      0x33    //IEN2.P2IE     IRCON2.P2IF     Port-2 inputs, USB, or I2C
#define UTX0_IRQv                       0x3B    //IEN2.UTX0IE   IRCON2.UTX0IF   USART 0 TX complete
#define DMA_IRQv                        0x43    //IEN1.DMAIE    IRCON.DMAIF     DMA transfer complete
#define TIM1_IRQv                       0x4B    //IEN1.T1IE     IRCON.T1IF      Timer 1 (16-bit) capture, compare, overflow
#define TIM2_IRQv                       0x53    //IEN1.T2IE     IRCON.T2IF      Timer 2
#define TIM3_IRQv                       0x5B    //IEN1.T3IE     IRCON.T3IF      Timer 3 (8-bit) capture, compare, overflow
#define TIM4_IRQv                       0x63    //IEN1.T4IE     IRCON.T4IF      Timer 4 (8-bit) capture, compare, overflow
#define P0INT_IRQv                      0x6B    //IEN1.P0IE     IRCON.P0IF      Port 0 inputs
#define UTX1_IRQv                       0x73    //IEN2.UTX1IE   IRCON2.UTX1IF   USART 1 TX complete
#define P1INT_IRQv                      0x7B    //IEN2.P1IE     IRCON2.P1IF     Port 1 inputs
#define RF_IRQv                         0x83    //IEN2.RFIE     S1CON.RFIF      RF general interrupts
#define WDT_IRQv                        0x8B    //IEN2.WDTIE    IRCON2.WDTIF    Watchdog overflow in timer mode
//==============================================================================================================================================================
#define RFERR_IRQn                      0
#define ADC_IRQn                        1
#define URX0_IRQn                       2
#define URX1_IRQn                       3
#define ENC_IRQn                        4
#define ST_IRQn                         5
#define P2INT_IRQn                      6
#define UTX0_IRQn                       7
#define DMA_IRQn                        8
#define TIM1_IRQn                       9
#define TIM2_IRQn                       10
#define TIM3_IRQn                       11
#define TIM4_IRQn                       12
#define P0INT_IRQn                      13
#define UTX1_IRQn                       14
#define P1INT_IRQn                      15
#define RF_IRQn                         16
#define WDT_IRQn                        17
//==============================================================================================================================================================
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
#define ITC_IE0_ADDRESS                 0xA8
SFRB(ITC_IEN0, 0xA8, ,                          //              0x00            Interrupt Enable 0
  RF_ERR                                , 1,    //0             0               RF core error
  ADC                                   , 1,    //1             0               ADC
  RX0                                   , 1,    //2             0               USART0 RX
  RX1                                   , 1,    //3             0               USART 1 RX
  AES                                   , 1,    //4             0               AES encryption and decryption
  SLEEP_TIMER                           , 1,    //5             0               Sleep Timer
  _reserved                             , 1,
  EA                                    , 1);   //7             0               Global interrupts
#define ITC_IE1_ADDRESS 0xB8
SFRB(ITC_IEN1, 0xB8, ,                          //              0x00            Interrupt Enable 1
  DMA                                   , 1,    //0             0               DMA transfer
  TIM1                                  , 1,    //1             0               Timer 1
  TIM2                                  , 1,    //2             0               Timer 2
  TIM3                                  , 1,    //3             0               Timer 3
  TIM4                                  , 1,    //4             0               Timer 4
  PORT0                                 , 1,    //5             0               Port 0
  _reserved                             , 2);
SFRB(ITC_IEN2, 0x9A, ,                          //              0x00            Interrupt Enable 2
  RF                                    , 1,    //0             0               RF general
  PORT2                                 , 1,    //0             0               Port 2 and USB
  TX0                                   , 1,    //0             0               USART 0 TX
  TX1                                   , 1,    //0             0               USART 1 TX
  PORT1                                 , 1,    //0             0               Port 1
  WDT                                   , 1,    //0             0               Watchdog Timer
  _reserved                             , 2);
#define ITC_IF0_ADDRESS                 0x88
SFRB(ITC_IF0, 0x88, ,                           //              0x00            Interrupt Flags
  _reserved                             , 1,    //0             1               Must always be set to 1
  RF_ERR                                , 1,    //1             0               RF core error interrupt flag
  _reserved1                            , 1,    //2             0               Must always be set to 1
  RX0                                   , 1,    //3             0               USART 0 RX interrupt flag
  _reserved2                            , 1,
  ADC                                   , 1,    //5             0               ADC interrupt flag
  _reserved3                            , 1,
  RX1                                   , 1);   //7             0               USART 1 RX interrupt flag
#define ITC_IF1_ADDRESS                 0x98
SFRB(ITC_IF1, 0x98, ,                           //              0x00            Interrupt Flags
  AES                                   , 2,    //0-1           0               AES interrupt flag
  _reserved                             , 6);
SFRB(ITC_IF2, 0x9B, ,                           //              0x00            Interrupt Flags
  RF                                    , 2,    //0-1           0               RF general interrupt flag
  _reserved                             , 6);
#define ITC_IF3_ADDRESS                 0xC0
SFRB(ITC_IF3, 0xC0, ,                           //              0x00            Interrupt Flags
  DMA                                   , 1,    //0             0               DMA-complete
  TIM1                                  , 1,    //1             0               Timer 1
  TIM2                                  , 1,    //2             0               Timer 2
  TIM3                                  , 1,    //3             0               Timer 3
  TIM4                                  , 1,    //4             0               Timer 4
  PORT0                                 , 1,    //5             0               Port 0
  _reserved                             , 1,
  SLEEP_TIMER                           , 1);   //7             0               Sleep Timer
#define ITC_IF4_ADDRESS                 0xE8
SFRB(ITC_IF4, 0xE8, ,                           //              0x00            Interrupt Flags
  PORT2                                 , 1,    //0             0               Port 2
  TX0                                   , 1,    //1             0               USART 0 TX
  TX1                                   , 1,    //2             0               USART 1 TX
  PORT1                                 , 1,    //3             0               Port 1
  WDT                                   , 1,    //4             0               Watchdog Timer
  _reserved                             , 3);
SFRB(ITC_IP0, 0xA9, ,                           //              0x00            Interrupt Priority
  IPG0                                  , 1,    //0             0               Interrupt group 0, priority control bit 0
  IPG1                                  , 1,    //1             0
  IPG2                                  , 1,    //2             0
  IPG3                                  , 1,    //3             0
  IPG4                                  , 1,    //4             0
  IPG5                                  , 1,    //5             0
  _reserved                             , 2);
SFRB(ITC_IP1, 0xB9, ,                           //              0x00            Interrupt Priority
  IPG0                                  , 1,    //0             0               Interrupt group 0, priority control bit 1
  IPG1                                  , 1,    //1             0
  IPG2                                  , 1,    //2             0
  IPG3                                  , 1,    //3             0
  IPG4                                  , 1,    //4             0
  IPG5                                  , 1,    //5             0
  _reserved                             , 2);

#endif