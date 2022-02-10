//#include <MMA7660.h>
//#include <soft_i2c.h>
//
//#define MMA7660_SLV_ADDRESS             0x4C
//
//unsigned char MMA7760_Begin()
//{
//  if (SI2C_WriteBytes(MMA7660_SLV_ADDRESS, 7, "\0", 1))                 //stand by mode to config registers
//  {
//    static const unsigned char config[] = {0xF0, 0, 0, 0x6F, 0x0F};
//    if (SI2C_WriteBytes(MMA7660_SLV_ADDRESS, 6, config, 5))
//    {
//      static const unsigned char active[] = {0xC1};
//      return SI2C_WriteBytes(MMA7660_SLV_ADDRESS, 7, active, 1);        //active mode
//    }
//  }
//  return 0;
//}
//unsigned char MMA7760_ReadAxis(MMA7760Regs_TypeDef* MMA7760Regs)
//{
//  if (SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 0, (unsigned char*)MMA7760Regs, 3))
//  {
//    if (MMA7760Regs->X.BITS.Alert)
//      return SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 0, (unsigned char*)MMA7760Regs, 3);
//    return 1;
//  }
//  return 0;
//}
//MMA7760_Shake_TypeDef MMA7760_ReadShake()
//{
//  MMA7760_Shake_TypeDef shake;
//  BUNION(titl, unsigned char,
//        BaFro                   , 2,
//        PoLa                    , 3,
//        Tap                     , 1,
//        Alert                   , 1,
//        Shake                   , 1) = {.BITS = {.Alert = 0}};
//  shake.BITS.ERROR = !SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 3, &titl.REG, 1);
//  if (titl.BITS.Alert)
//    shake.BITS.ERROR = !SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 3, &titl.REG, 1);
//  if (titl.BITS.Shake)
//    shake.REG |= BIT1 | BIT2 | BIT3;
//  return shake;
//}
//unsigned char MMA7760_Read(unsigned char* Buffer, unsigned char Length)
//{
//  if (SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 0, Buffer, Length))
//  {
//    if (Buffer[0] & BIT5)
//      return SI2C_ReadBytes(MMA7660_SLV_ADDRESS, 0, Buffer, Length);
//    return 1;
//  }
//  return 0;
//}