#include <crc.h>
//==============================================================================================================================================================
reg8 CRC8_1(CRCInfo_TypeDef __gptr* CRCInfo, unsigned char* Data, reg16 Size)
{
  reg8 Preset = CRCInfo->CRC8.Preset;
  while (Size--)
  {
    reg8 i;
    if (CRCInfo->ReverseIn)
      Preset ^= ReverseByte[*Data++];
    else
      Preset ^= *Data++;
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRCInfo->CRC8.Polyminoal) : (Preset >> 1);
  }
  if (CRCInfo->ReverseOut)
    Preset = ReverseByte[Preset];
  Preset ^= CRCInfo->CRC8.XorOut;
  return Preset;
}
//==============================================================================================================================================================
reg16 CRC16_1(CRCInfo_TypeDef __gptr* CRCInfo, unsigned char* Data, reg16 Size)
{
  reg16 Preset = CRCInfo->CRC16.Preset;
  while (Size--)
  {
    reg8 i;
    if (CRCInfo->ReverseIn)
      Preset ^= ReverseByte[*Data++];
    else
      Preset ^= *Data++;
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRCInfo->CRC16.Polyminoal) : (Preset >> 1);
  }
  if (CRCInfo->ReverseOut)
  {
    reg8 temp = ((unsigned char*)&Preset)[0];
    ((unsigned char*)&Preset)[0] = ReverseByte[((unsigned char*)&Preset)[1]];
    ((unsigned char*)&Preset)[1] = ReverseByte[temp];
  }
  Preset ^= CRCInfo->CRC16.XorOut;
  return Preset;
}
//==============================================================================================================================================================
reg32 CRC32_1(CRCInfo_TypeDef __gptr* CRCInfo, unsigned char* Data, reg16 Size)
{
  reg32 Preset = CRCInfo->CRC32.Preset;
  while (Size--)
  {
    reg8 i;
    if (CRCInfo->ReverseIn > 0)
      Preset ^= ReverseByte[*Data++];
    else
      Preset ^= *Data++;
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRCInfo->CRC32.Polyminoal) : (Preset >> 1);
  }
  if (CRCInfo->ReverseOut > 0)
  {
    reg8 temp = ((unsigned char*)&Preset)[0];
    ((unsigned char*)&Preset)[0] = ReverseByte[((unsigned char*)&Preset)[3]];
    ((unsigned char*)&Preset)[3] = ReverseByte[temp];
    temp = ((unsigned char*)&Preset)[1];
    ((unsigned char*)&Preset)[1] = ReverseByte[((unsigned char*)&Preset)[2]];
    ((unsigned char*)&Preset)[2] = ReverseByte[temp];
  }
  Preset ^= CRCInfo->CRC32.XorOut;
  return Preset;
}