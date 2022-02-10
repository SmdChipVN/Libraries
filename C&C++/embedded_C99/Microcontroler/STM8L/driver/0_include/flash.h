#ifndef _FLASH_H_
#define _FLASH_H_

#define EEPROM_WriteByte(Address,Data)  *((unsigned char*)(EEPROM_BASE_ADDRESS+Address))=Data
#define FLASH_WriteByte(Address,Data)   *((unsigned char*)(FLASH_BASE_ADDRESS+Address))=Data
#define EEPROM_ReadByte(Address)        (*((unsigned char*)(EEPROM_BASE_ADDRESS+Address)))
#define FLASH_ReadByte(Address)         (*((unsigned char*)(FLASH_BASE_ADDRESS+Address)))
#define Flash_Lock()                    FLASH.IAPSR.BITS.PUL=0
#define EEPROM_Lock()                   FLASH.IAPSR.BITS.DUL=0
void EEPROM_Unlock();
void FLASH_Unlock();
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  BUNION(CR1, unsigned char,     //0x0           0x00            Flash control register 1
    FIX                 , 1,    //0             0               Fixed Byte programming time
    IE                  , 1,    //1             0               Flash Interrupt enable
    WAITM               , 1,    //2             0               Flash program and data EEPROM IDDQ mode during wait mode
    EEPM                , 1,    //3             0               Flash program and data EEPROM IDDQ mode selection during run, low power run and low power wait mode
    _Reserved           , 4);
  BUNION(CR2, unsigned char,     //0x1           0x00            Flash control register 2
    PRG                 , 1,    //0             0               Standard block programming
    _Reserved           , 3,
    FPRG                , 1,    //4             0               Fast block programming
    ERASE               , 1,    //5             0               Block erasing
    WPRG                , 1,    //6             0               Word programming
    OPT                 , 1);   //7             0               Write option bytes
  unsigned char PUKR;           //0x2           0x00            Flash program memory unprotecting key register
  unsigned char DUKR;           //0x3           0x00            Data EEPROM unprotection key register
  BUNION(IAPSR, unsigned char,   //0x4           0x40            Flash status register
    WR_PG_DIS           , 1,    //0             0               Write attempted to protected page flag
    PUL                 , 1,    //1             0               Flash Program memory unlocked flag
    EOP                 , 1,    //2             0               End of programming (write or erase operation) flag
    DUL                 , 1,    //3             0               Data EEPROM area unlocked flag
    _Reserved           , 2,
    const HVOFF         , 1,    //6             1               End of high voltage flag
    _Reserved1          , 1);
} FLASH_TypeDef;
extern __no_init volatile FLASH_TypeDef FLASH;

#endif