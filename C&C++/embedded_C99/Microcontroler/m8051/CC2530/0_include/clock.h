#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
SFRB(CLOCK_CTRL_STATUS, 0x9E, ,                 //              0xC9
  SPEED                                 , 3,    //0:2           1               Current clock speed
                                                //                                      0: 32 MHz
                                                //                                      1: 16 MHz
                                                //                                      2: 8 MHz
                                                //                                      3: 4 MHz
                                                //                                      4: 2 MHz
                                                //                                      5: 1 MHz
                                                //                                      6: 500 KHz
                                                //                                      7: 250 KHz
  TICK_SPEED                            , 3,    //3:5           1               Current timer ticks output setting
  OSC                                   , 1,    //6             1               Current system clock selected           0: 32-MHz XOSC          1: 16-MHz RCOSC
  OSC32K                                , 1);   //7             1               Current 32-kHz clock source selected    0: 32-kHz XOSC          1: 32-kHz RCOSC
SFRB(CLOCK_CTRL_CMD, 0xC6, ,                    //              0xC9
  SPEED                                 , 3,    //0:2           1               Clock speed. Cannot be higher than system clock setting given by the OSC bit setting
  TICK_SPEED                            , 3,    //3:5           1               Timer ticks output setting. Cannot be higher than system clock setting given by OSC bit setting
  OSC                                   , 1,    //6             1               System clock-source select
  OSC32K                                , 1);   //7             1               32-kHz clock-source select
SFRB(SLEEP_CMD, 0xBE, ,                         //              0x04
  MODE                                  , 2,    //0-1           0               Power-mode setting
  _Reserved                             , 5,    //2:6           1               Always write 00001b
  OSC32K_CALDIS                         , 1);   //7             0               Disable 32-kHz RC oscillator calibration
SFRB(SLEEP_STATUS, 0x9D, ,                      //              
  CLK32K                                , 1,    //0             0               The 32-kHz clock signal
  _Reserved                             , 2,
  RST                                   , 2,    //3-4           --              Status bit indicating the cause of the last reset
  _Reserved1                            , 2,
  OSC32K_CALDIS                         , 1);   //7             0               32-kHz RC oscillator calibration status
/*
  Init clock 32MHz
*/
#define CLOCK_Init()            CLOCK_CTRL_CMD.REG = BIT7;while (CLOCK_CTRL_STATUS.REG != BIT7)

#endif