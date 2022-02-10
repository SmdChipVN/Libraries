#include <crc.h>

unsigned int CRC_Calculator(CRC_TypeDef* CRC, unsigned int InitValue, unsigned int* Input, unsigned int Length)
{
  unsigned int ret;
  unsigned int index;
   CRC->DR = InitValue;
  for (index = 0; index < Length; index++)
  {
    CRC->DR = Input[index];
    ret = CRC->DR;
  }
  return ret;
}