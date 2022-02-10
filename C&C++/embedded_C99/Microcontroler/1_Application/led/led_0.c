#include <Led.h>
#include <config.h>

extern __no_init Led_TypeDef Led_f0;
//==============================================================================================================================================================
void Led_Begin_0()
{
  Led_f0.IsOn = Led_f0.CountEdgeTime = Led_f0.Times = 0;
  LED_TURN_0(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Process_0(void Finish())
{
  if (Led_f0.Times)
  {
    if (++Led_f0.CountEdgeTime > Led_f0.EdgeTime)
    {
      Led_f0.CountEdgeTime = 1;
      LED_TURN_0((Led_f0.IsOn = !Led_f0.IsOn));
      if (Led_f0.Times != LED_ALWAYS_BLINK)
      {
        if (!(--Led_f0.Times) && Finish)
          Finish();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Blink_0(reg8 Times, reg8 EdgeTime)
{
  Led_f0.IsOn = 0;
  LED_TURN_0(0);
  Led_f0.CountEdgeTime = 0xFE;
  if (Times > 100)
    Led_f0.Times = LED_ALWAYS_BLINK;
  else
    Led_f0.Times = Times << 1;
  Led_f0.EdgeTime = EdgeTime;
}