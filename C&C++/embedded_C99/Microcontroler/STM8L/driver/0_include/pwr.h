#ifndef _PWR_H_
#define _PWR_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CSR1, unsigned char,    //0             0x00            PWR control and status register 1
    PVDE                , 1,    //0             0               Power voltage detector (PVD) enable
    PLS                 , 3,    //1:3           0               PVD level selection
    PVDIEN              , 1,    //4             0               PVD interrupt enable
    PVDIF               , 1,    //5             0               PVD interrupt flag
    const PVDOF         , 1,    //6             0               PVD output flag
    _Reserved           , 1);
  BUNION(CSR2, unsigned char,    //0             0x00            PWR control and status register 2
    const VREFINTF      , 1,    //0             0               Internal reference voltage status flag
    ULP                 , 1,    //1             0               Ultra-low-power configuration
    FWU                 , 1,    //2             0               Fast wake up configuration
    _Reserved           , 5);
} PWR_TypeDef;
extern __no_init volatile PWR_TypeDef PWR;

#endif