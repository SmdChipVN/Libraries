#ifndef _RST_H_
#define _RST_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  unsigned char RSTPIN_KEY;     //0x0           0x00            write 0xD0: NRST/PA1 configured as general purpose output
  BUNION(SR, unsigned char,      //0x1           0x00            Reset status register
    PORF                , 1,    //0             0               Power-on Reset (POR) flag 
    IWDGF               , 1,    //1             0               Independent Watchdog reset flag
    ILLOPF              , 1,    //2             0               Illegal opcode reset flag
    SWIMF               , 1,    //3             0               SWIM reset flag
    WWDGF               , 1,    //4             0               Window Watchdog reset flag
    BORF                , 1,    //5             0               Brownout reset flag
    _Reserved           , 2);
} RST_TypeDef;
extern __no_init volatile RST_TypeDef RST;

#endif