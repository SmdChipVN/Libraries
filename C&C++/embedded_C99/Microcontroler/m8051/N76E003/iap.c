#include <n76e003.h>

static void IAP_Start()
{
  unsigned char backup = IE.BITS.EA;
  IE.BITS.EA = 0;
  TA = 0xAA;
  TA = 0x55;
  IAPTRG.BITS.IAPGO = 1;
  IE.BITS.EA = backup;
}

void IAP_AP_ErasePage(unsigned short Address)
{
  IAPFD = 0xFF;
  IAPCN.REG = 0x22;
  IAPAH = Address >> 8;
  IAPAL = Address;
  IAP_Start();
}

void IAP_Init()
{
  TA = 0xAA;
  TA = 0x55;
  CHPCON.BITS.IAPEN = 1;
  TA = 0xAA;
  TA = 0x55;
  IAPUEN.REG = 0x07;
}

unsigned char IAP_AP_ReadByte(unsigned short Address)
{
  IAPAL = Address;
  IAPAH = Address >> 8;
  IAPCN.REG = 0x00;
  IAP_Start();
  return IAPFD;
}

void IAP_AP_WriteByte(unsigned short Address, unsigned char Value)
{
  IAPFD = Value;
  IAPAL = Address;
  IAPAH = Address >> 8;
  IAPCN.REG = 0x21;
  IAP_Start();
}