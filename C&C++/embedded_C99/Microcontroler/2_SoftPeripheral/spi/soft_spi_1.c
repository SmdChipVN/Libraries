#include <soft_spi.h>
#include <config.h>

reg8 SSPI_WriteByte_1(const SSPIFunction_TypeDef __code* SSPIFunction, const reg8 Data)
{
  #ifndef SSPI_POLARITY_1
    #define SSPI_POLARITY_1     SSPIFunction->Info.Polarity
  #endif
#define SHIFT_MSB()\
      SSPIFunction->ConfigMOSI(!!(Data & BIT7)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT6)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT5)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT4)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT3)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT2)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT1)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT0)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx <<= 1; rx |= SSPIFunction->ReadMISO(); SSPIFunction->ConfigSCK(SSPI_POLARITY_1)
#define SHIFT_LSB()\
      reg8 bit[2] = {0, 0x80};\
      SSPIFunction->ConfigMOSI(!!(Data & BIT0)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT1)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT2)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT3)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT4)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT5)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT6)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1);\
      SSPIFunction->ConfigMOSI(!!(Data & BIT7)); SSPIFunction->ConfigSCK(!SSPI_POLARITY_1); rx >>= 1; rx |= bit[SSPIFunction->ReadMISO()]; SSPIFunction->ConfigSCK(SSPI_POLARITY_1)
  //=========================================================       LEVEL 2      ===============================================================================
  reg8 rx = 0;
  #ifdef SSPI_MSB_1
    #if (SSPI_MSB_1 == 1)
      SHIFT_MSB();
    #else
      SHIFT_LSB();
    #endif
  #else
    if (SSPIFunction->Info.MSB) { SHIFT_MSB(); }
    else { SHIFT_LSB();  }
  #endif
  return rx;
}
void SSPI_WriteBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, const unsigned char __gptr* Data, reg8 Length)
{
  while (Length--)
    SSPI_WriteByte_1(SSPIFunction, *Data++);
}
void SSPI_ReadBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, unsigned char* Buffer, reg8 Length)
{
  while (Length--)
    *Buffer++ = SSPI_WriteByte_1(SSPIFunction, 0xFF);
}