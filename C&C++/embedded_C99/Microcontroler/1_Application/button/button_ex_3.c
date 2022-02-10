#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_3(BUTTON_EX, ButtonEx, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void ButtonEx_BeginStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonExFunction->NumberOfButtonEx; ButtonIndex++)
  {
    ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonIndex];
    ButtonEx->HoldTime[0] = ButtonEx->HoldTime[1] = 0;
  }
  ButtonEx_BeginStack(ButtonExFunction);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_ProcessIndexStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 PressTimeOut)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonIndex];
  if (ButtonEx_ProcessIndexStack(ButtonExFunction, ButtonIndex))
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
void ButtonEx_ProcessStack_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 PressTimeOut)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonExFunction->NumberOfButtonEx; ButtonIndex++)
    ButtonEx_ProcessIndexStack_3(ButtonExFunction, ButtonIndex, PressTimeOut);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Begin_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonExFunction->NumberOfButtonEx; ButtonIndex++)
  {
    ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonIndex];
    ButtonEx->HoldTime[0] = ButtonEx->HoldTime[1] = 0;
  }
  ButtonEx_Begin(ButtonExFunction, CountSample);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Process_mask(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 PressTimeOut)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonExFunction->ButtonEx[ButtonIndex];
  if (Process(ButtonExFunction, ButtonIndex))
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
    if (ButtonEx->Logic == BUTTON_STATUS_UP)
    {
      if (ButtonEx->HoldTime[1] < 0xFE)
        ButtonEx->HoldTime[1]++;
    }
    else if (ButtonEx->HoldTime[0] < 0xFE)
        ButtonEx->HoldTime[0]++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Process_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, unsigned char* CountSample, reg8 PressTimeOut)
{
  reg8 count_sample = *CountSample;
  reg8 number_of_button = ButtonExFunction->NumberOfButtonEx;
  if (!count_sample)
  {
    reg8 ButtonIndex;
    for (ButtonIndex = 0; ButtonIndex < number_of_button; ButtonIndex++)
      Process_mask(ButtonExFunction, ButtonIndex, PressTimeOut);
    count_sample = ButtonExFunction->SampleTimes;
  }
  {
    reg8 ButtonIndex;
    reg8 (*button_read)(reg8 ButtonIndex) = ButtonExFunction->ButtonExRead;
    for (ButtonIndex = 0; ButtonIndex < number_of_button; ButtonIndex++)
      ButtonExFunction->ButtonEx[ButtonIndex].SumSample += button_read(ButtonIndex);
  }
  *CountSample = count_sample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_ProcessIndex_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 CountSample, reg8 PressTimeOut)
{
  if (!CountSample)
  {
    Process_mask(ButtonExFunction, ButtonIndex, PressTimeOut);
    CountSample = ButtonExFunction->SampleTimes;
  }
  ButtonExFunction->ButtonEx[ButtonIndex].SumSample += ButtonExFunction->ButtonExRead(ButtonIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Press_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Times)
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
reg8 ButtonEx_Check_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus)
{
  return ButtonEx_Check(ButtonExFunction, ButtonIndex, Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Hold_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once)
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
reg8 ButtonEx_HoldAccel_3(const ButtonExFunction_TypeDef __code* ButtonExFunction, reg8 Status, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_3
  #define BUTTON_ACCEL_MAX_HOLD_TIME_3  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_3  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_3       Accel->SubStep
#endif
  ButtonEx_TypeDef* ButtonEx = ButtonExFunction->ButtonEx;
  if (ButtonEx->Logic == --Status)
  {
    reg8 hold_time = *HoldTime;
    if (ButtonEx->HoldTime[Status] >= hold_time)
    {
      ButtonEx->HoldTime[Status] = ButtonExFunction->PressDownTime;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_3 + BUTTON_ACCEL_SUB_STEP_3))
        hold_time -= BUTTON_ACCEL_SUB_STEP_3;
      *HoldTime = hold_time;
      return 1;
    }
  }
  else
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_3;
  return 0;
}