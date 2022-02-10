#include <oled.h>
#include <config.h>
#include <common.h>
//==============================================================================================================================================================
void Oled_Init_0(const OledInit_TypeDef __code* OledInit)
{
  //common config
  OLED_CONFIG_CE_0(1);
  Oled_Clear_0();
  OLED_CONFIG_DC_0(0);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xD5); OLED_SPI_WRITE_0(0xF0); OLED_CONFIG_CE_0(1);             //clock divider
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x81); OLED_SPI_WRITE_0(128); OLED_CONFIG_CE_0(1);              //contrast
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xD3); OLED_SPI_WRITE_0(0); OLED_CONFIG_CE_0(1);                //no display offset
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x40); OLED_CONFIG_CE_0(1);                                     //start line address = 0
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xA4 | 0); OLED_CONFIG_CE_0(1);                                 //Entire mode off, output RAM to display
  
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xA0 | (OledInit->ScanMode.REG & 1)); OLED_CONFIG_CE_0(1);      //segment scan mode
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xC0 | (OledInit->ScanMode.REG & 8)); OLED_CONFIG_CE_0(1);      //COM scan mode
  
  if (OledInit->ExtendConfig)
    OledInit->ExtendConfig();

  OLED_CONFIG_DC_0(0);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xAF); OLED_CONFIG_CE_0(1);                                     //show
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Clear_0()
{
  reg8 i;
  for (i = 0; i < 8; i++)
  {
    OLED_CONFIG_DC_0(0);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xB0 | i); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(OLED_X_OFFSET_0(0)); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x10); OLED_CONFIG_CE_0(1);
    {
      reg8 j;
      OLED_CONFIG_DC_0(1);
      OLED_CONFIG_CE_0(0);
      for (j = 0; j < 128; j++)
        OLED_SPI_WRITE_0(0);
      OLED_CONFIG_CE_0(1);
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Fill_0(const unsigned char __gptr* Data)
{
  reg8 i;
  for (i = 0; i < 8; i++)
  {
    OLED_CONFIG_DC_0(0);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xB0 | i); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(OLED_X_OFFSET_0(0)); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x10); OLED_CONFIG_CE_0(1);
    {
      reg8 j;
      OLED_CONFIG_DC_0(1);
      OLED_CONFIG_CE_0(0);
      for (j = 0; j < 127; j++)
        OLED_SPI_WRITE_0(Data[j]);
      OLED_CONFIG_CE_0(1);
    }
    Data += 128;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_FillPart_0(const unsigned char __gptr* Data, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1)
{
  reg8 x_length = X1 - X0 + 1;
  X0 = OLED_X_OFFSET_0(X0);
  while (Y0 <= Y1)
  {
    OLED_CONFIG_DC_0(0);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xB0 | Y0); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(X0 & 0x0F); OLED_CONFIG_CE_0(1);
    OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x10 | (X0 >> 4)); OLED_CONFIG_CE_0(1);
    {
      reg8 j;
      OLED_CONFIG_DC_0(1);
      OLED_CONFIG_CE_0(0);
      for (j = 0; j < x_length; j++)
        OLED_SPI_WRITE_0(Data[j]);
      OLED_CONFIG_CE_0(1);
    }
    Data += x_length;
    Y0++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_On_0()
{
  OLED_CONFIG_DC_0(0);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xAF); OLED_CONFIG_CE_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Off_0()
{
  OLED_CONFIG_DC_0(0);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0xAE); OLED_CONFIG_CE_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//NOTE: REFER DATASHEET FOR AVAILABLE
static void DMA_EndTransfer()
{
  OLED_CONFIG_CE_0(1);
}
void Oled_FillPartDMA_0(DMAFunction_TypeDef* DMAFunction, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1)
{
  OLED_CONFIG_DC_0(0);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x21); OLED_SPI_WRITE_0(OLED_X_OFFSET_0(X0)); OLED_SPI_WRITE_0(OLED_X_OFFSET_0(X1)); OLED_CONFIG_CE_0(1);
  OLED_CONFIG_CE_0(0); OLED_SPI_WRITE_0(0x22); OLED_SPI_WRITE_0(Y0); OLED_SPI_WRITE_0(Y1); OLED_CONFIG_CE_0(1);
  
  OLED_CONFIG_DC_0(1);
  DMAFunction->EndTransferHandle = DMA_EndTransfer;
  DMAFunction->DMATransfer(DMAFunction->Data, (X1 - X0 + 1) * (Y1 - Y0 + 1));  
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_FillDMA_0(DMAFunction_TypeDef* DMAFunction)
{
  Oled_FillPartDMA_0(DMAFunction, 0, 0, 127, 7);
}