#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_2(BUTTON, Button, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void Button_BeginStack_2(const ButtonFunction_TypeDef __gptr* ButtonFunction)
{
  Button_BeginStack(ButtonFunction);
  ButtonFunction->Button[ButtonFunction->ButtonIndex].HoldTime = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessStack_2(const ButtonFunction_TypeDef __gptr* ButtonFunction)
{
  reg8 logic_changed = Button_ProcessStack(ButtonFunction);
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonFunction->ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Begin_2(const ButtonFunction_TypeDef __gptr* ButtonFunction)
{
  Button_Begin(ButtonFunction);
  ButtonFunction->Button[ButtonFunction->ButtonIndex].HoldTime = 0;
  return ButtonFunction->SampleTimes;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Process_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, unsigned char* CountSample)
{
  reg8 logic_changed = Button_Process(ButtonFunction, CountSample);
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonFunction->ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Press_2(const ButtonFunction_TypeDef __gptr* ButtonFunction)
{
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonFunction->ButtonIndex];
  if ((Button->Status & BUTTON_STATUS_UP) && Button->HoldTime < ButtonFunction->PressDownTime)
  {
    Button->Status = 0;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Check_2(Button_TypeDef* Button, reg8 Status, reg8 ClearStatus)
{
  return Button_Check(Button, Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Hold_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, reg8 HoldTime, reg8 Once)
{
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonFunction->ButtonIndex];
  reg8 hold_time = Button->HoldTime;
  if (hold_time == 0xFF)
    return 0;
  if ((hold_time >= HoldTime) && !Button->Logic)
  {
    Button->HoldTime = ButtonFunction->PressDownTime | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_HoldAccel_2(const ButtonFunction_TypeDef __gptr* ButtonFunction, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_2
  #define BUTTON_ACCEL_MAX_HOLD_TIME_2  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_2  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_2       Accel->SubStep
#endif
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonFunction->ButtonIndex];
  if (Button->Logic)
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_2;
  else 
  {
    reg8 hold_time = *HoldTime;
    if (Button->HoldTime >= hold_time)
    {
      Button->HoldTime = ButtonFunction->PressDownTime;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_2 + BUTTON_ACCEL_SUB_STEP_2))
        hold_time -= BUTTON_ACCEL_SUB_STEP_2;
      *HoldTime = hold_time;
      return 1;
    }
  }
  return 0;
}