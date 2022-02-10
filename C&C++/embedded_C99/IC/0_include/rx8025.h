/*
  must #define below into <config.h>:

#define RX8028_READ(Address,Buffer,Length)      I2C_ReadBytes(0x32,Address,Buffer,Length)               //0x32 is address of RX8025
#define RX8025_WRITE(Address,Data,Length)       I2C_WriteBytes(0x32,Address,Data,Length)
*/

#ifndef _RX8025_H_
#define _RX8025_H_

#include <common.h>
#include <datetime.h>
#include <config.h>

bool RX8025_Init();
bool RX8025_Read(DateTime_TypeDef* DateTime);
bool RX8025_Save(DateTime_TypeDef* DateTime);

#endif