#include <led.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init LedEx_TypeDef LedEx_f0;
//==============================================================================================================================================================
void LedEx_Begin_0()
{
  LedEx_f0.IsOn = LedEx_f0.CountEdgeTime = LedEx_f0.Times = 0;
  LED_EX_TURN_0(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void LedEx_Process_0(void Finish())
{
  if (LedEx_f0.Times)
  {
    if (++LedEx_f0.CountEdgeTime > LedEx_f0.EdgeTime[LedEx_f0.IsOn])
    {
      LedEx_f0.CountEdgeTime = 1;
      LED_EX_TURN_0((LedEx_f0.IsOn = !LedEx_f0.IsOn));
      if (LedEx_f0.Times != LED_ALWAYS_BLINK)
      {
        if (!(--LedEx_f0.Times) && Finish)
          Finish();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void LedEx_Blink_0(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  LedEx_f0.IsOn = 0;
  LED_EX_TURN_0(0);
  LedEx_f0.CountEdgeTime = 0xFE;
  if (Times > 100)
    LedEx_f0.Times = LED_ALWAYS_BLINK;
  else
    LedEx_f0.Times = Times << 1;
  LedEx_f0.EdgeTime[1] = HighEdgeTime;
  LedEx_f0.EdgeTime[0] = LowEdgeTime;
}