#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP_ON()                       BEEP.CSR2.BITS.EN=1
#define BEEP_OFF()                      BEEP.CSR2.BITS.EN=0
/*
  - output beep pin fix on GPIOA.ODR.PIN._0 (SWIM)
  - Frequency in range 148 to 6333 (Hz)
*/
void BEEP_Init(unsigned short Frequency);
void BEEP_SetFrequency(unsigned short Frequency);
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(CSR1, unsigned char,    //0             0x00            BEEP control/status register 1
    MSR                 , 1,    //0             0               Measurement enable
    _reserved           , 7);
  unsigned char _reserved[2];
  BUNION(CSR2, unsigned char,    //3             0x1F            BEEP control/status register 2
    DIV                 , 5,    //0:4           31              BEEP prescaler divider
    EN                  , 1,    //5             0               BEEP enable
    SEL                 , 2);   //6-7           0               BEEP selection
} BEEP_TypeDef;
extern __no_init volatile BEEP_TypeDef BEEP;

#endif