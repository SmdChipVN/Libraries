#include <led.h>
//==============================================================================================================================================================
void Led_Begin_3(const LedFunction_TypeDef __code* LedFunction)
{
  void (*LedTurn)(reg8 LedIndex, reg8 IsOn) = LedFunction->LedTurn;
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LedFunction->NumberOfLed; LedIndex++)
  {
    Led_TypeDef* Led = &LedFunction->Led[LedIndex];
    Led->IsOn = Led->CountEdgeTime = Led->Times = 0;
    LedTurn(LedIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_ProcessIndex_3(const LedFunction_TypeDef __code* LedFunction, reg8 LedIndex)
{
  Led_TypeDef* Led = &LedFunction->Led[LedIndex];
  void(*Finish)(reg8 LedIndex) = LedFunction->Finish;
  if (Led->Times)
  {
    if (++Led->CountEdgeTime > Led->EdgeTime)
    {
      Led->CountEdgeTime = 1;
      LedFunction->LedTurn(LedIndex, (Led->IsOn = !Led->IsOn));
      if (Led->Times != LED_ALWAYS_BLINK)
      {
        if (!(--Led->Times) && Finish)
          Finish(LedIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_3(const LedFunction_TypeDef __code* LedFunction)
{
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LedFunction->NumberOfLed; LedIndex++)
    Led_ProcessIndex_3(LedFunction, LedIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_3(const LedFunction_TypeDef __code* LedFunction, reg8 LedIndex, reg8 Times, reg8 EdgeTime)
{
  Led_TypeDef* Led = &LedFunction->Led[LedIndex];
  LedFunction->LedTurn(LedIndex, Led->IsOn = 0);
  Led->CountEdgeTime = 0xFE;
  if (Times > 100)
    Led->Times = LED_ALWAYS_BLINK;
  else
    Led->Times = Times * 2;
  Led->EdgeTime = EdgeTime;
}