#include <soft_i2c.h>
#include <config.h>

/*
#define PREPARE_WRITE           



#define SI2C_START()    SI2C_CONFIG_SDA_0(0);SI2C_CONFIG_SCL_0(0)
#define SI2C_STOP()     SI2C_CONFIG_SCL_0(1);SI2C_CONFIG_SDA_0(1)

static reg8 SI2C_WriteByte(const reg8 Data)
{
  reg8 ret;
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT6)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT5)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT4)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT3)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT2)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT1)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT0)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  
  SI2C_CONFIG_SDA_MODE_0(0);
  SI2C_CONFIG_SCL_0(1);
  ret = SI2C_READ_SDA_0();
  SI2C_CONFIG_SDA_0(ret);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return ret;
}
reg8 SI2C_WriteBytes_0(SI2CWriter_TypeDef* SI2CWriter)
{
  if (SI2CWriter->Normal.SlaveAddress & BIT0)
  {
    SI2CWriter->Stream.BitIndex = 0;
    SI2CWriter->Stream.Length += 2;
    SI2CWriter->Stream.State = DATA_STREAM_STATE_PREPARE;
    return 1;
  }
  else
  {
    SI2C_START();
    if (SI2C_WriteByte(SI2CWriter->Normal.SlaveAddress & (~BIT0)))
      goto FAIL;
    if (SI2C_WriteByte(SI2CWriter->Normal.DataAddress))
      goto FAIL;
    while (SI2CWriter->Normal.Length--)
    {
      if (SI2C_WriteByte(*SI2CWriter->Normal.Data++))
        goto FAIL;
    }
    SI2C_STOP();
    return 1;
    FAIL:
    SI2C_CONFIG_SDA_0(0);
    SI2C_STOP();
    return 0;
  }
}
static reg8 SI2C_ReadByte(const reg8 NACK)
{
  reg8 result;
  SI2C_CONFIG_SDA_MODE_0(0);
  for (reg8 i = 0; i < 8; i++)
  {
    result <<= 1;
    SI2C_CONFIG_SCL_0(1);
    result |= SI2C_READ_SDA_0();
    SI2C_CONFIG_SCL_0(0);
  }
  SI2C_CONFIG_SDA_0(NACK);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return result;
}

//reg8 SI2C_ReadBytes_0(SI2CReader_TypeDef* SI2CReader)
//{
//  if (SI2CWriter->Normal.SlaveAddress & BIT0)
//  {
//    SI2CWriter->Stream.BitIndex = 0;
//    SI2CWriter->Stream.State = DATA_STREAM_STATE_PREPARE + 1;
//    return 1;
//  }
//  else
//  {
//    unsigned char ret = 1;
//    SI2C_START();
//    if (_SI2C_WriteByte_Mask(SI2CFunction, SlaveAddr << 1))
//    {
//      ret = 0;
//      goto END;
//    }
//    if (_SI2C_WriteByte_Mask(SI2CFunction, DataAddr))
//    {
//      ret = 0;
//      goto END;
//    }
//    SI2C_STOP();
//    //restart
//    SI2C_START();
//    if (_SI2C_WriteByte_Mask(SI2CFunction, (SlaveAddr << 1) | 0x01))
//    {
//      ret = 0;
//      goto END;
//    }
//    while (--Length)
//      *Buffer++ = _SI2C_ReadByte_Mask(SI2CFunction, 0);
//    *Buffer = _SI2C_ReadByte_Mask(SI2CFunction, 1);
//    END:
//    SI2C_CONFIG_SDA(0);
//    SI2C_STOP();
//    return ret;
//  }
//}
//void SI2C_Process_0(SI2CWriter_TypeDef* SI2CWriter)
//{
//  if (SI2CWriter->Stream.State)
//  {
//    switch (SI2CWriter->Stream.State)
//    {
//      case DATA_STREAM_STATE_PREPARE:
//        SI2CWriter->Stream.State += 10;
//        break;
//      //--------------------------------------------------------------------------------------------------------------------------------------------------------
//      case DATA_STREAM_STATE_START_WRITTING:
//        break;
//      case DATA_STREAM_STATE_WRITTING:
//        break;
//      case DATA_STREAM_STATE_END_WRITTING:
//        break;
//      //--------------------------------------------------------------------------------------------------------------------------------------------------------
//      case DATA_STREAM_STATE_START_READDING:
//        break;
//      case DATA_STREAM_STATE_READING:
//        break;
//      case DATA_STREAM_STATE_END_READING:
//        break;
//      //--------------------------------------------------------------------------------------------------------------------------------------------------------
//      case DATA_STREAM_STATE_ENDING:
//        break;
//    }
//  }
//}






#ifdef SI2C_CONFIG_SDA
  #define SI2C_DIRECT
  #define _SI2C_WriteByte_Mask(SI2CFunction, Data)      _SI2C_WriteByte(Data)
  #define _SI2C_ReadByte_Mask(SI2CFunction, ACK)        _SI2C_ReadByte(ACK)
#else
  #define _SI2C_WriteByte_Mask(SI2CFunction, Data)      _SI2C_WriteByte(SI2CFunction, Data)
  #define _SI2C_ReadByte_Mask(SI2CFunction, NACK)       _SI2C_ReadByte(SI2CFunction, NACK)
  #define SI2C_CONFIG_SDA(value)                        SI2CFunction->ConfigSDA(value)
  #define SI2C_READ_SDA()                               SI2CFunction->ReadSDA()
  #define SI2C_CONFIG_SCL(value)                        SI2CFunction->ConfigSCL(value)
  #define SI2C_CONFIG_SDA_MODE(value)                   SI2CFunction->ConfigSDAMode(value)
  #define SI2C_DELAY()                                  SI2CFunction->Delay()
#endif

#define SI2C_START()                                    SI2C_CONFIG_SDA(0);SI2C_CONFIG_SCL(0)
#define SI2C_STOP()                                     SI2C_CONFIG_SCL(1);SI2C_CONFIG_SDA(1)


#ifdef SI2C_DIRECT
static unsigned char _SI2C_ReadByte(const unsigned char NACK)
#else
static unsigned char _SI2C_ReadByte(const SI2CFunction_TypeDef* SI2CFunction, const unsigned char NACK)
#endif
{
  unsigned char result;
  SI2C_CONFIG_SDA_MODE(0);
  SI2C_CONFIG_SCL(1);
  result = SI2C_READ_SDA();
  SI2C_CONFIG_SCL(0);
  
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  result <<= 1; SI2C_CONFIG_SCL(1); result |= SI2C_READ_SDA(); SI2C_CONFIG_SCL(0);
  
  SI2C_CONFIG_SDA(NACK);
  SI2C_CONFIG_SDA_MODE(1);
  SI2C_CONFIG_SCL(1); SI2C_CONFIG_SCL(0);
#ifndef SI2C_DIRECT
  if (SI2CFunction->Delay)
#endif
    SI2C_DELAY();
  return result;
}

#ifdef SI2C_DIRECT
unsigned char SI2C_WriteBytes(const unsigned char SlaveAddr, const unsigned char DataAddr, const unsigned char *Data, unsigned char Length)
#else
unsigned char SI2C_WriteBytes(const SI2CFunction_TypeDef* SI2CFunction, const unsigned char SlaveAddr, const unsigned char DataAddr, const unsigned char *Data, unsigned char Length)
#endif
{
  SI2C_START();
  if (_SI2C_WriteByte_Mask(SI2CFunction, SlaveAddr << 1))
    goto FAIL;
  if (_SI2C_WriteByte_Mask(SI2CFunction, DataAddr))
    goto FAIL;
  while (Length--)
  {
    if (_SI2C_WriteByte_Mask(SI2CFunction, *Data++))
      goto FAIL;
  }
  SI2C_STOP();
  return 1;
  FAIL:
  SI2C_CONFIG_SDA(0);
  SI2C_STOP();
  return 0;
}

#ifdef SI2C_DIRECT
unsigned char SI2C_ReadBytes(const unsigned char SlaveAddr, const unsigned char DataAddr, unsigned char *Buffer, unsigned char Length)
#else
unsigned char SI2C_ReadBytes(const SI2CFunction_TypeDef* SI2CFunction, const unsigned char SlaveAddr, const unsigned char DataAddr, unsigned char *Buffer, unsigned char Length)
#endif
{
  unsigned char ret = 1;
  SI2C_START();
  if (_SI2C_WriteByte_Mask(SI2CFunction, SlaveAddr << 1))
  {
    ret = 0;
    goto END;
  }
  if (_SI2C_WriteByte_Mask(SI2CFunction, DataAddr))
  {
    ret = 0;
    goto END;
  }
  SI2C_STOP();
  //restart
  SI2C_START();
  if (_SI2C_WriteByte_Mask(SI2CFunction, (SlaveAddr << 1) | 0x01))
  {
    ret = 0;
    goto END;
  }
  while (--Length)
    *Buffer++ = _SI2C_ReadByte_Mask(SI2CFunction, 0);
  *Buffer = _SI2C_ReadByte_Mask(SI2CFunction, 1);
  END:
  SI2C_CONFIG_SDA(0);
  SI2C_STOP();
  return ret;
}
*/





#define SI2C_START()    SI2C_CONFIG_SDA_0(0);SI2C_CONFIG_SCL_0(0)
#define SI2C_STOP()     SI2C_CONFIG_SCL_0(1);SI2C_CONFIG_SDA_0(1)

static reg8 SI2C_WriteByte(const reg8 Data)
{
  reg8 ret;
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT6)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT5)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT4)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT3)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT2)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT1)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT0)); SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  
  SI2C_CONFIG_SDA_MODE_0(0);
  SI2C_CONFIG_SCL_0(1);
  ret = SI2C_READ_SDA_0();
  SI2C_CONFIG_SDA_0(ret);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return ret;
}
unsigned char SI2C_WriteBytes(const unsigned char SlaveAddr, const unsigned char DataAddr, const unsigned char *Data, unsigned char Length)
{
  SI2C_START();
  if (SI2C_WriteByte(SlaveAddr))
    goto FAIL;
  if (SI2C_WriteByte(DataAddr))
    goto FAIL;
  while (Length--)
  {
    if (SI2C_WriteByte(*Data++))
      goto FAIL;
  }
  SI2C_STOP();
  return 1;
  FAIL:
  SI2C_CONFIG_SDA_0(0);
  SI2C_STOP();
  return 0;
}
static reg8 SI2C_ReadByte(const reg8 NACK)
{
  reg8 result;
  SI2C_CONFIG_SDA_MODE_0(0);
  for (reg8 i = 0; i < 8; i++)
  {
    result <<= 1;
    SI2C_CONFIG_SCL_0(1);
    result |= SI2C_READ_SDA_0();
    SI2C_CONFIG_SCL_0(0);
  }
  SI2C_CONFIG_SDA_0(NACK);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return result;
}
unsigned char SI2C_ReadBytes(const unsigned char SlaveAddr, const unsigned char DataAddr, unsigned char *Buffer, unsigned char Length)
{
  unsigned char ret = 1;
  SI2C_START();
  if (SI2C_WriteByte(SlaveAddr))
  {
    ret = 0;
    goto END;
  }
  if (SI2C_WriteByte(DataAddr))
  {
    ret = 0;
    goto END;
  }
  SI2C_STOP();
  //restart
  SI2C_START();
  if (SI2C_WriteByte((SlaveAddr | 0x01)))
  {
    ret = 0;
    goto END;
  }
  while (--Length)
    *Buffer++ = SI2C_ReadByte(0);
  *Buffer = SI2C_ReadByte(1);
  END:
  SI2C_CONFIG_SDA_0(0);
  SI2C_STOP();
  return ret;
}
