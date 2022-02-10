/*
MODE 0:
  +) Config:
      #define FLASHIC_CONFIG_CS_0(IsSet)                              CS_PIN = IsSet
      #define FLASHIC_SPI_WRITE_BYTE_0(Data)                          SPI_WriteByte(Data)       //return Data
      #define FLASHIC_SPI_WAIT_0()                                    while (SPI.Busy)
      #define FLASHIC_WRITE_ENABLE_TIME_OUT_0(Stage)                  false     //reg8 FlashIC_CheckWriteEnableTimeout(reg8 Stage = 1: begin, 2: end, 0: check), return 1 to timeout
                                                                                //or false to disable (maybe infinity loop)
      #define FLASHIC_SPI_DMA_RX(RXBuffer, Size, EndFunction)         SPI_RX_DMA_WithInterrupt(RXBuffer, Size, EndFunction)     //void (*EndFunction)()
      #define FLASHIC_SPI_DMA_TX(Data, Size, EndFunction)             SPI_TX_DMA_WithInterrupt(Data, Size, EndFunction)
  +) Declare:
       __no_init FlashIC_TypeDef FlashIC;
  +) Using:
      reg8 FlashIC_GetInfo_0();                                                                       //return 0: failed, else return manufacture id
      BASE_STATUS FlashIC_Read_0(unsigned char* RXBuffer, reg32 Address, reg16 Size);
      BASE_STATUS FlashIC_ReadDMA_0(unsigned char* RXBuffer, reg32 Address, reg16 Size);
      BASE_STATUS FlashIC_EraseMass_0();                                                              //after erase mass, any action need to check wait busy flag
      reg8 FlashIC_IsBusy_0();
      BASE_STATUS FlashIC_EraseSector_0(reg32 SectorAddress);                                         //should need to check wait busy flag
      BASE_STATUS FlashIC_Write_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size);       //should need to check wait busy flag, maximum Size base Address and FlashIC.Size.Program
      BASE_STATUS FlashIC_WriteDMA_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size);    //should need to check wait busy flag, maximum Size base Address and FlashIC.Size.Program
*/
#ifndef _FLASH_IC_H_
#define _FLASH_IC_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  unsigned char BusBusy;
  struct
  {
    unsigned char Memory;
    unsigned char Sector;
    unsigned char Program;
  } Size;
  struct
  {
    /*make sure same code
    unsigned char WriteEnable   = 0x06;
    unsigned char ReadSR1       = 0x05;
    unsigned char EraseMass     = 0xC7;
    unsigned char PowerDown     = 0xB9;
    unsigned char ReadUID       = 0x4B;         //                              4xDummy, UID63-UID0
    */
    unsigned char EraseSector;                  //                              3/4 bytes Address; usually 4KB
    unsigned char EraseBlock;                   //                              3/4 bytes Address; usually 64KB
    unsigned char PageProgram;                  //                              3/4 bytes Address; usually 256 bytes    
    unsigned char ReadData;
  } Instruction;
} FlashIC_TypeDef;
//==============================================================================================================================================================
reg8 FlashIC_GetInfo_0();                                                                       //return 0: failed, else return manufacture id
BASE_STATUS FlashIC_Read_0(unsigned char* RXBuffer, reg32 Address, reg16 Size);
BASE_STATUS FlashIC_ReadDMA_0(unsigned char* RXBuffer, reg32 Address, reg16 Size);
BASE_STATUS FlashIC_EraseMass_0();                                                              //after erase mass, any action need to check wait busy flag
reg8 FlashIC_IsBusy_0();
BASE_STATUS FlashIC_EraseSector_0(reg32 SectorAddress);                                         //should need to check wait busy flag
BASE_STATUS FlashIC_Write_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size);       //should need to check wait busy flag, maximum Size base Address and FlashIC.Size.Program
BASE_STATUS FlashIC_WriteDMA_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size);    //should need to check wait busy flag, maximum Size base Address and FlashIC.Size.Program
//==============================================================================================================================================================
typedef struct
{
  void (*ConfigCS)(reg8 IsSet);
  reg8 (*SPI_WriteByte)(reg8 Data);
  void (*SPI_WriteDMA)(const unsigned char* Data, unsigned int Size);
  void (*SPI_Wait)();
  unsigned char (*WaitWriteEnable)();   //return 0: wait, else time out
} FlashICFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char FlashIC_GetInfo_1(const FlashICFunction_TypeDef* FlashICFunction);
void FlashIC_Read_1(const FlashICFunction_TypeDef* FlashICFunction, unsigned char *RXBuffer, unsigned int Address, unsigned int Size);
void FlashIC_EraseMass_1(const FlashICFunction_TypeDef* FlashICFunction);
unsigned char FlashIC_IsBusy_1(const FlashICFunction_TypeDef* FlashICFunction);
void FlashIC_EraseSector_1(const FlashICFunction_TypeDef* FlashICFunction, unsigned int SectorAddress);
void FlashIC_Write_1(const FlashICFunction_TypeDef* FlashICFunction, const unsigned char* Data, unsigned int Address, unsigned int Size);

#endif