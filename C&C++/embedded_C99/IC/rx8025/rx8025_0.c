#include <rx8025.h>
#include <soft_i2c.h>

#define RX8025_ADDRESS    0x32

static unsigned int _BinToDec(unsigned int Value)
{
  return (Value >> 4) * 10 + (Value & 0x0F);
}
static unsigned int _DecToBin(unsigned int Value)
{
  return ((Value / 10) << 4) | (Value % 10);
}

bool RX8025_Init()
{
  static const unsigned char config[] = {0x20, 0xA0};
  return SI2C_WriteBytes(RX8025_ADDRESS, 0xE0, config, 2);
}
bool RX8025_Read(DateTime_TypeDef* DateTime)
{
  unsigned char buff[8];
  if (SI2C_ReadBytes(RX8025_ADDRESS, 0, buff, 8))
  {
    DateTime->Second      = _BinToDec(buff[1]);
    DateTime->Minute      = _BinToDec(buff[2]);
    DateTime->Hour        = _BinToDec(buff[3]);
    DateTime->WeekDay     = _BinToDec(buff[4]);
    DateTime->Day         = _BinToDec(buff[5]);
    DateTime->Month       = _BinToDec(buff[6]);
    DateTime->Year        = _BinToDec(buff[7]);
    return true;
  }
  return false;
}

bool RX8025_Save(DateTime_TypeDef* DateTime)
{
  unsigned char buff[7];
  buff[0]       = _DecToBin(DateTime->Second );
  buff[1]       = _DecToBin(DateTime->Minute );
  buff[2]       = _DecToBin(DateTime->Hour   );
  buff[3]       = _DecToBin(DateTime->WeekDay);
  buff[4]       = _DecToBin(DateTime->Day    );
  buff[5]       = _DecToBin(DateTime->Month  );
  buff[6]       = _DecToBin(DateTime->Year   );
  if (SI2C_WriteBytes(RX8025_ADDRESS, 0, buff, 7))
    return true;
  return false;
}