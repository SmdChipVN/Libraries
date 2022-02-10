#include <led.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init LedEx_TypeDef LedEx_f5[LED_EX_QUANTITY_5];
void LedEx_Turn_5(reg8 LedIndex, reg8 IsOn);
//==============================================================================================================================================================
void Led_Begin_5()
{
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LED_EX_QUANTITY_5; LedIndex++)
  {
    LedEx_TypeDef* LedEx = &LedEx_f5[LedIndex];
    LedEx->IsOn = LedEx->CountEdgeTime = LedEx->Times = 0;
    LedEx_Turn_5(LedIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_5(void Finish(reg8 LedIndex))
{
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LED_EX_QUANTITY_5; LedIndex++)
  {
    LedEx_TypeDef* LedEx = &LedEx_f5[LedIndex];
    if (LedEx->Times)
    {
      if (++LedEx->CountEdgeTime > LedEx->EdgeTime[LedEx->IsOn])
      {
        LedEx->CountEdgeTime = 1;
        LedEx_Turn_5(LedIndex, (LedEx->IsOn = !LedEx->IsOn));
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
void Led_Blink_5(reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  LedEx_TypeDef* LedEx = &LedEx_f5[LedIndex];
  LedEx_Turn_5(LedIndex, (LedEx->IsOn = 0));
  LedEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    LedEx->Times = LED_ALWAYS_BLINK;
  else
    LedEx->Times = Times * 2;
  LedEx->EdgeTime[1] = HighEdgeTime;
  LedEx->EdgeTime[0] = LowEdgeTime;
}