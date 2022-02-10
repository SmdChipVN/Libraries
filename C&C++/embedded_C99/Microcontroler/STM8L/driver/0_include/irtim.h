#ifndef _IRTIM_H_
#define _IRTIM_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(CR, unsigned char,      //0x0           0x00            Control register
    IR_EN               , 1,    //0             0               Infrared output enable
    HS_EN               , 1,    //1             0               High Sink LED driver capability enable
    _Reserved           , 6);
} IRTIM_TypeDef;

#endif