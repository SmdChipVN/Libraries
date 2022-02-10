#ifndef _CPU_H_
#define _CPU_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
SFR(SP, 0x81);                                  //                              CPU Stack pointer
SFR(DP0L, 0x82);                                //                              CPU Data pointer 0
SFR(DP0H, 0x83);
SFR(DP1L, 0x84);
SFR(DP1H, 0x85);
SFRB(DPS, 0x92, ,                               //                              CPU Data pointer select
  DPTR                                  , 1,    //0             0
  _Reserved                             , 7);
//==============================================================================================================================================================
#define PSW_ADDRESS                     0xD0
SFRB(PSW, 0xD0, ,                               //                              CPU Program status Word
  P                                     , 1,    //0                             Parity flag
  F1                                    , 1,    //1                             User-defined
  OV                                    , 1,    //2                             Overflow flag
  RS                                    , 2,    //3-4                           Register bank select bits
  F0                                    , 1,    //5                             User-defined
  AC                                    , 1,    //6                             Auxiliary carry flag for BCD operations
  CY                                    , 1);   //7                             Carry flag
SFR(ACC, 0xE0);                                 //                              CPU Accumulator
SFR(B, 0xF0);                                   //                              CPU B register

#endif