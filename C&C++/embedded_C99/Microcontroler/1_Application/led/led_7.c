#include <led.h>

//==============================================================================================================================================================
void Led_Begin_7(const LedFunction_TypeDef __code* LedExFunction)
{
  void(*LedTurn)(reg8 LedIndex, reg8 IsOn) = LedExFunction->LedTurn;
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LedExFunction->NumberOfLed; LedIndex++)
  {
    LedEx_TypeDef* LedEx = &LedExFunction->LedEx[LedIndex];
    LedEx->IsOn = LedEx->CountEdgeTime = LedEx->Times = 0;
    LedTurn(LedIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_7(const LedFunction_TypeDef __code* LedExFunction)
{
  void (*Finish)(reg8 LedIndex) = LedExFunction->Finish;
  void (*LedTurn)(reg8 LedIndex, reg8 IsOn) = LedExFunction->LedTurn;
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LedExFunction->NumberOfLed; LedIndex++)
  {
    LedEx_TypeDef* LedEx = &LedExFunction->LedEx[LedIndex];
    if (LedEx->Times)
    {
      if (++LedEx->CountEdgeTime > LedEx->EdgeTime[LedEx->IsOn])
      {
        LedEx->CountEdgeTime = 1;
        LedTurn(LedIndex, (LedEx->IsOn = !LedEx->IsOn));
        if (LedEx->Times != LED_ALWAYS_BLINK)
        {
          if (!(--LedEx->Times) && Finish)
            Finish(LedIndex);
        }
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_7(const LedFunction_TypeDef __code* LedExFunction, reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  LedEx_TypeDef* LedEx = &LedExFunction->LedEx[LedIndex];
  LedExFunction->LedTurn(LedIndex, (LedEx->IsOn = 0));
  LedEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    LedEx->Times = LED_ALWAYS_BLINK;
  else
    LedEx->Times = Times * 2;
  LedEx->EdgeTime[1] = HighEdgeTime;
  LedEx->EdgeTime[0] = LowEdgeTime;
}