/*
  RTC using LSI
*/

#ifndef _RTC_H_
#define _RTC_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  struct
  {
    BUNION(SECOND, unsigned char,//0x0           0x--            TR1-Time register 1
      SU                , 4,    //0:3           --              Second units in BCD format
      ST                , 3,    //4:6           --              Second tens in BCD format
      _reserved         , 1);
    BUNION(MINUTE, unsigned char,//0x1           0x--            TR1-Time register 2
      MU                , 4,    //0:3           --              Minute units in BCD format
      MT                , 3,    //4:6           --              Minute tens in BCD format
      _reserved         , 1);
    BUNION(HOUR, unsigned char,  //0x2           0x--            TR1-Time register 3
      HU                , 4,    //0:3           --              Hour units in BCD format
      HT                , 2,    //4-5           --              Hour tens in BCD format
      PM                , 1,    //6             --              AM/PM notation
      _reserved         , 1);
    unsigned char _reserved;
    BUNION(DATE, unsigned char,  //0x4           0x--            TR1-Date register 1
      DU                , 4,    //0:3           --              Date units in BCD format
      DT                , 2,    //4-5           --              Date tens in BCD format
      _reserved         , 2);
    BUNION(MONTH_WEEKDAY, unsigned char,//0x5    0x--            TR1-Date register 2
      MU                , 4,    //0:3           --              Month units in BCD format
      MT                , 1,    //4             --              Month tens in BCD format
      WEEKDAY           , 3);   //5:7           --              Week day units: 001->111: Monday->Sunday
    BUNION(YEAR, unsigned char,  //0x6           0x--            TR1-Date register 3
      YU                , 4,    //0:3           --              Year units in BCD format
      YT                , 4);   //4-7           --              Year tens in BCD format
    unsigned char _reserved1;
  } TIME;
  struct
  {
    BUNION(r1, unsigned char,    //0x8           0x00            Control register 1
      WUCKSEL           , 3,    //0:2           0               Wakeup clock selection
      _reserved         , 1,      
      BYPSHAD           , 1,    //4             0               Bypass the shadow registers
      RATIO             , 1,    //5             0               System clock (SYSCLK) versus RTCCLK ratio
      FMT               , 1,    //6             0               Hour format: 0: 24 hour/day format
      _reserved1        , 1);
    BUNION(r2, unsigned char,    //0x9           0x00            Control register 2
      ALRAE             , 1,    //0             0               Alarm A enable
      _reserved         , 1,
      WUTE              , 1,    //2             0               Wakeup timer enable
      _reserved1        , 1,
      ALRAIE            , 1,    //4             0               Alarm A interrupt enable
      _reserved2        , 1,
      WUTIE             , 1,    //6             0               Wakeup timer interrupt enable
      _reserved3        , 1);
    BUNION(r3, unsigned char,    //0xA           0x00            Control register 3
      ADD1H             , 1,    //0             0               Add 1 hour (summer time change)
      SUB1H             , 1,    //1             0               Subtract 1 hour (winter time change)
      BCK               , 1,    //2             0               Backup
      COSEL             , 1,    //3             0               Calibration output selection
      POL               , 1,    //4             0               Output polarity 
      OSEL              , 2,    //5-6           0               Output selection
      COE               , 1);   //7             0               Calibration output enable
    unsigned char _reserved;
  } CR;
  struct
  {
    BUNION(r1, unsigned char,    //0xC           0x00            Initialization and status register 1
      const ALRAWF      , 1,    //0             0               Alarm A write flag
      const RECALPF     , 1,    //1             0               Recalibration pending Flag      
      const WUTWF       , 1,    //2             0               Wakeup timer write flag      
      const SHPF        , 1,    //3             0               Shift operation pending
      const INITS       , 1,    //4             0               Initialization status flag
      RSF               , 1,    //5             0               Registers synchronization flag
      const INITF       , 1,    //6             0               Initialization flag
      INIT              , 1);   //7             0               Initialization mode
    BUNION(r2, unsigned char,    //0xD           0x00            Initialization and status register 2
      ALRAF             , 1,    //0             0               Alarm A Flag
      _reserved         , 1,
      WUTF              , 1,    //2             0               Periodic wakeup flag
      _reserved1        , 2,
      TAMP1F            , 1,    //5             0               TAMPER1 detection flag
      TAMP2F            , 1,    //6             0               TAMPER2 detection flag
      TAMP3F            , 1);   //7             0               TAMPER3 detection flag
    unsigned char _reserved[2];
  } ISR;  
  struct
  {
    BRUNION_16x8(SPRER, , HIGH, LOW,    //0x10-0x11     0x00FF          Synchronous prescaler register
        PREDIV_S_12_8   , 5,    //0:4           0
        PREDIV_S_14_13  , 2,    //5-6           0
        _reserved       , 1,
        PREDIV_S_7_0    , 8);   //0:7           0xFF
    BUNION(APRER, unsigned char, //0x12          0x7F            Asynchronous prescaler register
      PREDIV_A          , 7,    //0:6           0x7F
      _reserved         , 1);
    unsigned char _reserved;
  } PRSC;
  RUNION_16x8(WUTR, ,       //0x14-0x15     0xFFFF          Wakeup timer register
    HIGH, LOW);
  unsigned char _reserved5;
  RUNION_16x8(SSR, const,   //0x17-0x18     0x0000          Subsecond register
    HIGH, LOW);
  unsigned char WPR;            //0x19          0x00            Write protection register  
  BRUNION_16x8(SHIFTR, , HIGH, LOW,     //0x1A-0x1B     0x0000          RTC shift control register  
      SUBFS_14_8        , 7,    //0:6           0               MSB to subtract a fraction of a second
      ADD1S             , 1,    //7             0               Add one second
      SUBFS_7_0         , 8);   //0:7           0               LSB to subtract a fraction of a second
  struct
  {
    BUNION(SECOND, unsigned char,//0x1C          0x00            ALRMAR1-Alarm A register 1
      SU                , 4,    //0:3           0               Second units in BCD format
      ST                , 3,    //4:6           0               Second tens in BCD format
      MSK1              , 1);   //7             0               Alarm A Seconds mask: 1:Seconds don’t care in alarm A comparison
    BUNION(MINUTE, unsigned char,//0x1D          0x00            ALRMAR1-Alarm A register 2
      MU                , 4,    //0:3           0               Minute units in BCD format
      MT                , 3,    //4:6           0               Minute tens in BCD format
      MSK2              , 1);   //7             0               Alarm A minutes mask
    BUNION(HOUR, unsigned char,  //0x1E          0x00            ALRMAR1-Alarm A register 3
      HU                , 4,    //0:3           0               Hour units in BCD format
      HT                , 2,    //4-5           0               Hour tens in BCD format
      PM                , 1,    //6             0               AM/PM notation
      MSK2              , 1);   //7             0               Alarm A hour mask
    BUNION(DATE, unsigned char,  //0x1F          0x00            ALRMAR4-Alarm A register 4;
      DU                , 4,    //0:3           0               Date units or Day in BCD format
      DT                , 2,    //4-5           0               Date tens in BCD format
      WDSEL             , 1,    //6             0               Week day selection
      MSK4              , 1);   //7             0               Alarm A Date mask
    unsigned char _reserved[4];
    RUNION_16x8(ALRMASSR, , //0x24-0x25     0x0000          Alarm A sub second register
              HIGH, LOW);
    BUNION(MASSMSKR, unsigned char,//0x26        0x00            Alarm A subsecond masking register
      MASKSS            , 4,    //0:3           0               Mask the most significant bits starting at this bit
      _reserved         , 4);
    unsigned char _reserved1[3];
  } ALARM;
  BRUNION_16x8(CALR, , HIGH, LOW,     //0x2A-0x2B     0x0000          Calibration register
      CALM_HIGH         , 1,    //0             0               MSB of calibration minus
      _reserved         , 4,
      CALW16            , 1,    //5             0               Use a16-second calibration cycle period
      CALW8             , 1,    //6             0               Use an 8-second calibration cycle period
      CALP              , 1,    //7             0               Increase of RTC frequency by 488.5 ppm
      CLAM_LOW          , 8);   //0:7           0               LSB of calibration minus

  struct
  {
    BUNION(TCR1, unsigned char,  //0x2C          0x00(P)         Tamper control register 1
      TAMPIE            , 1,    //0             0               Tamper interrupt enable
      TAMP1E            , 1,    //1             0               Tamper detection enable for tamper input 1 (TAMPER1)
      TAMP1TRG          , 1,    //2             0               Active level for tamper 1
      TAMP2E            , 1,    //3             0               Tamper detection enable for tamper input 2 (TAMPER2)
      TAMP2TRG          , 1,    //4             0               Active level for tamper input 2
      TAMP3E            , 1,    //5             0               Tamper detection enable for tamper input 3 (TAMPER3)
      TAMP3TRG          , 1,    //6             0               Active level for tamper input 3
      _reserved         , 1);
    BUNION(TCR2, unsigned char,  //0x2D          0x00(P)         Tamper control register 2
      TAMPFREQ          , 3,    //0:2           0               Tamper sampling frequency
      TAMPFLT           , 2,    //3-4           0               Tamper filter count
      TAMPPRCH          , 2,    //5-6           0               Tamper precharge duration
      TAMPPUDIS         , 1);   //7             0               TAMPER pull-up disable
  } TAMPER;
} RTC_TypeDef;
extern __no_init volatile RTC_TypeDef RTC;

typedef struct
{
  unsigned char Second;
  unsigned char Minute;
  unsigned char Hour;
  unsigned char WeekDay;
  unsigned char Date;
  unsigned char Month;
  unsigned char Year;
} DateTime_TypeDef;

typedef struct
{
  struct
  {
    unsigned char Second                : 1;
    unsigned char Minute                : 1;
    unsigned char Hour                  : 1;
    unsigned char Date_WeekDay          : 1;
    unsigned char _reserved             : 4;
  } Mask;
  unsigned char Second;
  unsigned char Minute;
  unsigned char Hour;
  struct
  {
    unsigned char Value                 : 7;
    unsigned char IsWeekday             : 1;
  } Date_WeekDay;
} Alarm_TypeDef;

void RTC_Init();
void RTC_ConfigTick(unsigned char IsSecond);
void RTC_SetTime(DateTime_TypeDef* DateTime);
void RTC_GetTime(DateTime_TypeDef* DateTime);
void RTC_Alarm(Alarm_TypeDef* Alarm);
void RTC_DisableAlarm();
void RTC_Weakup(unsigned short Time);
void RTC_DisableWeakup();

__weak void RTC_Alarm_ISR();
__weak void RTC_Weakup_ISR();
  
#endif