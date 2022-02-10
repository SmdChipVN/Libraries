#ifndef _TIMER_8BIT_H_
#define _TIMER_8BIT_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
SFR(const TIM3_CNT, 0xCA);                      //              0x00            Timer count byte
SFRB(TIM3_CTL, 0xCB, ,                          //              0x80            Timer 3 Control
  MODE                                  , 2,    //0-1           0               Timer 3 mode:
                                                //                                      0: Free-running, repeat 0x00 -/ 0xFF
                                                //                                      1: Down, once TIM3_CC0 -\ 0x00
                                                //                                      2: Modulo, repeat 0x00 -/ TIM3_CC0
                                                //                                      3: Up-and-down, repeat 0x00 -/ TIM3_CC0 -\ 0x00
  CLR                                   , 1,    //2             0               Clear counter
  OVFIM                                 , 1,    //3             1               Overflow interrupt mask
  START                                 , 1,    //4             0               Start timer
  DIV                                   , 3);   //5:7           0               Prescaler divider: F_TIMER = CLOCK_CTRL_CMD.TICK_SPEED / (2^DIV)
SFRB(TIM3_CCTL0, 0xCC, ,                        //              0x40            Timer 3 Channel 0 Capture or Compare Control
  CAP                                   , 2,    //0-1           0               Capture mode:
                                                //                                      0: No capture
                                                //                                      1: Capture on rising edge
                                                //                                      2: Capture on falling edge
                                                //                                      3: Capture on both edges
  MODE                                  , 1,    //2             0               Select Timer 3 channel 0 mode:
                                                //                                      0: Capture mode
                                                //                                      1: Compare mode
  CMP                                   , 3,    //3:5           0               Channel 0 compare output mode select:
                                                //                                      0: Set output on compare
                                                //                                      1: Clear output on compare
                                                //                                      2: Toggle output on compare
                                                //                                      3: Set output on compare-up, clear on 0
                                                //                                      4: Clear output on compare-up, set on 0
                                                //                                      5: Set output on compare, clear on 0xFF
                                                //                                      6: Clear output on compare, set on 0x00
                                                //                                      7: Initialize output pin. CMP[2:0] is not changed
  IM                                    , 1,    //6             1               Channel 0 interrupt mask
  _reserved                             , 1);
SFR(TIM3_CC0, 0xCD);                            //              0x00            Timer 3 Channel 0 Capture or Compare Value
SFRB(TIM3_CCTL1, 0xCE, ,                        //                              (same as CH1)
  CAP                                   , 2,
  MODE                                  , 1,
  CMP                                   , 3,
  IM                                    , 1,
  _reserved                             , 1);
SFR(TIM3_CC1, 0xCF);
//==============================================================================================================================================================
SFR(const TIM4_CNT, 0xEA);
SFRB(TIM4_CTL, 0xEB, ,
  MODE                                  , 2,
  CLR                                   , 1,
  OVFIM                                 , 1,
  START                                 , 1,
  DIV                                   , 3);
SFRB(TIM4_CCTL0, 0xEC, ,
  CAP                                   , 2,
  MODE                                  , 1,
  CMP                                   , 3,
  IM                                    , 1,
  _reserved                             , 1);
SFR(TIM4_CC0, 0xED);
SFRB(TIM4_CCTL1, 0xEE, ,
  CAP                                   , 2,
  MODE                                  , 1,
  CMP                                   , 3,
  IM                                    , 1,
  _reserved                             , 1);
SFR(TIM4_CC1, 0xEF);
//==============================================================================================================================================================
#define TIM_IF_ADDRESS                  0xD8
SFRB(TIM_IF, 0xD8, ,                            //              0x40            Timer 1 Interrupt Mask, Timers 3 and 4 Interrupt Flags
  TIM3_OVF                              , 1,    //0             0               Timer 3 overflow interrupt flag
  TIM3_CH0                              , 1,    //1             0               Timer 3 channel 0 interrupt flag
  TIM3_CH1                              , 1,    //2             0
  TIM4_OVF                              , 1,    //3             0
  TIM4_CH0                              , 1,    //4             0
  TIM4_CH1                              , 1,    //5             0
  TIM1_OVF_IM                           , 1,    //6             1               Timer 1 overflow interrupt mask
  _reserved                             , 1);
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#define TIMER_8BIT_Init(TIMER, Mode, Prescale)  TIM##TIMER##_CTL.REG = (Mode) | ((Prescale) << 5) | BIT2 | BIT4
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TIMER_8BIT_EnableInterrupt(TIMER)       TIM##TIMER##_CTL.REG |= 0x08
#define TIMER_8BIT_DisableInterrupt(TIMER)      TIM##TIMER##_CTL.REG &= ~0x08
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TIMER_8BIT_Turn(TIMER, IsOn)            TIM##TIMER##_CTL.BITS.START = IsOn
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TIMER_8BIT_CapComMode(TIMER, Channel, Mode, CapMode, CompareMode, Interrupt)   TIM##TIMER##_CCTL##Channel.REG = (CapMode) | ((Mode) << 2) | ((CompareMode) << 3) | ((Interrupt) << 6)

#endif