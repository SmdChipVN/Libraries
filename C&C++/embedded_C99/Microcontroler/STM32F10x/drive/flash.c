#include <flash.h>
#include <bitband.h>

void Flash_Lock(volatile FLASH_TypeDef* FLASH)
{
  FLASH_BITBAND_TypeDef* FLASH_BITBAND = (FLASH_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)FLASH, 0);
  while (FLASH_BITBAND->SR.BSY);
  FLASH_BITBAND->CR.PG = 0;
  FLASH_BITBAND->CR.LOCK = 1;
}
void Flash_Unlock(volatile FLASH_TypeDef* FLASH)
{
  FLASH_BITBAND_TypeDef* FLASH_BITBAND = (FLASH_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)FLASH, 0);
  do
  {
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
  } while (FLASH_BITBAND->CR.LOCK);
  FLASH_BITBAND->CR.PG = 1;
}

void Flash_WriteShort(volatile FLASH_TypeDef* FLASH, unsigned int Address, unsigned int Data)
{
  FLASH_BITBAND_TypeDef* FLASH_BITBAND = (FLASH_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)FLASH, 0);
  *((unsigned short*)Address) = Data;
  while(!FLASH_BITBAND->SR.EOP);
  FLASH_BITBAND->SR.EOP = 1;
}

void Flash_WriteShorts(volatile FLASH_TypeDef* FLASH, unsigned int Address, unsigned short *Data, unsigned int Length)
{  
  FLASH_BITBAND_TypeDef* FLASH_BITBAND = (FLASH_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)FLASH, 0);
  while (Length--)
  {
    *((unsigned short*)Address) = *Data++;
    while(!FLASH_BITBAND->SR.EOP);
    FLASH_BITBAND->SR.EOP = 1;
    Address += 2;
  }
  while (FLASH_BITBAND->SR.BSY);
}

void Flash_Erase(volatile FLASH_TypeDef* FLASH, unsigned int Address)
{
  FLASH_BITBAND_TypeDef* FLASH_BITBAND = (FLASH_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)FLASH, 0);
  FLASH_BITBAND->CR.PG = 0;
  FLASH_BITBAND->CR.PER = 1;
  FLASH->AR = Address;
  FLASH_BITBAND->CR.STRT = 1;
  while (FLASH_BITBAND->SR.BSY);
  FLASH_BITBAND->SR.EOP = 1;
  FLASH_BITBAND->CR.PER = 0;
  FLASH_BITBAND->CR.PG = 1;
}