//#include <flashIC.h>
////==============================================================================================================================================================
//#define __config_cs(IsSet)                      FlashICFunction->ConfigCS(IsSet)
//#define __spi_writebyte(Data)                   FlashICFunction->SPI_WriteByte(Data)
//#define __spi_writeDMA(Data, Length)            FlashICFunction->SPI_WriteDMA(Data, Length)
//#define __spi_wait()                            FlashICFunction->SPI_Wait()
//
//extern __no_init FlashIC_TypeDef FlashIC;
////==============================================================================================================================================================
//#define COMMAND_JEDEC_ID        0x9F            //MF7-MF0, ID15-ID8, ID7-ID0
//
//#define WRITE_ENABLE            0x06
//#define READ_SR1                0x05
//#define ERASE_MASS              0xC7
//#define POWER_DOWN              0xB9
//#define READ_UID                0x4B            //4xDummy, UID63-UID0
//
//typedef union
//{
//  unsigned char REG;
//  struct
//  {
//    unsigned char BUSY  : 1;                    //Erase/Write In Progress
//    unsigned char WEL   : 1;                    //Write Enable Latch
//    unsigned char BP    : 3;                    //Block Protect Bits
//    unsigned char TB    : 1;                    //Top/Bottom Block Protect
//    unsigned char SEC   : 1;                    //Sector/Block Protect Bit
//    unsigned char SRP0  : 1;                    //Status Register Protect
//  } BITS;
//} FlashIC_SR1_TypeDef;                          //Status Registers
//
//static const struct
//{
//  unsigned char EraseSector;
//  unsigned char EraseBlock;
//  unsigned char PageProgram;
//  unsigned char ReadData;
//} code[3] = {
//  //EraseSector         EraseBlock      PageProgram     ReadData
//  {0x20,                0xD8,           0x02,           0x03},  //WINBOND, EON, ESMT, CYPRESS_ADDR_3BYTE, 
//  {0x21,                0xDC,           0x12,           0x13},  //CYPRESS_ADDR_4BYTE
//  {0xD8,                0xD8,           0x02,           0x03},  //SPANISION
//};
//static void store(unsigned char code_index)
//{
//  FlashIC.Code.EraseSector = code[code_index].EraseSector;
//  FlashIC.Code.EraseBlock = code[code_index].EraseBlock;
//  FlashIC.Code.PageProgram = code[code_index].PageProgram;
//  FlashIC.Code.ReadData = code[code_index].ReadData;
//}
//unsigned char FlashIC_GetInfo_0x01(const FlashICFunction_TypeDef* FlashICFunction)
//{
//  FlashIC.Size.Sector = 12;     //(1 << 12) bytes
//  FlashIC.Size.Program = 8;     //(1 << 8) bytes
//  store(0);
//  //=====================================================
//  unsigned char manufacture_id, memory_type, memory_size;
//  __config_cs(0);
//  __spi_writebyte(COMMAND_JEDEC_ID);
//  FlashIC.Manufacturer = (enum MANUFACTURER_ID)(manufacture_id = __spi_writebyte(0x00));
//  memory_type = __spi_writebyte(0x00);
//  FlashIC.Size.Memory = memory_size = __spi_writebyte(0x00);
//  __spi_wait();
//  __config_cs(1);
//  //=====================================================
//  if (manufacture_id == MANUFACTURER_ID_WINBOND || manufacture_id == MANUFACTURER_ID_EON || manufacture_id == MANUFACTURER_ID_ESMT)
//    return 1;
//  if (manufacture_id == MANUFACTURER_ID_SPANISION)      //MANUFACTURER_ID same as CYPRESS
//  {
//    if (memory_type == 0x02)
//      store(2);
//    else if (memory_size > 24)                          //CYPRESS: if memory size larger than (1 >> 24 (3 bytes addresable)) bytes
//    {
//      FlashIC.Manufacturer = MANUFACTURER_ID_CYPRESS_4BYTE;
//      store(1);
//    }
//    return 1;
//  }
//  return 0;
//}
//static void _WriteAddress(const FlashICFunction_TypeDef* FlashICFunction, unsigned int Address)
//{
//  if (FlashIC.Size.Memory > 24)
//    __spi_writebyte(Address >> 24);
//  __spi_writebyte(Address >> 16);
//  __spi_writebyte(Address >> 8);
//  __spi_writebyte(Address);
//}
//void FlashIC_Read_0x01(const FlashICFunction_TypeDef* FlashICFunction, unsigned char *RXBuffer, unsigned int Address, unsigned int Length)
//{
//  __config_cs(0);
//  __spi_writebyte(FlashIC.Code.ReadData);
//  _WriteAddress(FlashICFunction, Address);
//  for (unsigned int i = 0; i < Length; i++)
//    RXBuffer[i] = __spi_writebyte(0x00);
//  __spi_wait();
//  __config_cs(1);
//}
//void FlashIC_ReadDMA_0x01(const FlashICFunction_TypeDef* FlashICFunction, unsigned char *RXBuffer, unsigned int Address, unsigned int Length)
//{
//  __config_cs(0);
//  __spi_writebyte(FlashIC.Code.ReadData);
//  _WriteAddress(FlashICFunction, Address);
//  __spi_writeDMA(NULL, Length);
//  __spi_wait();
//  __config_cs(1);
//}
//static void _WriteEnable(const FlashICFunction_TypeDef* FlashICFunction)
//{
//  FlashIC_SR1_TypeDef sr1;
//  __config_cs(0);
//  __spi_writebyte(WRITE_ENABLE);
//  __spi_wait();
//  __config_cs(1);
//  do
//  {
//    __config_cs(0);
//    __spi_writebyte(READ_SR1);
//    sr1.REG = __spi_writebyte(0x00);
//    __spi_wait();
//    __config_cs(1);
//    
//    
//  } while (!sr1.BITS.WEL);
//}
//void FlashIC_EraseMass_0x01(const FlashICFunction_TypeDef* FlashICFunction)
//{
//  _WriteEnable(FlashICFunction);
//
//  __config_cs(0);
//  __spi_writebyte(ERASE_MASS);
//  __spi_wait();
//  __config_cs(1);
//}
//unsigned char FlashIC_IsBusy_0x01(const FlashICFunction_TypeDef* FlashICFunction)
//{
//  FlashIC_SR1_TypeDef sr1;
//  __config_cs(0);
//  __spi_writebyte(READ_SR1);
//  sr1.REG = __spi_writebyte(0x00);
//  __spi_wait();
//  __config_cs(1);
//  return sr1.BITS.BUSY;
//}
//void FlashIC_EraseSector_0x01(const FlashICFunction_TypeDef* FlashICFunction, unsigned int SectorAddress)
//{
//  _WriteEnable(FlashICFunction);
//
//  __config_cs(0);
//  __spi_writebyte(FlashIC.Code.EraseSector);
//  _WriteAddress(FlashICFunction, SectorAddress);
//  __spi_wait();
//  __config_cs(1);
//}
//void FlashIC_Write_0x01(const FlashICFunction_TypeDef* FlashICFunction, const unsigned char* Data, unsigned int Address, unsigned int Length)
//{
//  _WriteEnable(FlashICFunction);
//
//  __config_cs(0);
//  __spi_writebyte(FlashIC.Code.PageProgram);
//  _WriteAddress(FlashICFunction, Address);
//  __spi_writeDMA(Data, Length);
//  __spi_wait();
//  __config_cs(1);
//}