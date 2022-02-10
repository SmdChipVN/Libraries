#ifndef _WINDOW_WATCHDOG_H_
#define _WINDOW_WATCHDOG_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR, unsigned char,      //0x0           0x00            Control register
    T                   , 7,    //0:6           0               7-bit counter (MSB to LSB)
    WDGAA               , 1);   //7             0               Activation bit
  BUNION(WR, unsigned char,      //0x1           0x00            Window register
    W                   , 7,    //0:6           0               7-bit window value
    _Reserved           , 1);
} WWDG_TypeDef;
extern __no_init volatile WWDG_TypeDef WWDG;

#endif