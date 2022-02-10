#include <rtc.h>
#include <clk.h>

//#pragma vector = RTC_IRQn
#pragma vector = 6
__interrupt void RTC_ISR()
{
  if (RTC.ISR.r2.BITS.WUTF)
    RTC_Weakup_ISR();
  if (RTC.ISR.r2.BITS.ALRAF)
    RTC_Alarm_ISR();
  RTC.ISR.r2.REG = 0;
}

void RTC_Init()
{  
  //CLK.PCKENR2.BITS.RTC = 1;
  //change RTC clock source
  CLK.RTCR.REG = BIT6 | BIT2;
  while (CLK.RTCR.BITS.RTCSWBSY);  

  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  //reset RTC registers
  RTC.ISR.r2.REG = 0;
  RTC.CR.r2.BITS.WUTE = 0;
  while (!RTC.ISR.r1.BITS.WUTWF);

  RTC.ISR.r1.BITS.INIT = 1;
  while (!RTC.ISR.r1.BITS.INITF);
  RTC.CR.r1.REG = BIT6 | BIT4 | BIT2;  
  RTC.ISR.r1.BITS.INIT = 0;
  RTC.CR.r2.REG = BIT6 | BIT4;

  //write protected
  RTC.WPR = 0x00;
  
  RTC_ConfigTick(1);
}

void RTC_ConfigTick(unsigned char IsSecond)
{
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.ISR.r1.BITS.INIT = 1;
  while (!RTC.ISR.r1.BITS.INITF);  
  if (IsSecond)
  {
    /*NOTE: adjust for 1s <=> 1Hz*/
    //38000 / 4 / ((RTC.SPRER.REG + 1) * (RTC.APRER.REG + 1)) = 1
//    RTC.SPRER.REG = 94;               //max: 32767        //calculated but not exactly
//    RTC.APRER.REG = 99;               //max: 127
    RTC.PRSC.SPRER.REG = 250;
    RTC.PRSC.APRER.REG = 35;
  }
  else
  {
    /*NOTE: adjust for 1ms <=> 1000Hz*/
    //38000 / 4 / ((RTC.SPRER.REG + 1) * (RTC.APRER.REG + 1)) = 1000
    RTC.PRSC.SPRER.REG = 8;             //max: 32767
    RTC.PRSC.APRER.REG = 0;             //max: 127
  }
  RTC.ISR.r1.BITS.INIT = 0;
  //write protected
  RTC.WPR = 0x00;
}

static unsigned char binToDec(unsigned char Bin)
{
  return ((Bin >> 4) * 10) + (Bin & 0x0F);
}
static unsigned char decToBin(unsigned char Dec)
{
  return ((Dec / 10) << 4) | (Dec % 10);
}
void RTC_SetTime(DateTime_TypeDef* DateTime)
{
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.ISR.r1.BITS.INIT = 1;
  while (!RTC.ISR.r1.BITS.INITF);
  RTC.TIME.SECOND.REG = decToBin(DateTime->Second);
  RTC.TIME.MINUTE.REG = decToBin(DateTime->Minute);
  RTC.TIME.HOUR.REG = decToBin(DateTime->Hour);
  RTC.TIME.DATE.REG = decToBin(DateTime->Date);
  RTC.TIME.MONTH_WEEKDAY.REG =  ((DateTime->WeekDay + 1) << 5) | decToBin(DateTime->Month);
  RTC.TIME.YEAR.REG = decToBin(DateTime->Year);
  RTC.ISR.r1.BITS.INIT = 0;
  //write protected
  RTC.WPR = 0x00;
}
void RTC_GetTime(DateTime_TypeDef* DateTime)
{
  DateTime->Second = binToDec(RTC.TIME.SECOND.REG);
  DateTime->Minute = binToDec(RTC.TIME.MINUTE.REG);
  DateTime->Hour = binToDec(RTC.TIME.HOUR.REG);
  DateTime->WeekDay = RTC.TIME.MONTH_WEEKDAY.BITS.WEEKDAY - 1;
  DateTime->Date = binToDec(RTC.TIME.DATE.REG);
  DateTime->Month = binToDec(RTC.TIME.MONTH_WEEKDAY.REG & 0x1F);
  DateTime->Year = binToDec(RTC.TIME.YEAR.REG);
}
void RTC_Alarm(Alarm_TypeDef* Alarm)
{
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.CR.r2.BITS.ALRAE = 0;
  while (!RTC.ISR.r1.BITS.ALRAWF);
  RTC.ALARM.SECOND.REG = (Alarm->Mask.Second << 7) | decToBin(Alarm->Second);
  RTC.ALARM.MINUTE.REG = (Alarm->Mask.Minute << 7) | decToBin(Alarm->Minute);
  RTC.ALARM.HOUR.REG = (Alarm->Mask.Hour << 7) | decToBin(Alarm->Hour);
  RTC.ALARM.DATE.REG = (Alarm->Mask.Date_WeekDay << 7) | (Alarm->Date_WeekDay.IsWeekday << 6) | ((Alarm->Date_WeekDay.Value / 10) << 4) | (Alarm->Date_WeekDay.Value + Alarm->Date_WeekDay.IsWeekday);
  RTC.CR.r2.BITS.ALRAE = 1;
  
  //write protected
  RTC.WPR = 0x00;
}
void RTC_DisableAlarm()
{
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.CR.r2.BITS.ALRAE = 0;
  while (!RTC.ISR.r1.BITS.ALRAWF);
  
  //write protected
  RTC.WPR = 0x00;
}

void RTC_Weakup(unsigned short Time)
{
  if (!Time)
    return;
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.CR.r2.BITS.WUTE = 0;
  while (!RTC.ISR.r1.BITS.WUTWF);
  Time--;
  RTC.WUTR.REGS.HIGH = Time >> 8;
  RTC.WUTR.REGS.LOW = Time;
  RTC.CR.r2.BITS.WUTE = 1;
  
  //write protected
  RTC.WPR = 0x00;
}

void RTC_DisableWeakup()
{
  //unlock write protected
  RTC.WPR = 0xCA;
  RTC.WPR = 0x53;
  
  RTC.CR.r2.BITS.WUTE = 0;
  while (!RTC.ISR.r1.BITS.WUTWF);
  
  //write protected
  RTC.WPR = 0x00;
}

__weak void RTC_Alarm_ISR()
{
  
}

__weak void RTC_Weakup_ISR()
{
  
}