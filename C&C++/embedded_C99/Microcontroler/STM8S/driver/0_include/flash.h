#ifndef _FLASH_H_
#define _FLASH_H_

#define EEPROM_WriteByte(Address,Data)  *((unsigned char*)(Address))=Data
#define FLASH_WriteByte(Address,Data)   *((unsigned char*)(Address))=Data
#define EEPROM_ReadByte(Address)        (*((unsigned char*)(Address)))
#define FLASH_ReadByte(Address)         (*((unsigned char*)(Address)))
#define FLASH_Lock()                    FLASH.IAPSR.BITS.PUL=0
#define EEPROM_Lock()                   FLASH.IAPSR.BITS.DUL=0
void EEPROM_Unlock();
void FLASH_Unlock();
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned char,                    //              0x00            Flash control register 1
    FIX                                 , 1,    //0             0               Fixed Byte programming time
    IE                                  , 1,    //1             0               Flash Interrupt enable
    AHALT                               , 1,    //2             0               Power-down in Active-halt mode
    HALT                                , 1,    //3             0               Power-down in Halt mode
    _reserved                           , 4);
  BUNION(CR2, unsigned char,                    //              0x00            Flash control register 2
    PRG                                 , 1,    //0             0               Standard block programming
    _reserved                           , 3,
    FPRG                                , 1,    //4             0               Fast block programming
    ERASE                               , 1,    //5             0               Block erasing
    WPRG                                , 1,    //6             0               Word programming
    OPT                                 , 1);   //7             0               Write option bytes
  BUNION(NCR2, unsigned char,                   //              0xFF            Revert of CR2
    NPRG                                , 1,
    _reserved                           , 3,
    NFPRG                               , 1,
    NERASE                              , 1,
    NWPRG                               , 1,
    NOPT                                , 1);
  unsigned char const FPR;                      //              0x00            Flash protection register (6 BIT low)
  unsigned char const NFPR;                     //              0xFF            Revert of FPR
  BUNION(IAPSR, unsigned char,                  //              0x40            Flash status register
    const WR_PG_DIS                     , 1,    //0             0               Write attempted to protected page flag
    PUL                                 , 1,    //1             0               Flash Program memory unlocked flag
    const EOP                           , 1,    //2             0               End of programming (write or erase operation) flag
    DUL                                 , 1,    //3             0               Data EEPROM area unlocked flag
    _reserved                           , 2,
    const HVOFF                         , 1,    //6             1               End of high voltage flag
    _reserved1                          , 1);
  unsigned char _reserved[2];
  unsigned char PUKR;                           //              0x00            Flash program memory unprotecting key: write 0x56 -> 0xAE
  unsigned char _reserved1;
  unsigned char DUKR;                           //              0x00            Data EEPROM unprotection key: write 0xAE -> 0x56
} FLASH_TypeDef;

#endif