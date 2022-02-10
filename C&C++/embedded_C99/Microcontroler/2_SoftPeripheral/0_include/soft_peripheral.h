#ifndef _SOFT_PERIPHERAL_H_
#define _SOFT_PERIPHERAL_H_

#include <DataStream.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  unsigned char State;
  DataStream_TypeDef Data;
} PeripheralStage_TypeDef;

#endif