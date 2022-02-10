#include <buzz.h>
#include <config.h>

extern __no_init Buzz_TypeDef Buzz0;
//==============================================================================================================================================================
void Buzz_Begin_0()
{
  Buzz0.IsOn = Buzz0.Count = Buzz0.Times = 0;
  TURN_BUZZ_0(0);
}
//==============================================================================================================================================================
void Buzz_Process_0(void Finish())
{
  if (Buzz0.Times)
  {
    if (++Buzz0.Count > Buzz0.Period)
    {
      Buzz0.Count = 1;
      TURN_BUZZ_0((Buzz0.IsOn = !Buzz0.IsOn));
      if (Buzz0.Times != BUZZ_ALWAYS_RING)
      {
        if (!(--Buzz0.Times) && Finish)
          Finish();
      }
    }
  }
}
//==============================================================================================================================================================
void Buzz_Ring_0(reg8 Times, reg8 Period)
{
  TURN_BUZZ_0(Buzz0.IsOn = 0);
  Buzz0.Count = 0xFE;
  if (Times > 100)
    Buzz0.Times = BUZZ_ALWAYS_RING;
  else
    Buzz0.Times = Times * 2;
  Buzz0.Period = Period;
}