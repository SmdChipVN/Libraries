#ifndef _TIMER_16BIT_H_
#define _TIMER_16BIT_H_

#include <define.h>
//                                      //Address       Default         Description

SFR(TIM1_CNTL           , 0xE2);        //              0x00            Timer 1 count low
SFR(TIM1_CNTH           , 0xE3);        //              0x00            Timer 1 count high
SFRS(TIM1_CTL           , 0xE4, ,       //              0x00            Timer 1 Control
     MODE               , 2,            //0-1           0               Timer 1 mode select:
                                        //                                      0: Operation is suspended
                                        //                                      1: Free-running, repeatedly count from 0x0000 to 0xFFFF
                                        //                                      2: Modulo, repeatedly count from 0x0000 to TIM1_CC0
                                        //                                      3: Up-and-down, repeatedly count from 0x0000 to TIM1_CC0 and from TIM1_CC0 down to 0x0000
     DIV                , 2,            //2-3           0
     _reserved          , 4);
SFRS(TIM1_STAT          , 0xAF, ,       //              0x00            Timer 1 Status
     CH0_IF             , 1,            //              0               Timer 1 channel 0 interrupt flag
     CH1_IF             , 1,            //              0
     CH2_IF             , 1,            //              0
     CH3_IF             , 1,            //              0
     CH4_IF             , 1,            //              0
     OVF_IF             , 1,            //              0               Timer 1 counter-overflow interrupt flag
     _reserved          , 2);
SFRS(TIM1_CCTL0         , 0xE5, ,       //              0x40            Timer 1 Channel 0 Capture or Compare Control
     CAP                , 2,            //0-1           0               Capture mode:
                                        //                                      0: No capture
                                        //                                      1: Capture on rising edge
                                        //                                      2: Capture on falling edge
                                        //                                      3: Capture on both edges
     MODE               , 1,            //2             0               Select Timer 3 channel 0 mode:
                                        //                                      0: Capture mode
                                        //                                      1: Compare mode
     CMP                , 3,            //3:5           0               Channel 0 compare output mode select:
                                        //                                      0: Set output on compare
                                        //                                      1: Clear output on compare
                                        //                                      2: Toggle output on compare
                                        //                                      3: Set output on compare-up, clear on 0
                                        //                                      4: Clear output on compare-up, set on 0
                                        //                                      7: Initialize output pin. CMP[2:0] is not changed
     IM                 , 1,            //6             1               Channel 0 interrupt mask
     RFIRQ              , 1);           //7             0               When set, use RF interrupt for capture instead of regular capture input
SFR(TIM1_CC0L           , 0xDA);        //              0x00            Timer 1 Channel 0 Capture or Compare Value low
SFR(TIM1_CC0H           , 0xDB);        //              0x00            Timer 1 Channel 0 Capture or Compare Value high
SFRS(TIM1_CCTL1         , 0xE6, ,
     CAP                , 2,
     MODE               , 1,
     CMP                , 3,
     IM                 , 1,
     RFIRQ              , 1);
SFR(TIM1_CC1H           , 0xDD);
SFR(TIM1_CC1L           , 0xDC);
SFRS(TIM1_CCTL2         , 0xE7, ,
     CAP                , 2,
     MODE               , 1,
     CMP                , 3,
     IM                 , 1,
     RFIRQ              , 1);
SFR(TIM1_CC2H           , 0xDF);
SFR(TIM1_CC2L           , 0xDE);
xSFRS(TIM1_CCTL3        , 0x62A3, ,
     CAP                , 2,
     MODE               , 1,
     CMP                , 3,
     IM                 , 1,
     RFIRQ              , 1);
xSFR(TIM1_CC3H          , 0x62AD);
xSFR(TIM1_CC3L          , 0x62AC);
xSFRS(TIM1_CCTL4        , 0x62A4, ,
     CAP                , 2,
     MODE               , 1,
     CMP                , 3,
     IM                 , 1,
     RFIRQ              , 1);
xSFR(TIM1_CC4H          , 0x62AF);
xSFR(TIM1_CC4L          , 0x62AE);
xSFRS(TIM1_IRCTL        , 0x6281, ,     //              0x00            Timer 1 IR Generation Control
     IRGEN              , 1,            //0             0               ?
     _reserved          , 7);

#endif