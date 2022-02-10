#ifndef _DATA_ACCESS_H_
#define _DATA_ACCESS_H_

#include <common.h>

typedef struct
{
  unsigned char* Data;
  void (*DMATransfer)(unsigned char* Data, reg16 Size);
  void (*EndTransferHandle)();
} DMAFunction_TypeDef;

#endif