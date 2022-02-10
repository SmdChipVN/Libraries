#ifndef _DHT12_H_
#define _DHT12_H_

#define DHT12_ID        0x5C
typedef struct
{
  struct
  {
    unsigned char Interger;
    unsigned char Decimal;
  } Humidity;
  struct
  {
    unsigned char Interger;
    unsigned char Decimal;
  } Temperature;
} DHT12_TypeDef;

#include <config.h>
#ifdef DHT12_DIRECT
  unsigned char DHT12_Read();
#else
  unsigned char DHT12_Read(DHT12_TypeDef* DHT12);
#endif

#endif