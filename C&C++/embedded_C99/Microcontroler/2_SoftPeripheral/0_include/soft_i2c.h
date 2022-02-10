/*

*/
#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#include <data_stream.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
//==============================================================================================================================================================
//===========================================================       LEVEL 1      ===============================================================================
//==============================================================================================================================================================
typedef struct
{
  void (__code* ConfigSDA)(reg8 IsSet);
  reg8 (__code* ReadSDA)();
  void (__code* ConfigSCL)(reg8 IsSet);
  void (__code* ConfigSDAMode)(reg8 IsOutput);
  void (__code* Delay)();
} SI2CFunction_TypeDef;
//==============================================================================================================================================================
/*
  NOTE:
    SlaveAddress: RX8025 0x32 -> 0x64
    if (SlaveAddress & 1) -> using Stream
*/
typedef union
{
  struct
  {
    unsigned char SlaveAddress;
    unsigned char DataAddress;
    unsigned char Length;
    unsigned char* Data;
  } Normal;
  struct
  {
    DATA_STREAM_STATE State;
    unsigned char BitIndex;
    unsigned char Length;
    struct
    {
      unsigned char SlaveAddress;
      unsigned char DataAddress;
      unsigned char Data[64];
    }* Info;
  } Stream;
} SI2CReader_TypeDef;
reg8 SI2C_ReadBytes_0(SI2CReader_TypeDef* SI2CReader);
reg8 SI2C_ReadBytes_1(const SI2CFunction_TypeDef __code* SI2CFunction, SI2CReader_TypeDef* SI2CReader);
//==============================================================================================================================================================
typedef union
{
  struct
  {
    unsigned char SlaveAddress;
    unsigned char DataAddress;
    unsigned char Length;
    const unsigned char __gptr* Data;
  } Normal;
  struct
  {
    DATA_STREAM_STATE State;
    unsigned char BitIndex;
    unsigned char Length;
    struct
    {
      unsigned char SlaveAddress;
      unsigned char DataAddress;
      const unsigned char Data[64];
    } __gptr* Info;
  } Stream;
} SI2CWriter_TypeDef;
reg8 SI2C_WriteBytes_0(SI2CWriter_TypeDef* SI2CWriter);
reg8 SI2C_WriteBytes_1(const SI2CFunction_TypeDef __code* SI2CFunction, SI2CWriter_TypeDef* SI2CWriter);
//==============================================================================================================================================================
void SI2C_Process_0(SI2CWriter_TypeDef* SI2CWriter);
void SI2C_Process_1(const SI2CFunction_TypeDef __code* SI2CFunction, SI2CWriter_TypeDef* SI2CWriter);
  
#endif