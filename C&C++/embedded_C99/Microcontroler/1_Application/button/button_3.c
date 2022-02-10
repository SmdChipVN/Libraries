#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_3(BUTTON, Button, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void Button_BeginStack_3(const ButtonFunction_TypeDef __code* ButtonFunction)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonFunction->NumberOfButton; ButtonIndex++)
    ButtonFunction->Button[ButtonIndex].HoldTime = 0;
  Button_BeginStack(ButtonFunction);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessIndexStack_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex)
{
  reg8 logic_changed = Button_ProcessIndexStack(ButtonFunction, ButtonIndex);
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessStack_3(const ButtonFunction_TypeDef __code* ButtonFunction)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonFunction->NumberOfButton; ButtonIndex++)
    Button_ProcessIndexStack_3(ButtonFunction, ButtonIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Begin_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample)
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < ButtonFunction->NumberOfButton; ButtonIndex++)
    ButtonFunction->Button[ButtonIndex].HoldTime = 0;
  Button_Begin(ButtonFunction, CountSample);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Process_mask(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex)
{
  reg8 logic_changed = Process(ButtonFunction, ButtonIndex);
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Process_3(const ButtonFunction_TypeDef __code* ButtonFunction, unsigned char* CountSample)
{
  reg8 count_sample = *CountSample;
  if (!count_sample)
  {
    reg8 ButtonIndex;
    for (ButtonIndex = 0; ButtonIndex < ButtonFunction->NumberOfButton; ButtonIndex++)
      Process_mask(ButtonFunction, ButtonIndex);
    count_sample = ButtonFunction->SampleTimes;
  }
  {
    reg8(*button_read)(reg8 ButtonIndex) = ButtonFunction->ButtonRead;
    reg8 ButtonIndex;
    for (ButtonIndex = 0; ButtonIndex < ButtonFunction->NumberOfButton; ButtonIndex++)
      ButtonFunction->Button[ButtonIndex].SumSample += button_read(ButtonIndex);
  }
  *CountSample = count_sample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_ProcessIndex_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 CountSample)
{
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  if (!CountSample)
  {
    Process_mask(ButtonFunction, ButtonIndex);
    CountSample = ButtonFunction->SampleTimes;
  }
  Button->SumSample += ButtonFunction->ButtonRead(ButtonIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Press_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex)
{
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  if ((Button->Status & BUTTON_STATUS_UP) && (Button->HoldTime < ButtonFunction->PressDownTime))
  {
    Button->Status = 0;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Check_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 Status, reg8 ClearStatus)
{
  return Button_Check(ButtonFunction, ButtonIndex, Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Hold_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, reg8 HoldTime, reg8 Once)
{
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  reg8 hold_time = Button->HoldTime;
  if (hold_time == 0xFF)
    return 0;
  if ((hold_time >= HoldTime) && !Button->Logic)
  {
    Button->HoldTime = BUTTON_PRESS_DOWN_TIME_1 | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_HoldAccel_3(const ButtonFunction_TypeDef __code* ButtonFunction, reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_3
  #define BUTTON_ACCEL_MAX_HOLD_TIME_3  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_3  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_3       Accel->SubStep
#endif
  Button_TypeDef* Button = &ButtonFunction->Button[ButtonIndex];
  if (Button->Logic)
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_3;
  else 
  {
    reg8 hold_time = *HoldTime;
    if (Button->HoldTime >= hold_time)
    {
      Button->HoldTime = ButtonFunction->PressDownTime;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_3 + BUTTON_ACCEL_SUB_STEP_3))
        hold_time -= BUTTON_ACCEL_SUB_STEP_3;
      *HoldTime = hold_time;
      return 1;
    }
  }
  return 0;
}