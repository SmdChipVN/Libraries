//#include <HX711.h>
//#include <config.h>
//
//void HX711_Begin()
//{
//  unsigned char i;
//  CLR_HX711_CK();  
//  for (i = 0; i < 25; i++)
//  {
//    SET_HX711_CK();
//    DELAY_HX711_T2();
//    DELAY_HX711_T3();
//    CLR_HX711_CK();
//    DELAY_HX711_T4();
//  }
//}
//
//bool HX711_Read(signed long* OutValue)
//{
//  unsigned char i;
//  if (RD_HX711_DOUT())
//    return false;
//  DELAY_HX711_T1();
//  for (*OutValue = 0, i = 0; i < 24; i++)
//  {
//    SET_HX711_CK();
//    DELAY_HX711_T2();
//    *OutValue <<= 1;
//    DELAY_HX711_T3();
//    CLR_HX711_CK();
//    *OutValue |= RD_HX711_DOUT();
//    DELAY_HX711_T4();
//  }
//  SET_HX711_CK();
//  *OutValue ^= 0x800000;
//  DELAY_HX711_T3();
//  CLR_HX711_CK();
//  return true;
//}