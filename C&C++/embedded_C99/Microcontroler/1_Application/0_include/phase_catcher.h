/*
+) NOTE:
+) Common use:
    #define PhaseCatcher_PowerProcess(PhaseMode, PowerPercent, OpenFunction, CloseFunction)
      //must import phase_catcher.c
      +) Param:
          PhaseMode: 0, 1, 2, 3
          PowerPercent: 0:100
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
+) Example:
//==============================================================================================================================================================
MODE 0:
  +) Description:
      Capture at rise and fall edge
  +) Config:
      #define PHASE_CATCHER_READ_0()          GPIOB.IDR.BITS.b7
      #define PHASE_CATCHER_WIDTH_TIME_0      10000     //us
      #define PHASE_CATCHER_TRIG_TIME_0       40        //us, make sure (WIDTH_TIME / TRIG_TIME) <= 255 - (200 / TRIG_TIME)
  +) Declare:
      __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f0;
      void PhaseCatch_0();                              //process in interrupt
  +) Using:
      void PhaseCatcher_Begin_0();
      void PhaseCatcher_Catch_0();                      //process in interrupt
MODE 1:
  +) Description:
      Capture at rise or fall edge, then offset width time to export next catch event
  +) Config:
      #define PHASE_CATCHER_READ_1()          GPIOB.IDR.BITS.b7
      #define PHASE_CATCHER_WIDTH_TIME_1      10000     //us
      #define PHASE_CATCHER_TRIG_TIME_1       40        //us, make sure (WIDTH_TIME / TRIG_TIME) <= 255 - (200 / TRIG_TIME)
      #define PHASE_CATCHER_EDGE_1            1         //1: rise edge, 0: down edge
  +) Declare:
      __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f1;
      void PhaseCatch_1();                              //process in interrupt
  +) Using:
      void PhaseCatcher_Begin_1();
      void PhaseCatcher_Catch_1();                      //process in interrupt
MODE 2:
  +) Description:
      Like mode 0 but have rise/fall edge offset
  +) Config:
      #define PHASE_CATCHER_READ_2()          GPIOB.IDR.BITS.b7
      #define PHASE_CATCHER_WIDTH_TIME_2      10000     //us
      #define PHASE_CATCHER_TRIG_TIME_2       40        //us, make sure (WIDTH_TIME / TRIG_TIME) <= 255 - (200 / TRIG_TIME)
      #define PHASE_CATCHER_OFFSET_HIGH_2     0         //
      #define PHASE_CATCHER_OFFSET_LOW_2      0         //
  +) Declare:
      __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f2;
      void PhaseCatch_2();                              //process in interrupt
  +) Using:
      void PhaseCatcher_Begin_2();
      void PhaseCatcher_Catch_2();                      //process in interrupt
MODE 3:
  +) Description:
      Like mode 1 but have edge offset
  +) Config:
      #define PHASE_CATCHER_READ_3()          GPIOB_BITBAND.IDR.b7
      #define PHASE_CATCHER_WIDTH_TIME_3      10000     //us
      #define PHASE_CATCHER_TRIG_TIME_3       40        //us, make sure (WIDTH_TIME / TRIG_TIME) <= 255 - (200 / TRIG_TIME)
      #define PHASE_CATCHER_EDGE_3            1         //1: rise edge, 0: down edge
      #define PHASE_CATCHER_OFFSET_3          0
  +) Declare:
      __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f3;
      void PhaseCatch_3();                              //process in interrupt
  +) Using:
      void PhaseCatcher_Begin_3();
      void PhaseCatcher_Catch_3();                      //process in interrupt
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
MODE object:
  +) Config:
  +) Declare:
  +) Using:
      void PhaseCatcher_Begin(PhaseCatcher_TypeDef* PhaseCatcher, reg8 (ReadSignal)());
      void PhaseCatcher_Catch(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction);
      void PhaseCatcher_CatchEdge(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction);
      reg8 PhaseCatcher_PowerProcessAdvanced(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction, reg8 PowerPercent);
        return 0: not impact
               1: open
               2: close
*/
#ifndef _PHASE_CATCHER_H_
#define _PHASE_CATCHER_H_

#include <common.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef enum
{
  PHASE_CATCHER_STATUS_IDLE             = 0,
  PHASE_CATCHER_STATUS_AC_ERROR         = 1,
  PHASE_CATCHER_STATUS_READY            = 2,
  PHASE_CATCHER_STATUS_CALIB            = 4,
} PHASE_CATCHER_STATUS;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  PHASE_CATCHER_STATUS Status;
  struct
  {
    unsigned char Logic;
    unsigned char SumSample;
    unsigned char Stage;
    struct
    {
      unsigned char Time;
      unsigned char Error;
      unsigned char Ok;
    } Counter;
  } Capture;
} PhaseCatcher_TypeDef;
//==============================================================================================================================================================
extern __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f0;
void PhaseCatcher_Begin_0();
void PhaseCatcher_Catch_0();                           //process in interrupt
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
extern __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f1;
void PhaseCatcher_Begin_1();
void PhaseCatcher_Catch_1();                           //process in interrupt
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
extern __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f2;
void PhaseCatcher_Begin_2();
void PhaseCatcher_Catch_2();                           //process in interrupt
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
extern __no_init PhaseCatcher_TypeDef __data PhaseCatcher_f3;
void PhaseCatcher_Begin_3();
void PhaseCatcher_Catch_3();                           //process in interrupt
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PhaseCatcher_PowerProcess(PhaseMode, PowerPercent, OpenFunction, CloseFunction)\
if (PowerPercent && PhaseCatcher_f##PhaseMode.Status == PHASE_CATCHER_STATUS_READY)\
{\
  reg8 point = PhaseCatcher_PowerOpenPoint[PowerPercent] * (PHASE_CATCHER_WIDTH_TIME_##PhaseMode / PHASE_CATCHER_TRIG_TIME_##PhaseMode) / 200;\
  if (PhaseCatcher_f##PhaseMode.Capture.Counter.Time == point)\
  {\
    OpenFunction\
  }\
  else if (PhaseCatcher_f##PhaseMode.Capture.Counter.Time == point + 4)\
  {\
    CloseFunction\
  }\
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
extern const unsigned char __code PhaseCatcher_PowerOpenPoint[101];
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
typedef struct
{
  reg8 (*ReadSignal)();
  void (*PhaseCatch)();
  struct
  {
    unsigned char Offset;
    unsigned char Time;
  }* Counter;
  struct
  {
    unsigned char MinWidth;
    unsigned char MaxWidth;
    unsigned char WidthTime;
    unsigned char CatchAt;
  } Edge;
  unsigned char Offset[2];
} PhaseCatcherFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Begin(PhaseCatcher_TypeDef* PhaseCatcher, reg8 (ReadSignal)());
void PhaseCatcher_Catch(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction);
void PhaseCatcher_CatchEdge(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction);
reg8 PhaseCatcher_PowerProcessAdvanced(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction, reg8 PowerPercent);

#endif