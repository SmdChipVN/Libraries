#include <oled.h>
#include <common.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define COMMAND(command)                OledFunction->ConfigDC(0);_WriteByte(OledFunction, command)
#define COMMANDs(command, length)       OledFunction->ConfigDC(0);_WriteBytes(OledFunction, command, length, 0)
#define DATAs(data, length)             OledFunction->ConfigDC(1);_WriteBytes(OledFunction, data, length, 1)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void _WriteByte(const OledFunction_TypeDef* OledFunction, reg8 Value)
{
  OledFunction->ConfigCE(0);
  OledFunction->SPI_WriteByte(Value);
  OledFunction->ConfigCE(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void _WriteBytes(const OledFunction_TypeDef* OledFunction, const unsigned char* Data, reg8 Length, reg8 lastDC)
{
  OledFunction->ConfigCE(0);
  for (reg8 i = 0; i < Length; i++)
  {
    OledFunction->SPI_WriteByte(Data[i]);
    OledFunction->ConfigDC(!lastDC); OledFunction->ConfigDC(lastDC);
  }
  OledFunction->ConfigCE(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Begin_1(const OledFunction_TypeDef* OledFunction)
{
  extern void delay_ms(reg16 Time);
  OledFunction->ConfigCE(1);
  OledFunction->ConfigDC(1);
  OledFunction->ConfigRST(0);  
  delay_ms(10);
  OledFunction->ConfigRST(1);
  delay_ms(100);
  
  unsigned char ar[2] = {0x81, 128};
  COMMANDs(ar, 2);                              //contrast
  ar[0] = 0xD5; ar[1] = 0xF0;                   //clock divider
  COMMANDs(ar, 2);
  ar[0] = 0xD3; ar[1] = 0x00;                   //no display offset
  COMMANDs(ar, 2);
  COMMAND(0x40);                                //start line address=0
  ar[0] = 0x8D; ar[1] = 0x14;                   //enable charge pump
  COMMANDs(ar, 2);
  ar[0] = 0x20; ar[1] = 0x00;                   //memory adressing mode=horizontal
  COMMANDs(ar, 2);
  COMMAND(0xA1);                                //segment remapping mode
  COMMAND(0xC8);                                //COM output scan direction
  COMMAND(0xA4);                                //output RAM to display
  COMMAND(0x2E);                                //stop scrolling  
  Oled_Clear_1(OledFunction);
  COMMAND(0xAF);                                //show
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void _Eraser(const OledFunction_TypeDef* OledFunction, reg8 Length)
{
  OledFunction->ConfigDC(1);
  OledFunction->ConfigCE(0);
  while (Length--)
  {
    OledFunction->SPI_WriteByte(0);
    OledFunction->ConfigDC(0); OledFunction->ConfigDC(1);
  }
  OledFunction->ConfigCE(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Clear_1(const OledFunction_TypeDef* OledFunction)
{
  for (reg8 i = 0; i < 8; i++)
  {
    COMMAND(0xB0 + i);
    COMMAND(2);
    COMMAND(0x10);
    _Eraser(OledFunction, 128);   
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_SetPosition_1(const OledFunction_TypeDef* OledFunction, reg8 X, reg8 Y)
{
  COMMAND(0xB0 + Y);
  COMMAND((X + 2) & 0x0F);
  COMMAND(0x10 | ((X + 2) >> 4));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Eraser_1(const OledFunction_TypeDef* OledFunction, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1)
{
  while ((Y0 <= Y1) && (X0 <= X1))
  {
    Oled_SetPosition_1(OledFunction, X0, Y0);
    _Eraser(OledFunction, X1 - X0 + 1);
    Y0++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Off_1(const OledFunction_TypeDef* OledFunction)
{
  COMMAND(0xAE);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_On_1(const OledFunction_TypeDef* OledFunction)
{
  COMMAND(0xAF);
}