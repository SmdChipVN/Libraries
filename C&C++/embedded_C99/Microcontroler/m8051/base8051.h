#ifndef _BASE8051_H_
#define _BASE8051_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
#define P0_ADDRESS                      0x80
SFRxB(P0, 0x80, , 0, 7, 1);                     //              0xFF            Port 0 data
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
SFR(SP, 0x81);                                  //              0x07            Stack pointer
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
SFR(DPL, 0x82);                                 //              0x00            Data pointer low byte
SFR(DPH, 0x83);                                 //              0x00            Data pointer high byte
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TCON_ADDRESS                    0x88
SFRB(TCON, 0x88, ,                              //              0x00            Timer 0 and 1 control 
  IT0                                   , 1,    //0             0               External interrupt 0 type select
  IE0                                   , 1,    //1             0               External interrupt 0 edge flag
  IT1                                   , 1,    //2             0               External interrupt 1 type select
  IE1                                   , 1,    //3             0               External interrupt 1 edge flag
  TR0                                   , 1,    //4             0               Timer 0 run control
  TF0                                   , 1,    //5             0               Timer 0 overflow flag
  TR1                                   , 1,    //6             0               Timer 1 run control
  TF1                                   , 1);   //7             0               Timer 1 overflow flag
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
SFRB(TMOD, 0x89, ,                              //              0x00            Timer 0 and 1 mode
  M0                                    , 2,    //0:1           0               Timer 0 mode select:
                                                //                                      0: 13-bit
                                                //                                      1: 16-bit, need re-write value TH, TL
                                                //                                      2: 8-bit, auto reload from TH
                                                //                                      3: bla...bla...
  CT0                                   , 1,    //2             0               Timer 0 Counter/Timer select
  GATE0                                 , 1,    //3             0               Timer 0 gate control
  M1                                    , 2,    //4:5           0               Timer 1 mode select
  CT1                                   , 1,    //6             0               Timer 1 Counter/Timer select
  GATE1                                 , 1);   //7             0               Timer 1 gate control
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
SFR(TL0, 0x8A);                                 //              0x00            Timer 0 low byte
SFR(TH0, 0x8C);                                 //              0x00            Timer 0 high byte
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
SFR(TL1, 0x8B);                                 //              0x00            Timer 1 low byte
SFR(TH1, 0x8D);                                 //              0x00            Timer 1 high byte
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define P1_ADDRESS                      0x90
SFRxB(P1, 0x90, , 0, 7, 1);                     //              0xFF            Port 1 data
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SCON_ADDRESS                    0x98
SFRB(SCON, 0x98, ,                              //              0x00            Serial port 0 control
  RI                                    , 1,    //0             0               Receiving interrupt flag
  TI                                    , 1,    //1             0               Transmission interrupt flag
  RB8                                   , 1,    //2             0               9th received bit
  TB8                                   , 1,    //3             0               9th transmitted bit
  REN                                   , 1,    //4             0               Receiving enable
  SM2                                   , 1,    //5             0               
  SM1                                   , 1,    //6             0               
  SM0_FE                                , 1);   //7             0
//----------------------------------------------------------------------------------------------------------------------
SFR(SBUF, 0x99);                                //              0x00            Serial port 0 data buffer
//----------------------------------------------------------------------------------------------------------------------
#define P2_ADDRESS                      0xA0
SFRxB(P2, 0xA0, , 0, 7, 1);                     //              0x00            Port 2 data
//----------------------------------------------------------------------------------------------------------------------
#define P3_ADDRESS                      0xB0
SFRxB(P3, 0xB0, , 0, 7, 1);                     //              0x01            Port 3 data
//----------------------------------------------------------------------------------------------------------------------
#define PSW_ADDRESS                     0xD0
SFRB(PSW, 0xD0, ,                               //              0x00            Program status word
  const P                               , 1,    //0             0               Parity flag
  F1                                    , 1,    //1             0               User flag 1
  OV                                    , 1,    //2             0               Overflow flag
  RS                                    , 2,    //3             0               Register bank selection bits
  F0                                    , 1,    //4             0               User flag 0
  AC                                    , 1,    //5             0               Auxiliary carry
  CY                                    , 1);   //6             0               Carry flag
//------------------------------------------------7----------------------------------------------------------------------
SFR(ACC, 0xE0);
//----------------------------------------------------------------------------------------------------------------------
SFR(B, 0xF0);

#endif