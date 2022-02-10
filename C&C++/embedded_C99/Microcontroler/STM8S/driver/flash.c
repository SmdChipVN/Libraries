#include <flash.h>

extern __no_init volatile FLASH_TypeDef FLASH;

#define KEY_1           0x56
#define KEY_2           0xAE

void EEPROM_Unlock()
{
  while (!FLASH.IAPSR.BITS.DUL)
  {
    FLASH.DUKR = KEY_2;
    FLASH.DUKR = KEY_1;
  }
}

void FLASH_Unlock()
{
  while (!FLASH.IAPSR.BITS.PUL)
  {
    FLASH.PUKR = KEY_1;
    FLASH.PUKR = KEY_2;
  }
}