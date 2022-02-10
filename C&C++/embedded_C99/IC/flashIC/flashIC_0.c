#include <flashIC.h>
#include <config.h>

#define COMMAND_JEDEC_ID        0x9F            //MF7-MF0, ID15-ID8, ID7-ID0
#define WRITE_ENABLE            0x06
#define READ_SR1                0x05
#define ERASE_MASS              0xC7
#define POWER_DOWN              0xB9
#define READ_UID                0x4B            //4xDummy, UID63-UID0
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef
BUNION(FlashIC_SR1_TypeDef, unsigned char,      //                              Status Registers
  BUSY                                  , 1,    //0                             Erase/Write In Progress
  WEL                                   , 1,    //1                             Write Enable Latch
  BP                                    , 3,    //2:4                           Block Protect Bits
  TB                                    , 1,    //5                             Top/Bottom Block Protect
  SEC                                   , 1,    //6                             Sector/Block Protect Bit
  SRP0                                  , 1);   //7                             Status Register Protect
static const unsigned char __code Instruction[3][4] = {
  //EraseSector         EraseBlock      PageProgram     ReadData
  {0x20,                0xD8,           0x02,           0x03},  //WINBOND, EON, ESMT, CYPRESS_ADDR_3BYTE, 
  {0x21,                0xDC,           0x12,           0x13},  //CYPRESS_ADDR_4BYTE
  {0xD8,                0xD8,           0x02,           0x03},  //SPANISION
};
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
extern __no_init FlashIC_TypeDef FlashIC;
reg8 FlashIC_GetInfo_0()
{
  typedef enum
  {
    MANUFACTURER_ID_WINBOND             = 0xEF,
    MANUFACTURER_ID_EON                 = 0x1C,
    MANUFACTURER_ID_ESMT                = 0x8C,
    MANUFACTURER_ID_CYPRESS             = 0x01,
    MANUFACTURER_ID_CYPRESS_4BYTE       = 0x41,
    MANUFACTURER_ID_SPANISION           = 0x01,
  } MANUFACTURER_ID;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  reg8 ins_id, memory_type, memory_size, manufacture;
  FLASHIC_CONFIG_CS_0(0);
  FLASHIC_SPI_WRITE_BYTE_0(COMMAND_JEDEC_ID);
  manufacture = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
  memory_type = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
  FlashIC.Size.Memory = memory_size = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
  FlashIC.BusBusy = 0;
  FLASHIC_SPI_WAIT_0();
  FLASHIC_CONFIG_CS_0(1);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------  
  switch (manufacture)
  {
    case MANUFACTURER_ID_WINBOND:
    case MANUFACTURER_ID_EON:
    case MANUFACTURER_ID_ESMT:
      ins_id = 0;
      break;
    case MANUFACTURER_ID_SPANISION:     //MANUFACTURER_ID same as CYPRESS
      if (memory_type == 0x02)
        ins_id = 2;
      else if (memory_size > 24)        //CYPRESS: if memory size larger than (1 << 24 (3 bytes addresable)) bytes
      {
        manufacture = MANUFACTURER_ID_CYPRESS_4BYTE;
        ins_id = 1;
      }
      break;
    default:
      ins_id = 255;
  }
  if (ins_id != 255)
  {
    reg8 i;
    for (i = 0; i < sizeof(Instruction[0]); i++)
      ((unsigned char*)&FlashIC.Instruction)[i] = Instruction[ins_id][i];
    FlashIC.Size.Sector = 12;           //(1 << 12) bytes
    FlashIC.Size.Program = 8;           //(1 << 8) bytes
    return manufacture;
  }
  return 0;
}
//==============================================================================================================================================================
static void WriteAddress(reg32 Address)
{
  if (FlashIC.Size.Memory > 24)
    FLASHIC_SPI_WRITE_BYTE_0(Address >> 24);
  FLASHIC_SPI_WRITE_BYTE_0(Address >> 16);
  FLASHIC_SPI_WRITE_BYTE_0(Address >> 8);
  FLASHIC_SPI_WRITE_BYTE_0(Address);
}
//==============================================================================================================================================================
static void EndProcess()
{
  FLASHIC_SPI_WAIT_0();
  FLASHIC_CONFIG_CS_0(1);
  FlashIC.BusBusy = 0;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_Read_0(unsigned char *RXBuffer, reg32 Address, reg16 Size)
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  FLASHIC_CONFIG_CS_0(0);
  FLASHIC_SPI_WRITE_BYTE_0(FlashIC.Instruction.ReadData);
  WriteAddress(Address);
  for (reg16 i = 0; i < Size; i++)
    RXBuffer[i] = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
  EndProcess();
  return BASE_STATUS_DONE;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_ReadDMA_0(unsigned char *RXBuffer, reg32 Address, reg16 Size)
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  FLASHIC_CONFIG_CS_0(0);
  FLASHIC_SPI_WRITE_BYTE_0(FlashIC.Instruction.ReadData);
  WriteAddress(Address);
  FLASHIC_SPI_DMA_RX(RXBuffer, Size, EndProcess);
  return BASE_STATUS_DONE;
}
//==============================================================================================================================================================
static reg8 WriteEnable()
{
  FlashIC_SR1_TypeDef sr1;
  FLASHIC_CONFIG_CS_0(0);
  FLASHIC_SPI_WRITE_BYTE_0(WRITE_ENABLE);
  FLASHIC_SPI_WAIT_0();
  FLASHIC_CONFIG_CS_0(1);
  FLASHIC_WRITE_ENABLE_TIME_OUT_0(1);
  do
  {
    if (FLASHIC_WRITE_ENABLE_TIME_OUT_0(0))
      return 0;
    FLASHIC_CONFIG_CS_0(0);
    FLASHIC_SPI_WRITE_BYTE_0(READ_SR1);
    sr1.REG = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
    FLASHIC_SPI_WAIT_0();
    FLASHIC_CONFIG_CS_0(1);
  } while (!sr1.BITS.WEL);
  FLASHIC_WRITE_ENABLE_TIME_OUT_0(2);
  return 1;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_EraseMass_0()
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  if (WriteEnable())
  {
    FLASHIC_CONFIG_CS_0(0);
    FLASHIC_SPI_WRITE_BYTE_0(ERASE_MASS);
    EndProcess();
    return BASE_STATUS_DONE;
  }
  return BASE_STATUS_FAILED;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_EraseSector_0(reg32 SectorAddress)
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  if (WriteEnable())
  {
    FLASHIC_CONFIG_CS_0(0);
    FLASHIC_SPI_WRITE_BYTE_0(FlashIC.Instruction.EraseSector);
    WriteAddress(SectorAddress);
    EndProcess();
    return BASE_STATUS_DONE;
  }
  return BASE_STATUS_FAILED;
}
//==============================================================================================================================================================
reg8 FlashIC_IsBusy_0()
{
  if (FlashIC.BusBusy)
    return 1;
  FlashIC.BusBusy = 1;
  FlashIC_SR1_TypeDef sr1;
  FLASHIC_CONFIG_CS_0(0);
  FLASHIC_SPI_WRITE_BYTE_0(READ_SR1);
  sr1.REG = FLASHIC_SPI_WRITE_BYTE_0(0xFF);
  EndProcess();
  return sr1.BITS.BUSY;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_Write_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size)
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  if (WriteEnable())
  {
    FLASHIC_CONFIG_CS_0(0);
    FLASHIC_SPI_WRITE_BYTE_0(FlashIC.Instruction.PageProgram);
    WriteAddress(Address);
    for (reg16 i = 0; i < Size; i++)
      FLASHIC_SPI_WRITE_BYTE_0(Data[i]);
    EndProcess();
    return BASE_STATUS_DONE;
  }
  return BASE_STATUS_FAILED;
}
//==============================================================================================================================================================
BASE_STATUS FlashIC_WriteDMA_0(const unsigned char __gptr* Data, reg32 Address, reg16 Size)
{
  if (FlashIC.BusBusy)
    return BASE_STATUS_BUSY;
  FlashIC.BusBusy = 1;
  if (WriteEnable())
  {
    FLASHIC_CONFIG_CS_0(0);
    FLASHIC_SPI_WRITE_BYTE_0(FlashIC.Instruction.PageProgram);
    WriteAddress(Address);
    FLASHIC_SPI_DMA_TX((void volatile*)Data, Size, EndProcess);
    return BASE_STATUS_DONE;
  }
  return BASE_STATUS_FAILED;
}