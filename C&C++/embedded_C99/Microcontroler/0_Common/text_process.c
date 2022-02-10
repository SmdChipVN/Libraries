#include <common.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Text_FromInt(reg16 Value, unsigned char* TextBuffer)
{
  reg8 index = 0, ret;
  if (value > 9999)
    TextBuffer[index++] = value / 10000;
  if (value > 999)
    TextBuffer[index++] = (value / 1000) % 10;
  if (value > 99)
    TextBuffer[index++] = (value / 100) % 10;
  if (value > 9)
    TextBuffer[index++] = (value / 10) % 10;
  TextBuffer[index++] = value % 10;
  
  TextBuffer[index] = 0;
  ret = index;
  while (index)
    TextBuffer[--index] += '0';
  return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Text_Length(unsigned char* Text, reg8 BreakChar)
{
  reg8 length = 0;
  while (Text[length] && Text[length] != BreakChar)
    length++;
  return length;
}