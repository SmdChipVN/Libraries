#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
extern __no_init ButtonEx_TypeDef ButtonEx_f0;
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_0(BUTTON_EX, ButtonEx, ButtonEx_f0, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void ButtonEx_BeginStack_0()
{
  ButtonEx_f0.HoldTime[0] = ButtonEx_f0.HoldTime[1] = 0;
  ButtonEx_BeginStack();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_ProcessStack_0()
{
  if (ButtonEx_ProcessStack())
  {
    if (ButtonEx_f0.Logic)
    {
      if (ButtonEx_f0.HoldTime[0] < BUTTON_EX_PRESS_DOWN_TIME_0)
      {
        if (ButtonEx_f0.PressCount < 10)
          ButtonEx_f0.PressCount++;
      }
      ButtonEx_f0.HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx_f0.HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_0 + BUTTON_EX_PRESS_TIME_OUT_0))
        ButtonEx_f0.PressCount = 0;
      ButtonEx_f0.HoldTime[0] = 0;
    }
  }
  else
  {
    if (ButtonEx_f0.Logic)
    {
      if (ButtonEx_f0.HoldTime[1] < 0xFE)
        ButtonEx_f0.HoldTime[1]++;
    }
    else if (ButtonEx_f0.HoldTime[0] < 0xFE)
        ButtonEx_f0.HoldTime[0]++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Begin_0()
{
  ButtonEx_f0.HoldTime[0] = ButtonEx_f0.HoldTime[1] = 0;
  ButtonEx_f0.PressCount = 0;
  ButtonEx_Begin();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonEx_Process_0()
{
  reg8 logic_changed = ButtonEx_Process();
  if (logic_changed == 2)
  {
    if (ButtonEx_f0.Logic)
    {
      if (ButtonEx_f0.HoldTime[0] < BUTTON_EX_PRESS_DOWN_TIME_0)
      {
        if (ButtonEx_f0.PressCount < 10)
          ButtonEx_f0.PressCount++;
      }
      ButtonEx_f0.HoldTime[1] = 0;
    }
    else
    {
      if (ButtonEx_f0.HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_0 + BUTTON_EX_PRESS_TIME_OUT_0))
        ButtonEx_f0.PressCount = 0;
      ButtonEx_f0.HoldTime[0] = 0;
    }
  }
  else if (logic_changed)
  {
    if (ButtonEx_f0.Logic)
    {
      if (ButtonEx_f0.HoldTime[1] < 0xFE)
        ButtonEx_f0.HoldTime[1]++;
    }
    else if (ButtonEx_f0.HoldTime[0] < 0xFE)
        ButtonEx_f0.HoldTime[0]++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Press_0(reg8 Times)
{
  if (ButtonEx_f0.HoldTime[1] >= (unsigned char)(BUTTON_EX_PRESS_DOWN_TIME_0 + BUTTON_EX_PRESS_TIME_OUT_0))
  {
    reg8 ret = Times > 10 ? ButtonEx_f0.PressCount : (ButtonEx_f0.PressCount == Times);
    if (ret) 
      ButtonEx_f0.PressCount = 0;
    return ret;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Check_0(reg8 Status, reg8 ClearStatus)
{
  return ButtonEx_Check(Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_Hold_0(reg8 Status, reg8 HoldTime, reg8 Once)
{
  reg8 hold_time = ButtonEx_f0.HoldTime[--Status];
  if (hold_time == 0xFF)
    return 0;
  if ((hold_time >= HoldTime) && (ButtonEx_f0.Logic == Status))
  {
    ButtonEx_f0.HoldTime[Status] = BUTTON_EX_PRESS_DOWN_TIME_0 | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 ButtonEx_HoldAccel_0(reg8 Status, const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_EX_ACCEL_MAX_HOLD_TIME_0
  #define BUTTON_EX_ACCEL_MAX_HOLD_TIME_0  Accel->MaxHoldTime
  #define BUTTON_EX_ACCEL_MIN_HOLD_TIME_0  Accel->MinHoldTime
  #define BUTTON_EX_ACCEL_SUB_STEP_0       Accel->SubStep
#endif
  if (ButtonEx_f0.Logic == --Status)
  {
    reg8 hold_time = *HoldTime;
    if (ButtonEx_f0.HoldTime[Status] >= hold_time)
    {
      ButtonEx_f0.HoldTime[Status] = BUTTON_EX_PRESS_DOWN_TIME_0;
      if (hold_time >= (BUTTON_EX_ACCEL_MIN_HOLD_TIME_0 + BUTTON_EX_ACCEL_SUB_STEP_0))
        hold_time -= BUTTON_EX_ACCEL_SUB_STEP_0;
      *HoldTime = hold_time;
      return 1;
    }
  }
  else
    *HoldTime = BUTTON_EX_ACCEL_MAX_HOLD_TIME_0;
  return 0;
}