#ifndef _INDEPENDENT_WATCHDOG_H_
#define _INDEPENDENT_WATCHDOG_H_

#define IWDG_KEY_ENABLE         0xCC
#define IWDG_KEY_REFRESH        0xAA
#define IWDG_KEY_ACCESS         0x55            //enables the access to the protected IWDG_PR and IWDG_RLR
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  unsigned char KEY;            //0x0           0x--            Key value
  BUNION(PR, unsigned char,      //0x1           0x00            BEEP control/status register 1
    PR2                 , 3,    //0:2           0               Prescaler divider 
    _Reserved           , 5);
  unsigned char RLR;            //0x2           0xFF            Watchdog counter reload value
} IWDG_TypeDef;
extern __no_init volatile IWDG_TypeDef IWDG;

#endif