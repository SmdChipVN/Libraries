#include <crc.h>
#include <config.h>
//==============================================================================================================================================================
reg8 CRC8_0(unsigned char* Data, reg16 Size)
{
#ifdef CRC8_PRESET
  reg8 Preset = CRC8_PRESET;
  while (Size--)
  {
    reg8 i;
#if (CRC8_REVERSE_IN > 0)
    Preset ^= ReverseByte[*Data++];
#else
    Preset ^= *Data++;
#endif
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRC8_POLYNOMIAL) : (Preset >> 1);
  }
#if (CRC8_REVERSE_OUT > 0)
  Preset = ReverseByte[Preset & 0xFF];
#endif
#if (CRC8_XOR_OUT > 0)
  Preset ^= CRC8_XOR_OUT;
#endif
  return Preset;
#endif
}
//==============================================================================================================================================================
reg16 CRC16_0(unsigned char* Data, reg16 Size)
{
#ifdef CRC16_PRESET
  reg16 Preset = CRC16_PRESET;
  while (Size--)
  {
    reg8 i;
#if (CRC16_REVERSE_IN > 0)
    Preset ^= ReverseByte[*Data++];
#else
    Preset ^= *Data++;
#endif
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRC16_POLYNOMIAL) : (Preset >> 1);
  }
#if (CRC16_REVERSE_OUT > 0)
  {
    reg8 temp = ((unsigned char*)&Preset)[0];
    ((unsigned char*)&Preset)[0] = ReverseByte[((unsigned char*)&Preset)[1]];
    ((unsigned char*)&Preset)[1] = ReverseByte[temp];
  }
#endif
#if (CRC16_XOR_OUT > 0)
  Preset ^= CRC16_XOR_OUT;
#endif
  return Preset;
#endif
}
//==============================================================================================================================================================
reg32 CRC32_0(unsigned char* Data, reg16 Size)
{
#ifdef CRC32_PRESET
  reg32 Preset = CRC32_PRESET;
  while (Size--)
  {
    reg8 i;
#if (CRC32_REVERSE_IN > 0)
    Preset ^= ReverseByte[*Data++];
#else
    Preset ^= *Data++;
#endif
    for (i = 0; i < 8; i++)
      Preset = (Preset & 0x01) ? ((Preset >> 1) ^ CRC32_POLYNOMIAL) : (Preset >> 1);
  }
#if (CRC32_REVERSE_OUT > 0)
  {
    reg8 temp = ((unsigned char*)&Preset)[0];
    ((unsigned char*)&Preset)[0] = ReverseByte[((unsigned char*)&Preset)[3]];
    ((unsigned char*)&Preset)[3] = ReverseByte[temp];
    temp = ((unsigned char*)&Preset)[1];
    ((unsigned char*)&Preset)[1] = ReverseByte[((unsigned char*)&Preset)[2]];
    ((unsigned char*)&Preset)[2] = ReverseByte[temp];
  }
#endif
#if (CRC32_XOR_OUT > 0)
  Preset ^= CRC32_XOR_OUT;
#endif
  return Preset;
#endif
}