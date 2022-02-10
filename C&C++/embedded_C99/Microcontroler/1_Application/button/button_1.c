#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
extern __no_init Button_TypeDef Button_f1[BUTTON_QUANTITY_1];
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_1(BUTTON, Button, Button_f1, HighBitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void Button_BeginStack_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_QUANTITY_1; ButtonIndex++)
    Button_f1[ButtonIndex].HoldTime = 0;
  Button_BeginStack();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessIndexStack_1(reg8 ButtonIndex)
{
  reg8 logic_changed = Button_ProcessIndexStack(ButtonIndex);
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessStack_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_QUANTITY_1; ButtonIndex++)
    Button_ProcessIndexStack_1(ButtonIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Begin_1()
{
  reg8 ButtonIndex;
  for (ButtonIndex = 0; ButtonIndex < BUTTON_QUANTITY_1; ButtonIndex++)
    Button_f1[ButtonIndex].HoldTime = 0;
  Button_Begin();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Process_mask(reg8 ButtonIndex)
{
  reg8 logic_changed = Process(ButtonIndex);
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if (!Button->Logic)
  {
    if (logic_changed)
      Button->HoldTime = 0;
    else if (Button->HoldTime < 0xFE)
      Button->HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Process_1()
{
  reg8 ButtonIndex;
  if (!count_sample)
  {
    for (ButtonIndex = 0; ButtonIndex < BUTTON_QUANTITY_1; ButtonIndex++)
      Process_mask(ButtonIndex);
    count_sample = BUTTON_SAMPLE_TIMES_1;
  }
  for (ButtonIndex = 0; ButtonIndex < BUTTON_QUANTITY_1; ButtonIndex++)
    Button_f1[ButtonIndex].SumSample += Button_Read_1(ButtonIndex);
  count_sample--;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_ProcessIndex_1(reg8 ButtonIndex, reg8 CountSample)
{
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if (!CountSample)
  {
    Process_mask(ButtonIndex);
    CountSample = BUTTON_SAMPLE_TIMES_1;
  }
  Button->SumSample += Button_Read_1(ButtonIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Press_1(reg8 ButtonIndex)
{
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if ((Button->Status & BUTTON_STATUS_UP) && Button->HoldTime < BUTTON_PRESS_DOWN_TIME_1)
  {
    Button->Status = 0;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Check_1(reg8 ButtonIndex, reg8 Status, reg8 ClearStatus)
{
  return Button_Check(ButtonIndex, Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Hold_1(reg8 ButtonIndex, reg8 HoldTime, reg8 Once)
{
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if (Button->HoldTime == 0xFF)
    return 0;
  if ((Button->HoldTime >= HoldTime) && !Button->Logic)
  {
    Button->HoldTime = BUTTON_PRESS_DOWN_TIME_1 | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_HoldAccel_1(reg8 ButtonIndex, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_1
  #define BUTTON_ACCEL_MAX_HOLD_TIME_1  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_1  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_1       Accel->SubStep
#endif
  Button_TypeDef* Button = &Button_f1[ButtonIndex];
  if (Button->Logic)
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_1;
  else 
  {
    reg8 hold_time = *HoldTime;
    if (Button->HoldTime >= hold_time)
    {
      Button->HoldTime = BUTTON_PRESS_DOWN_TIME_1;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_1 + BUTTON_ACCEL_SUB_STEP_1))
        hold_time -= BUTTON_ACCEL_SUB_STEP_1;
      *HoldTime = hold_time;
      return 1;
    }
  }
  return 0;
}