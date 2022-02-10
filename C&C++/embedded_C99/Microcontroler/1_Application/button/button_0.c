#include <button.h>
#include <config.h>
#include <digital_input.h>
//==============================================================================================================================================================
extern __no_init Button_TypeDef Button_f0;
//==============================================================================================================================================================
DIGITAL_INPUT_INHERIT_SOURCE_0(BUTTON, Button, Button_f0, BitCompare5[sum_sample], static, )
//==============================================================================================================================================================
void Button_BeginStack_0()
{
  Button_BeginStack();
  Button_f0.HoldTime = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_ProcessStack_0()
{
  reg8 logic_changed = Button_ProcessStack();
  if (!Button_f0.Logic)
  {
    if (logic_changed)
      Button_f0.HoldTime = 0;
    else if (Button_f0.HoldTime < 0xFE)
      Button_f0.HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Begin_0()
{
  Button_Begin();
  Button_f0.HoldTime = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Process_0()
{
  reg8 logic_changed = Button_Process();
  if (!Button_f0.Logic)
  {
    if (logic_changed == 2)
      Button_f0.HoldTime = 0;
    else if (logic_changed && Button_f0.HoldTime < 0xFE)
      Button_f0.HoldTime++;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Press_0()
{
  if ((Button_f0.Status & BUTTON_STATUS_UP) && Button_f0.HoldTime < BUTTON_PRESS_DOWN_TIME_0)
  {
    Button_f0.Status = 0;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Check_0(reg8 Status, reg8 ClearStatus)
{
  return Button_Check(Status, ClearStatus);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_Hold_0(reg8 HoldTime, reg8 Once)
{
  if (Button_f0.HoldTime == 0xFF)
    return 0;
  if ((Button_f0.HoldTime >= HoldTime) && !Button_f0.Logic)
  {
    Button_f0.HoldTime = BUTTON_PRESS_DOWN_TIME_0 | Once;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Button_HoldAccel_0(const ButtonAccel_TypeDef __code* Accel, unsigned char* HoldTime)
{
#ifndef BUTTON_ACCEL_MAX_HOLD_TIME_0
  #define BUTTON_ACCEL_MAX_HOLD_TIME_0  Accel->MaxHoldTime
  #define BUTTON_ACCEL_MIN_HOLD_TIME_0  Accel->MinHoldTime
  #define BUTTON_ACCEL_SUB_STEP_0       Accel->SubStep
#endif
  if (Button_f0.Logic)
    *HoldTime = BUTTON_ACCEL_MAX_HOLD_TIME_0;
  else 
  {
    reg8 hold_time = *HoldTime;
    if (Button_f0.HoldTime >= hold_time)
    {
      Button_f0.HoldTime = BUTTON_PRESS_DOWN_TIME_0;
      if (hold_time >= (BUTTON_ACCEL_MIN_HOLD_TIME_0 + BUTTON_ACCEL_SUB_STEP_0))
        hold_time -= BUTTON_ACCEL_SUB_STEP_0;
      *HoldTime = hold_time;
      return 1;
    }
  }
  return 0;
}