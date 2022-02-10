#ifndef _ST7789_H_
#define _ST7789_H_

typedef struct
{
  void (*ConfigRST)(unsigned char IsSet);
  void (*ConfigDC)(unsigned char IsSet);
  void (*ConfigCS)(unsigned char IsSet);
  void (*WriteByte)(unsigned char Data);
} ST7789Function_TypeDef;

void ST7789_Begin(const ST7789Function_TypeDef* ST7789Function);

#endif