#ifndef _FLASH_H_
#define _FLASH_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(ACR, unsigned int,                     //              0x0000'0030     Flash access control register
    LATENCY                             , 3,    //0:2           0               Latency
    HLFCYA                              , 1,    //3             0               Flash half cycle access enable
    PRFTBE                              , 1,    //4             1               Prefetch buffer enable
    const PRFTBS                        , 1,    //5             1               Prefetch buffer status
    _Reserved                           , 26);
  unsigned int KEYR;                            //              --              FPEC key register
  unsigned int OPTKEYR;                         //              --              Flash OPTKEY register
  BUNION(SR, unsigned int,                      //              0x0000'0000     Flash status register
        const BSY                       , 1,    //0             0               Busy
        _Reserved                       , 1,
        PGERR                           , 1,    //2             0               Programming error
        _Reserved1                      , 1,
        WRPRTERR                        , 1,    //4             0               Write protection error
        EOP                             , 1,    //5             0               End of operation
        _Reserved2                      , 26);
  BUNION(CR, unsigned int,                      //              0x0000'0080     Flash control register
        PG                              , 1,    //0             0               Programming
        PER                             , 1,    //1             0               Page erase
        MER                             , 1,    //2             0               Mass erase
        _Reserved                       , 1,
        OPTPG                           , 1,    //4             0               Option byte programming
        OPTER                           , 1,    //5             0               Option byte erase
        STRT                            , 1,    //6             0               Start
        LOCK                            , 1,    //7             1               Lock
        _Reserved1                      , 1,
        OPTWRE                          , 1,    //9             0               Option bytes write enable
        ERRIE                           , 1,    //10            0               Error interrupt enable
        _Reserved2                      , 1,
        EOPIE                           , 1,    //12            0               End of operation interrupt enable
        _Reserved3                      , 19);
  unsigned int AR;                              //              0x0000'0000     Flash address register
  unsigned int _Reserved;
  BUNION(OBR, unsigned int const,               //              0x03FF'FFFC     Option byte register
        OPTERR                          , 1,    //0             0               Option byte error
        RDPRT                           , 1,    //1             0               Read protection
        WDG_SW                          , 1,    //2
        nRST_STOP                       , 1,    //3
        nRST_STDBY                      , 1,    //4
        _Reserved                       , 5,
        DATA0                           , 8,    //10:17
        DATA1                           , 8,    //18:25
        Reserved                        , 6);
  unsigned int const WRPR;                      //              0xFFFF.FFFF     Write protection register
} FLASH_TypeDef;

typedef struct
{
  RSTRUCT(ACR, unsigned int,                    //              0x0000'0030     Flash access control register
        LATENCY                         [3],    //0:2           0               Latency
        HLFCYA                             ,    //3             0               Flash half cycle access enable
        PRFTBE                             ,    //4             1               Prefetch buffer enable
        const PRFTBS                       ,    //5             1               Prefetch buffer status
        _Reserved                       [26]);  
  unsigned int KEYR[32];                        //              --              FPEC key register
  unsigned int OPTKEYR[32];                     //              --              Flash OPTKEY register
  RSTRUCT(SR, unsigned int,                     //              0x0000'0000     Flash status register
        const BSY                          ,    //0             0               Busy
        _Reserved                          ,    
        PGERR                              ,    //2             0               Programming error
        _Reserved1                         ,    
        WRPRTERR                           ,    //4             0               Write protection error
        EOP                                ,    //5             0               End of operation
        _Reserved2                      [26]);  
  RSTRUCT(CR, unsigned int,                     //              0x0000'0080     Flash control register
        PG                                 ,    //0             0               Programming
        PER                                ,    //1             0               Page erase
        MER                                ,    //2             0               Mass erase
        _Reserved                          ,    
        OPTPG                              ,    //4             0               Option byte programming
        OPTER                              ,    //5             0               Option byte erase
        STRT                               ,    //6             0               Start
        LOCK                               ,    //7             1               Lock
        _Reserved1                         ,    
        OPTWRE                             ,    //9             0               Option bytes write enable
        ERRIE                              ,    //10            0               Error interrupt enable
        _Reserved2                         ,    
        EOPIE                              ,    //12            0               End of operation interrupt enable
        _Reserved3                      [19]);  
  unsigned int AR[32];                          //              0x0000'0000     Flash address register
  unsigned int _Reserved[32];                   
  RSTRUCT(OBR, unsigned int const,              //              0x03FF'FFFC     Option byte register
        OPTERR                             ,    //0             0               Option byte error
        RDPRT                              ,    //1             0               Read protection
        WDG_SW                             ,    //2
        nRST_STOP                          ,    //3
        nRST_STDBY                         ,    //4
        _Reserved                       [5],    
        DATA0                           [8],    //10:17
        DATA1                           [8],    //18:25
        Reserved                        [6]);   
  unsigned int const WRPR[32];                  //              0xFFFF.FFFF     Write protection register
} FLASH_BITBAND_TypeDef;
//==============================================================================================================================================================
//===========================================================       LEVEL 1      ===============================================================================
//==============================================================================================================================================================
void Flash_Lock(volatile FLASH_TypeDef* FLASH);
void Flash_Unlock(volatile FLASH_TypeDef* FLASH);
void Flash_WriteShort(volatile FLASH_TypeDef* FLASH, unsigned int Address, unsigned int Data);
void Flash_WriteShorts(volatile FLASH_TypeDef* FLASH, unsigned int Address, unsigned short *Data, unsigned int Length);
void Flash_Erase(volatile FLASH_TypeDef* FLASH, unsigned int Address);          //1024 byte

#endif