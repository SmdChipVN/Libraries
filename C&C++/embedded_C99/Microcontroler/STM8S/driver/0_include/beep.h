/*
  - output beep pin fix on GPIOA.ODR.PIN._0 (SWIM)
  - Frequency in range 500 to 32k (Hz)
*/

#ifndef _BEEP_H_
#define _BEEP_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CSR, unsigned char,                    //              0x00            BEEP control/status register
    DIV                                 , 5,    //0:4           0               BEEP prescaler divider
    EN                                  , 1,    //5             0               BEEP enable
    SEL                                 , 2);   //6-7           0               BEEP selection
} BEEP_TypeDef;
//==============================================================================================================================================================
#define BEEP_ON()                       BEEP.CSR.BITS.EN=1
#define BEEP_OFF()                      BEEP.CSR.BITS.EN=0
//==============================================================================================================================================================
void BEEP_Init(unsigned short Frequency);
void BEEP_SetFrequency(unsigned short Frequency);

#endif