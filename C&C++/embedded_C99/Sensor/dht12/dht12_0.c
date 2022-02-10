//#include <soft_i2c.h>
//#include <dht12.h>
//
//#ifdef DHT12_DIRECT
//  extern DHT12_TypeDef DHT12_DIRECT;
//  #define DHT12_MASK    DHT12_DIRECT
//#else
//  #define DHT12_MASK    (*DHT12)
//#endif
//
//#ifdef DHT12_DIRECT
//unsigned char DHT12_Read()
//#else
//unsigned char DHT12_Read(DHT12_TypeDef* DHT12)
//#endif
//{
//  return SI2C_ReadBytes(DHT12_ID, 0, (unsigned char*)&DHT12_MASK, 4);
//}