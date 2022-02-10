#ifndef _SOFT_CRC_H_
#define _SOFT_CRC_H_

#include <common.h>

typedef struct
{
  unsigned char ReverseIn;
  unsigned char ReverseOut;
  union
  {
    struct
    {
      unsigned char Preset;
      unsigned char XorOut;
      unsigned char Polynomial;
    } CRC8;
    struct
    {
      unsigned short Preset;
      unsigned short XorOut;
      unsigned short Polynomial;
    } CRC16;
    struct
    {
      unsigned long Preset;
      unsigned long XorOut;
      unsigned long Polynomial;
    } CRC32;
  };
} CRCInfo_TypeDef;

reg8 CRC8_0(unsigned char* Data, reg16 Size);
reg16 CRC16_0(unsigned char* Data, reg16 Size);
reg32 CRC32_0(unsigned char* Data, reg16 Size);

reg8 CRC8_1(const CRCInfo_TypeDef __code* CRCInfo, unsigned char* Data, reg16 Size);
reg16 CRC16_1(const CRCInfo_TypeDef __code* CRCInfo, unsigned char* Data, reg16 Size);
reg32 CRC32_1(const CRCInfo_TypeDef __code* CRCInfo, unsigned char* Data, reg16 Size);

#endif