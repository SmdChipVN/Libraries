/*
+) NOTE:
    Button.Status = BUTTON_STATUS_DOWN (BIT0) or BUTTON_STATUS_UP (BIT1)
    Button_Check.ClearStatus = BIT2
    Button_Hold.Once = 0xFF
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
+) for Button_HoldAccel, maybe re-define to improve function's speed (where x is MODE)
    #define BUTTON_ACCEL_MAX_HOLD_TIME_x    100
    #define BUTTON_ACCEL_MIN_HOLD_TIME_x    20        //min time trigger is (20 - PRESS_DOWN_TIME)
    #define BUTTON_ACCEL_SUB_STEP_x         20
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
+) Example:
    reg8 Button_Read(reg8 ButtonIndex);
    {
      switch (ButtonIndex)
      {
        case 0: return GPIOB.IDR.BITS.b7;
      }
      return 2;
    }
    static const ButtonFunction_TypeDef __code ButtonFunction = 
    {
        .Button = ,
        .ButtonEx = ,
      .ButtonRead = Button_Read,
      .SampleTimes = 5,
      .SampleDivider = 4,
      .PressDownTime = 10,
      .NumberOfButton = 2,
    };
    static const ButtonAccel_TypeDef __code ButtonAccel = {.MaxHoldTime = 53, .MinHoldTime = 13, .SubStep = 10};
//==============================================================================================================================================================
MODE 0:
  +) Config:
      #define BUTTON_SAMPLE_TIMES_0            5
      #define BUTTON_SAMPLE_DIVIDER_0          4
      #define BUTTON_PRESS_DOWN_TIME_0         10
      #define BUTTON_READ_0()                  GPIOB.IDR.BITS.b7
  +) Declare:
      __no_init Button_TypeDef Button_f0;
  +) Using:
      void Button_BeginStack_0();
      void Button_ProcessStack_0();

      void Button_Begin_0();
      void Button_Process_0();
      reg8 Button_Press_0();
      reg8 Button_Check_0(reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_0(reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_0(const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
MODE 1:
  +) Config:
      #define BUTTON_QUANTITY_1                2
      #define BUTTON_SAMPLE_TIMES_1            5
      #define BUTTON_SAMPLE_DIVIDER_1          4
      #define BUTTON_PRESS_DOWN_TIME_1         10
  +) Declare:
      __no_init Button_TypeDef Button_f1[BUTTON_QUANTITY_1];
      reg8 Button_Read_1(reg8 ButtonIndex);
  +) Using:
      void Button_BeginStack_1();
      void Button_ProcessIndexStack_1(reg8 ButtonIndex);
      void Button_ProcessStack_1();

      void Button_Begin_1();
      reg8 Button_ProcessIndex_1(reg8 ButtonIndex, reg8 CountSample);
      void Button_Process_1();
      reg8 Button_Press_1(reg8 ButtonIndex);
      reg8 Button_Check_1(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_1(reg8 ButtonIndex, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_1(reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
MODE 2:
//==============================================================================================================================================================
  +) Config:
  +) Declare:
  +) Using:     (un-use: ButtonFunction->NumberOfButton)
      void Button_BeginStack_2(const ButtonFunction_TypeDef __code* ButtonFunction);
      void Button_ProcessStack_2(const ButtonFunction_TypeDef __code* ButtonFunction);

      reg8 Button_Begin_2(const ButtonFunction_TypeDef __code* ButtonFunction);
      void Button_Process_2(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample);
      reg8 Button_Press_2(const ButtonFunction_TypeDef __code* ButtonFunction);
      reg8 Button_Check_2(Button_TypeDef* Button, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_2(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_2(const ButtonFunction_TypeDef __code* ButtonFunction, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
MODE 3:
//==============================================================================================================================================================
  +) Config:
  +) Declare:
  +) Using:
      void Button_BeginStack_3(const ButtonFunction_TypeDef __code* ButtonFunction);
      void Button_ProcessIndexStack_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex);
      void Button_ProcessStack_3(const ButtonFunction_TypeDef __code* ButtonFunction);

      void Button_Begin_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample);
      reg8 Button_ProcessIndex_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 CountSample);
      void Button_Process_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample);
      reg8 Button_Press_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex);
      reg8 Button_Check_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
MODE EX 0:
  +) Config:
      #define BUTTON_EX_SAMPLE_TIMES_0         5
      #define BUTTON_EX_SAMPLE_DIVIDER_0       4
      #define BUTTON_EX_PRESS_DOWN_TIME_0      10
      #define BUTTON_EX_PRESS_TIME_OUT_0       10
      #define BUTTON_EX_READ_0()               GPIOB.IDR.BITS.b7
  +) Declare:
      __no_init ButtonEx_TypeDef ButtonEx_f4;
  +) Using:
      void Button_BeginStack_4();
      void Button_ProcessStack_4();

      void Button_Begin_4();
      void Button_Process_4();
      reg8 Button_Press_4(reg8 Times);
      reg8 Button_Check_4(reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_4(reg8 Status, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_4(reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
MODE 5:
  +) Config:
      #define BUTTON_EX_QUANTITY_5             2
      #define BUTTON_EX_SAMPLE_TIMES_5         5
      #define BUTTON_EX_SAMPLE_DIVIDER_5       4
      #define BUTTON_EX_PRESS_DOWN_TIME_5      10
      #define BUTTON_EX_PRESS_TIME_OUT_5       10
  +) Declare:
      __no_init ButtonEx_TypeDef ButtonEx_f5[BUTTON_EX_QUANTITY_5];
      reg8 ButtonEx_Read_5(reg8 ButtonIndex);
  +) Using:
      void Button_BeginStack_5();
      void Button_ProcessIndexStack_5(reg8 ButtonIndex);
      void Button_ProcessStack_5();

      void Button_Begin_5();
      reg8 Button_ProcessIndex_5(reg8 ButtonIndex, reg8 CountSample);
      void Button_Process_5();
      reg8 Button_Press_5(reg8 ButtonIndex, reg8 Times);
      reg8 Button_Check_5(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_5(reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_5(reg8 ButtonIndex, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
MODE 6:
  +) Config:
  +) Declare:
  +) Using:     (un-use: ButtonExFunction->NumberOfButton)
      void Button_BeginStack_6(const ButtonFunction_TypeDef __code* ButtonExFunction);
      void Button_ProcessStack_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 PressTimeOut);

      reg8 Button_Begin_6(const ButtonFunction_TypeDef __code* ButtonExFunction);
      reg8 Button_Process_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 CountSample, reg8 PressTimeOut);
      reg8 Button_Press_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 Times);
      reg8 Button_Check_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_6(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
MODE 7:
  +) Config:
  +) Declare:
  +) Using:
      void Button_BeginStack_7(const ButtonFunction_TypeDef __code* ButtonExFunction);
      void Button_ProcessIndexStack_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 PressTimeOut);
      void Button_ProcessStack_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 PressTimeOut);

      void Button_Begin_7(const ButtonFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample);
      reg8 Button_ProcessIndex_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 CountSample, reg8 PressTimeOut);
      void Button_Process_7(const ButtonFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample, reg8 PressTimeOut);
      reg8 Button_Press_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Times);
      reg8 Button_Check_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
      reg8 Button_Hold_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once);
      reg8 Button_HoldAccel_7(const ButtonFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_

#define BUTTON_STATUS_DOWN      BIT0    //1, voltage: 0, clear -> BIT0 | BIT2
#define BUTTON_STATUS_UP        BIT1    //2, voltage: VCC, clear -> BIT1 | BIT2
#define BUTTON_CLEAR_STATUS     BIT2
#define BUTTON_CLEAR_HOLD       0xFF

#include <common.h>
typedef struct
{
  unsigned char MaxHoldTime;
  unsigned char MinHoldTime;
  unsigned char SubStep;
} ButtonAccel_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned char Logic;
  unsigned char SumSample;
  unsigned char Status;
  unsigned char HoldTime;
} Button_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned char Logic;
  unsigned char SumSample;
  unsigned char Status;
  unsigned char PressCount;
  unsigned char HoldTime[2];
} ButtonEx_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  Button_TypeDef* Button;
  reg8 (*ButtonRead)(reg8 ButtonIndex);
  unsigned char SampleTimes;
  unsigned char SampleDivider;
  unsigned char PressDownTime;
  union
  {
    unsigned char ButtonIndex;
    unsigned char NumberOfButton;
  };
} ButtonFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  ButtonEx_TypeDef* ButtonEx;
  reg8 (*ButtonExRead)(reg8 ButtonExIndex);
  unsigned char SampleTimes;
  unsigned char SampleDivider;
  unsigned char PressDownTime;
  union
  {
    unsigned char ButtonExIndex;
    unsigned char NumberOfButtonEx;
  };
} ButtonExFunction_TypeDef;
//==============================================================================================================================================================
void Button_BeginStack_0();
void Button_ProcessStack_0();

void Button_Begin_0();
void Button_Process_0();
reg8 Button_Press_0();
reg8 Button_Check_0(reg8 Status, reg8 ClearStatus);
reg8 Button_Hold_0(reg8 HoldTime, reg8 Once);
reg8 Button_HoldAccel_0(const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_BeginStack_1();
void Button_ProcessIndexStack_1(reg8 ButtonIndex);
void Button_ProcessStack_1();

void Button_Begin_1();
reg8 Button_ProcessIndex_1(reg8 ButtonIndex, reg8 CountSample);
void Button_Process_1();
reg8 Button_Press_1(reg8 ButtonIndex);
reg8 Button_Check_1(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
reg8 Button_Hold_1(reg8 ButtonIndex, reg8 HoldTime, reg8 Once);
reg8 Button_HoldAccel_1(reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_BeginStack_2(const ButtonFunction_TypeDef __gptr* ButtonFunction);
void Button_ProcessStack_2(const ButtonFunction_TypeDef __gptr* ButtonFunction);

reg8 Button_Begin_2(const ButtonFunction_TypeDef __gptr* ButtonFunction);
void Button_Process_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, unsigned char* CountSample);
reg8 Button_Press_2(const ButtonFunction_TypeDef __gptr* ButtonFunction);
reg8 Button_Check_2(Button_TypeDef* Button, reg8 Status, reg8 ClearStatus);
reg8 Button_Hold_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, reg8 HoldTime, reg8 Once);
reg8 Button_HoldAccel_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_BeginStack_3(const ButtonFunction_TypeDef __code* ButtonFunction);
void Button_ProcessIndexStack_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex);
void Button_ProcessStack_3(const ButtonFunction_TypeDef __code* ButtonFunction);

void Button_Begin_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample);
reg8 Button_ProcessIndex_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 CountSample);
void Button_Process_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample);
reg8 Button_Press_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex);
reg8 Button_Check_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
reg8 Button_Hold_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 HoldTime, reg8 Once);
reg8 Button_HoldAccel_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//==============================================================================================================================================================
void ButtonEx_BeginStack_0();
void ButtonEx_ProcessStack_0();

void ButtonEx_Begin_0();
void ButtonEx_Process_0();
reg8 ButtonEx_Press_0(reg8 Times);
reg8 ButtonEx_Check_0(reg8 Status, reg8 ClearStatus);
reg8 ButtonEx_Hold_0(reg8 Status, reg8 HoldTime, reg8 Once);
reg8 ButtonEx_HoldAccel_0(reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_BeginStack_1();
void ButtonEx_ProcessIndexStack_1(reg8 ButtonIndex);
void ButtonEx_ProcessStack_1();

void ButtonEx_Begin_1();
reg8 ButtonEx_ProcessIndex_1(reg8 ButtonIndex, reg8 CountSample);
void ButtonEx_Process_1();
reg8 ButtonEx_Press_1(reg8 ButtonIndex, reg8 Times);
reg8 ButtonEx_Check_1(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
reg8 ButtonEx_Hold_1(reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once);
reg8 ButtonEx_HoldAccel_1(reg8 ButtonIndex, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_BeginStack_2(const ButtonExFunction_TypeDef __code* ButtonExFunction);
void ButtonEx_ProcessStack_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 PressTimeOut);

reg8 ButtonEx_Begin_2(const ButtonExFunction_TypeDef __code* ButtonExFunction);
void ButtonEx_Process_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample, reg8 PressTimeOut);
reg8 ButtonEx_Press_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Times);
reg8 ButtonEx_Check_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 ClearStatus);
reg8 ButtonEx_Hold_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 HoldTime, reg8 Once);
reg8 ButtonEx_HoldAccel_2(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_BeginStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction);
void ButtonEx_ProcessIndexStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 PressTimeOut);
void ButtonEx_ProcessStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 PressTimeOut);

void ButtonEx_Begin_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample);
reg8 ButtonEx_ProcessIndex_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 CountSample, reg8 PressTimeOut);
void ButtonEx_Process_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample, reg8 PressTimeOut);
reg8 ButtonEx_Press_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Times);
reg8 ButtonEx_Check_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus);
reg8 ButtonEx_Hold_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once);
reg8 ButtonEx_HoldAccel_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime);

#endif