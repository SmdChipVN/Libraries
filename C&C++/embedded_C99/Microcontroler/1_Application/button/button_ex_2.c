#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_2(BUTTON_EX, ButtonEx, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void ButtonEx_BeginStack_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonExFunction->ButtonExIndex];
  ButtonEx->HoldTime[0] = ButtonEx->HoldTime[1] = 0;
  ButtonEx_BeginStack(ButtonExFunction);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_ProcessStack_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, reg8 PressTimeOut)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonExFunction->ButtonExIndex];
  if (ButtonEx_ProcessStack(ButtonExFunction))
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[0] < ButtonExFunction->PressDownTime)
      {
        if (ButtonEx->PressCount < 10)
          ButtonEx->PressCount++;
      }
      ButtonEx->HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx->HoldTime[1] >= (unsigned char)(ButtonExFunction->PressDownTime + PressTimeOut))
        ButtonEx->PressCount = 0;
      ButtonEx->HoldTime[0] = 0;
    }
  }
  else
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[1] < 0xFE)
        ButtonEx->HoldTime[1]++;
    }
    else if (ButtonEx->HoldTime[0] < 0xFE)
        ButtonEx->HoldTime[0]++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Begin_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonExFunction->ButtonExIndex];
  ButtonEx->HoldTime[0] = ButtonEx->HoldTime[1] = 0;
  ButtonEx_Begin(ButtonExFunction);
  return ButtonExFunction->SampleTimes;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Process_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, unsigned char* CountSample, reg8 PressTimeOut)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonExFunction->ButtonExIndex];
  if (ButtonEx_Process(ButtonExFunction, CountSample))
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[0] < ButtonExFunction->PressDownTime)
      {
        if (ButtonEx->PressCount < 10)
          ButtonEx->PressCount++;
      }
      ButtonEx->HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx->HoldTime[1] >= (unsigned char)(ButtonExFunction->PressDownTime + PressTimeOut))
        ButtonEx->PressCount = 0;
      ButtonEx->HoldTime[0] = 0;
    }
  }
  else
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[1] < 0xFE)
        ButtonEx->HoldTime[1]++;
    }
    else if (ButtonEx->HoldTime[0] < 0xFE)
        ButtonEx->HoldTime[0]++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Press_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, reg8 Times)
{
  ButtonEx_TypeDef* ButtonEx = ButtonExFunction->ButtonEx;
  if (ButtonEx->HoldTime[1] >= ButtonExFunction->PressDownTime)
  {
    reg8 ret = Times > 10 ? ButtonEx->PressCount : (ButtonEx->PressCount == Times);
    if (ret) 
      ButtonEx->PressCount = 0;
    return ret;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Check_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, reg8 Status, reg8 ClearStatus)
{
  return ButtonEx_Check(&ButtonExFunction->ButtonEx[ButtonExFunction->ButtonExIndex], Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Hold_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, reg8 Status, reg8 HoldTime, reg8 Once)
{
  ButtonEx_TypeDef* ButtonEx = ButtonExFunction->ButtonEx;
  reg8 hold_time = ButtonEx->HoldTime[--Status];
  if (hold_time == 0xFF)
    return 0;
  if ((hold_time >= HoldTime) && (ButtonEx->Logic == Status))
  {
    ButtonEx->HoldTime[Status] = ButtonExFunction->PressDownTime | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_HoldAccel_2(const ButtonExFunction_TypeDef __gptr* ButtonExFunction, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_2
  #define BUTTON_ACCEL_MAX_HOLD_TIME_2  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_2  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_2       Accel->SubStep
#endif
  ButtonEx_TypeDef* ButtonEx = ButtonExFunction->ButtonEx;
  if (ButtonEx->Logic == --Status)
  {
    reg8 hold_time = *HoldTime;
    if (ButtonEx->HoldTime[Status] >= hold_time)
    {
      ButtonEx->HoldTime[Status] = ButtonExFunction->PressDownTime;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_2 + BUTTON_ACCEL_SUB_STEP_2))
        hold_time -= BUTTON_ACCEL_SUB_STEP_2;
      *HoldTime = hold_time;
      return 1;
    }
  }
  else
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_2;
  return 0;
}