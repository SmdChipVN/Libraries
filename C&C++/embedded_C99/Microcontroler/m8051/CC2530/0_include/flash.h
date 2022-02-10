#ifndef _FLASH_H_
#define _FLASH_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(FCTL, unsigned char,                   //              0x04            Flash Control
    ERASE                               , 1,    //0             0               Page erase
    WRITE                               , 1,    //1             0               Write. Start writing word at location given by FADDRH:FADDRL.
    CM                                  , 2,    //2-3           1               Cache mode
                                                //                                      0: Cache disabled
                                                //                                      1: Cache enabled
                                                //                                      2: Cache enabled, prefetch mode
                                                //                                      3: Cache enabled, real-time mode
    const _reserved                     , 1,
    ABORT                               , 1,    //5             0               Abort status
    FULL                                , 1,    //6             0               Buffer-full status
    const BUSY                          , 1);   //7             0               Indicates that write or erase is in operation
  RUNION_16x8(FADDR, , LOW, HIGH);              //              0x0000          Flash-Address
  unsigned char FWDATA;                         //              0               Flash Write Data
} FLASH_TypeDef;

#endif