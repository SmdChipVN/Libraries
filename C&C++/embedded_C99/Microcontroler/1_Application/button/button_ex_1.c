#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
extern __no_init ButtonEx_TypeDef ButtonEx_f1[BUTTON_EX_QUANTITY_1];
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_1(BUTTON_EX, ButtonEx, ButtonEx_f1, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void ButtonEx_BeginStack_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_EX_QUANTITY_1; ButtonIndex++)
    ButtonEx_f1[ButtonIndex].HoldTime[0] = ButtonEx_f1[ButtonIndex].HoldTime[1] = 0;
  ButtonEx_BeginStack();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_ProcessIndexStack_1(reg8 ButtonIndex)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonEx_f1[ButtonIndex];
  if (ButtonEx_ProcessIndexStack(ButtonIndex))
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[0] < BUTTON_EX_PRESS_DOWN_TIME_1)
      {
        if (ButtonEx->PressCount < 10)
          ButtonEx->PressCount++;
      }
      ButtonEx->HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx->HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_1 + BUTTON_EX_PRESS_TIME_OUT_1))
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
void ButtonEx_ProcessStack_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_EX_QUANTITY_1; ButtonIndex++)
    ButtonEx_ProcessIndexStack_1(ButtonIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Begin_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_EX_QUANTITY_1; ButtonIndex++)
    ButtonEx_f1[ButtonIndex].HoldTime[0] = ButtonEx_f1[ButtonIndex].HoldTime[1] = 0;
  ButtonEx_Begin();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Process_mask(reg8 ButtonIndex)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonEx_f1[ButtonIndex];
  if (Process(ButtonIndex))
  {
    if (ButtonEx->Logic)
    {
      if (ButtonEx->HoldTime[0] < BUTTON_EX_PRESS_DOWN_TIME_1)
      {
        if (ButtonEx->PressCount < 10)
          ButtonEx->PressCount++;
      }
      ButtonEx->HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx->HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_1 + BUTTON_EX_PRESS_TIME_OUT_1))
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
void ButtonEx_Process_1()
{
  reg8 ButtonIndex;
  if (!count_sample)
  {
    for (ButtonIndex = 0; ButtonIndex < BUTTON_EX_QUANTITY_1; ButtonIndex++)
      Process_mask(ButtonIndex);
    count_sample = BUTTON_EX_SAMPLE_TIMES_1;
  }
  for (ButtonIndex = 0; ButtonIndex < BUTTON_EX_QUANTITY_1; ButtonIndex++)
    ButtonEx_f1[ButtonIndex].SumSample += ButtonEx_Read_1(ButtonIndex);
  count_sample--;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_ProcessIndex_1(reg8 ButtonIndex, reg8 CountSample)
{
  if (!CountSample)
  {
    Process_mask(ButtonIndex);
    CountSample = BUTTON_EX_SAMPLE_TIMES_1;
  }
  ButtonEx_f1[ButtonIndex].SumSample += ButtonEx_Read_1(ButtonIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Press_1(reg8 ButtonIndex, reg8 Times)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonEx_f1[ButtonIndex];
  if (ButtonEx->HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_1 + BUTTON_EX_PRESS_TIME_OUT_1))
  {
    reg8 ret = Times > 10 ? ButtonEx->PressCount : (ButtonEx->PressCount == Times);
    if (ret) 
      ButtonEx->PressCount = 0;
    return ret;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Check_1(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus)
{
  return ButtonEx_Check(ButtonIndex, Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Hold_1(reg8 ButtonIndex, reg8 Status, reg8 HoldTime, reg8 Once)
{
  ButtonEx_TypeDef* ButtonEx = &ButtonEx_f1[ButtonIndex];
  reg8 hold_time = ButtonEx->HoldTime[--Status];
  if (hold_time == 0xFF)
    return 0;
  if ((hold_time >= HoldTime) && (ButtonEx->Logic == Status))
  {
    ButtonEx->HoldTime[Status] = BUTTON_EX_PRESS_DOWN_TIME_1 | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_HoldAccel_1(reg8 ButtonIndex, reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_1
  #define BUTTON_ACCEL_MAX_HOLD_TIME_1  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_1  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_1       Accel->SubStep
#endif
  ButtonEx_TypeDef* ButtonEx = &ButtonEx_f1[ButtonIndex];
  if (ButtonEx->Logic == --Status)
  {
    reg8 hold_time = *HoldTime;
    if (ButtonEx->HoldTime[Status] >= hold_time)
    {
      ButtonEx->HoldTime[Status] = BUTTON_EX_PRESS_DOWN_TIME_1;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_1 + BUTTON_ACCEL_SUB_STEP_1))
        hold_time -= BUTTON_ACCEL_SUB_STEP_1;
      *HoldTime = hold_time;
      return 1;
    }
  }
  else
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_1;
  return 0;
}