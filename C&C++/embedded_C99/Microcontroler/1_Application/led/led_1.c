#include <led.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init Led_TypeDef Led_f1[LED_QUANTITY_1];
void Led_Turn_1(reg8 LedIndex, reg8 IsOn);
//==============================================================================================================================================================
void Led_Begin_1()
{
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LED_QUANTITY_1; LedIndex++)
  {
    Led_TypeDef* Led = &Led_f1[LedIndex];
    Led->IsOn = Led->CountEdgeTime = Led->Times = 0;
    Led_Turn_1(LedIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_ProcessIndex_1(reg8 LedIndex, void Finish(reg8 LedIndex))
{
  Led_TypeDef* Led = &Led_f1[LedIndex];
  if (Led->Times)
  {
    if (++Led->CountEdgeTime > Led->EdgeTime)
    {
      Led->CountEdgeTime = 1;
      Led_Turn_1(LedIndex, (Led->IsOn = !Led->IsOn));
      if (Led->Times != LED_ALWAYS_BLINK)
      {
        if (!(--Led->Times) && Finish)
          Finish(LedIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_1(void Finish(reg8 LedIndex))
{
  reg8 LedIndex;
  for (LedIndex = 0; LedIndex < LED_QUANTITY_1; LedIndex++)
    Led_ProcessIndex_1(LedIndex, Finish);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_1(reg8 LedIndex, reg8 Times, reg8 EdgeTime)
{
  Led_TypeDef* Led = &Led_f1[LedIndex];
  Led_Turn_1(LedIndex, Led->IsOn = 0);
  Led->CountEdgeTime = 0xFE;
  if (Times > 100)
    Led->Times = LED_ALWAYS_BLINK;
  else
    Led->Times = Times << 1;
  Led->EdgeTime = EdgeTime;
}