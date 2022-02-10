#include <st7789.h>
#include <common.h>

typedef enum
{
  ST_CMD_DELAY          = 0x80,
  ST7789_NOP            = 0x00,
  ST7789_SWRESET        = 0x01,
  ST7789_RDDID          = 0x04,
  ST7789_RDDST          = 0x09,
  ST7789_SLPIN          = 0x10,
  ST7789_SLPOUT         = 0x11,
  ST7789_PTLON          = 0x12,
  ST7789_NORON          = 0x13,
  ST7789_INVOFF         = 0x20,
  ST7789_INVON          = 0x21,
  ST7789_DISPOFF        = 0x28,
  ST7789_DISPON         = 0x29,
  ST7789_CASET          = 0x2A,
  ST7789_RASET          = 0x2B,
  ST7789_RAMWR          = 0x2C,
  ST7789_RAMRD          = 0x2E,
  ST7789_PTLAR          = 0x30,
  ST7789_COLMOD         = 0x3A,
  ST7789_MADCTL         = 0x36,
  ST7789_MADCTL_MY      = 0x80,
  ST7789_MADCTL_MX      = 0x40,
  ST7789_MADCTL_MV      = 0x20,
  ST7789_MADCTL_ML      = 0x10,
  ST7789_MADCTL_RGB     = 0x00,
  ST7789_MADCTL_BGR     = 0x08,
  ST7789_RDID1          = 0xDA,
  ST7789_RDID2          = 0xDB,
  ST7789_RDID3          = 0xDC,
  ST7789_RDID4          = 0xDD,
} ST7789;

static const ST7789Function_TypeDef* _ST7789Function;
extern void delay_ms(unsigned int Time);

static void _ST7789_Reset()
{
  _ST7789Function->ConfigRST(0);
  delay_ms(10);
  _ST7789Function->ConfigRST(1);
  delay_ms(120);
}

void _ST7789_SetWindows(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1){
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_CASET);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->WriteByte((x0 + 0) >> 8);
  _ST7789Function->WriteByte(x0 + 0);
  _ST7789Function->WriteByte((x1 + 0) >> 8);
  _ST7789Function->WriteByte(x1 + 0);
//  _ST7789Function->ConfigCS(1);
  
//  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_RASET);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->WriteByte((y0 + 0) >> 8);
  _ST7789Function->WriteByte(y0 + 0);
  _ST7789Function->WriteByte((y1 + 0) >> 8);
  _ST7789Function->WriteByte(y1 + 0);
//  _ST7789Function->ConfigCS(1);
  
//  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_RAMWR);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
}

void _ST7789_Clr(){
  _ST7789_SetWindows(0, 0, 240, 240);
  _ST7789Function->ConfigCS(0);
  for(unsigned char y = 0; y < 240; y++){
    for(unsigned char x = 0; x < 240; x++){
      _ST7789Function->WriteByte(0x00);
      _ST7789Function->WriteByte(0x00);
    }
  }
  _ST7789Function->ConfigCS(1);
}

void ST7789_Begin(const ST7789Function_TypeDef* ST7789Function)
{
  _ST7789Function = ST7789Function;
  _ST7789_Reset();
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_SWRESET);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
  delay_ms(150);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_SLPOUT);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
  delay_ms(10);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_COLMOD);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->WriteByte(0x55);
  _ST7789Function->ConfigCS(1);
  delay_ms(10);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->WriteByte(ST7789_MADCTL);
  _ST7789Function->ConfigCS(1);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_CASET);
  _ST7789Function->ConfigDC(1);
  
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(240);
  
  _ST7789Function->ConfigCS(1);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_RASET);
  _ST7789Function->ConfigDC(1);
  
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->WriteByte(240);
  
  _ST7789Function->ConfigCS(1);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_INVON);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
  delay_ms(10);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_NORON);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
  delay_ms(10);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(ST7789_DISPON);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->ConfigCS(1);
  delay_ms(20);
  
  _ST7789Function->ConfigCS(0);
  _ST7789Function->ConfigDC(0);
  _ST7789Function->WriteByte(0x00);
  _ST7789Function->ConfigDC(1);
  _ST7789Function->WriteByte(ST7789_MADCTL);
  _ST7789Function->ConfigCS(1);
  delay_ms(1);
}
