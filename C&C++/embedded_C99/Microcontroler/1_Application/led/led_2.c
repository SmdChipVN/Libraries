#include <led.h>
//==============================================================================================================================================================
void Led_Begin_2(const LedFunction_TypeDef __code* LedFunction)
{
  Led_TypeDef* Led = LedFunction->Led;
  Led->IsOn = Led->CountEdgeTime = Led->Times = 0;
  LedFunction->LedTurn(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_2(const LedFunction_TypeDef __code* LedFunction)
{
  void (*Finish)(reg8 LedIndex) = LedFunction->Finish;
  Led_TypeDef* Led = LedFunction->Led;
  if (Led->Times)
  {
    if (++Led->CountEdgeTime > Led->EdgeTime)
    {
      Led->CountEdgeTime = 1;
      LedFunction->LedTurn(0, (Led->IsOn = !Led->IsOn));
      if (Led->Times != LED_ALWAYS_BLINK)
      {
        if (!(--Led->Times) && Finish)
          Finish(0);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_2(const LedFunction_TypeDef __code* LedFunction, reg8 Times, reg8 EdgeTime)
{
  Led_TypeDef* Led = LedFunction->Led;
  LedFunction->LedTurn(0, Led->IsOn = 0);
  Led->CountEdgeTime = 0xFE;
  if (Times > 100)
    Led->Times = LED_ALWAYS_BLINK;
  else
    Led->Times = Times << 1;
  Led->EdgeTime = EdgeTime;
}