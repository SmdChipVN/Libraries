#include <buzz.h>
#include <config.h>

extern __no_init BuzzEx_TypeDef BuzzEx3;
//==============================================================================================================================================================
void Buzz_Begin_3()
{
  BuzzEx3.IsOn = BuzzEx3.Count = BuzzEx3.Times = 0;
  TURN_BUZZ_EX_3(0);
}
//==============================================================================================================================================================
void Buzz_Process_3(void Finish())
{
  if (BuzzEx3.Times)
  {
    if (++BuzzEx3.Count > (&BuzzEx3.LowPeriod)[BuzzEx3.IsOn])
    {
      BuzzEx3.Count = 0;
      TURN_BUZZ_EX_3((BuzzEx3.IsOn = !BuzzEx3.IsOn));
      if (BuzzEx3.Times != BUZZ_ALWAYS_RING)
      {
        if (!(--BuzzEx3.Times) && Finish)
          Finish();
      }
    }
  }
}
//==============================================================================================================================================================
void Buzz_Ring_3(reg8 Times, reg8 HighPeriod, reg8 LowPeriod)
{
  TURN_BUZZ_EX_3((BuzzEx3.IsOn = 0));
  BuzzEx3.Count = 0xFE;
  if (Times > 100)
    BuzzEx3.Times = BUZZ_ALWAYS_RING;
  else
    BuzzEx3.Times = Times * 2;
  BuzzEx3.HighPeriod = HighPeriod;
  BuzzEx3.LowPeriod = LowPeriod;
}