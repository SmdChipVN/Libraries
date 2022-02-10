#include <led.h>
//==============================================================================================================================================================
void Led_Begin_6(const LedFunction_TypeDef __code* LedExFunction)
{
  LedEx_TypeDef* LedEx = LedExFunction->LedEx;
  LedEx->IsOn = LedEx->CountEdgeTime = LedEx->Times = 0;
  LedExFunction->LedTurn(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_6(const LedFunction_TypeDef __code* LedExFunction)
{
  LedEx_TypeDef* LedEx = LedExFunction->LedEx;
  if (LedEx->Times)
  {
    if (++LedEx->CountEdgeTime > LedEx->EdgeTime[LedEx->IsOn])
    {
      LedEx->CountEdgeTime = 1;
      LedExFunction->LedTurn(0, (LedEx->IsOn = !LedEx->IsOn));
      if (LedEx->Times != LED_ALWAYS_BLINK)
      {
        if (!(--LedEx->Times) && LedExFunction->Finish)
          LedExFunction->Finish(0);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_6(const LedFunction_TypeDef __code* LedExFunction, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  LedEx_TypeDef* LedEx = LedExFunction->LedEx;
  LedExFunction->LedTurn(0, (LedEx->IsOn = 0));
  LedEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    LedEx->Times = LED_ALWAYS_BLINK;
  else
    LedEx->Times = Times << 1;
  LedEx->EdgeTime[1] = HighEdgeTime;
  LedEx->EdgeTime[0] = LowEdgeTime;
}