/*
MODE 0:
  +) Config:
      #define SSPI_MSB_0                              1
      #define SSPI_POLARITY_0                         0
      #define SSPI_CONFIG_MOSI_0(IsSet)               //
      #define SSPI_READ_MISO_0()                      1
      #define SSPI_CONFIG_SCK_0(IsSet)                //
  +) Declare:
  +) Using:
      reg8 SSPI_WriteByte_0(const reg8 Data);
      #define SSPI_ReadByte_0()                 SSPI_WriteByte_0(0xFF)
      void SSPI_WriteBytes_0(const unsigned char __gptr* Data, reg8 Length);
      void SSPI_ReadBytes_0(unsigned char* Buffer, reg8 Length);
MODE 1:
  +) Config:
      #define SSPI_MSB_1                              1
        -)(maybe) override all of SSPIFunction.Info.MSB
      #define SSPI_POLARITY_1                         0
        -)(maybe) override all of SSPIFunction.Info.Polarity
  +) Declare:
  +) Using:
      reg8 SSPI_WriteByte_1(const SSPIFunction_TypeDef __code* SSPIFunction, const reg8 Data);
      #define SSPI_ReadByte_1(SSPIFunction)     SSPI_WriteByte_1(SSPIFunction, 0xFF)
      void SSPI_WriteBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, const unsigned char __gptr* Data, reg8 Length);
      void SSPI_ReadBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, unsigned char* Buffer, reg8 Length);
*/
#ifndef _SOFT_SPI_H_
#define _SOFT_SPI_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  struct
  {
    unsigned char MSB;
    unsigned char Polarity;
  } Info;
  void (* ConfigMOSI)(reg8 IsSet);
  reg8 (* ReadMISO)();
  void (* ConfigSCK)(reg8 IsSet);
} SSPIFunction_TypeDef;
/*
  Example:
    static void SSPI_ConfigMOSI_0(reg8 IsSet)
    {
      SSPI_MOSI_PIN_0 = IsSet;
    }
    static reg8 SSPI_ReadMISO_0()
    {
      return SSPI_MISO_PIN_0;
    }
    static void SSPI_ConfigSCK_0(reg8 IsSet)
    {
      SSPI_SCK_PIN_0 = IsSet;
    }
    static const SSPIFunction_TypeDef __code SSPIFunction_0 = {
      .Info = {.MSB = 1, .Polarity = 0}, 
      .ConfigMOSI = SSPI_ConfigMOSI_0,
      .ReadMISO = SSPI_ReadMISO_0,
      .ConfigSCK = SSPI_ConfigSCK_0,
    };
*/
//==============================================================================================================================================================
reg8 SSPI_WriteByte_0(const reg8 Data);
#define SSPI_ReadByte_0()               SSPI_WriteByte_0(0xFF)
void SSPI_WriteBytes_0(const unsigned char __gptr* Data, reg8 Length);
void SSPI_ReadBytes_0(unsigned char* Buffer, reg8 Length);
//==============================================================================================================================================================
reg8 SSPI_WriteByte_1(const SSPIFunction_TypeDef __code* SSPIFunction, const reg8 Data);
#define SSPI_ReadByte_1(SSPIFunction)   SSPI_WriteByte_1(SSPIFunction, 0xFF)
void SSPI_WriteBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, const unsigned char __gptr* Data, reg8 Length);
void SSPI_ReadBytes_1(const SSPIFunction_TypeDef __code* SSPIFunction, unsigned char* Buffer, reg8 Length);

#endif