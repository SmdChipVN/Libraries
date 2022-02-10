#include <buzz.h>
#include <config.h>

extern __no_init BuzzEx_TypeDef BuzzEx4[NUMBER_OF_BUZZ_EX_4];
void TurnBuzzEx4(reg8 BuzzIndex, reg8 IsOn);
//==============================================================================================================================================================
void Buzz_Begin_4()
{
  for (reg8 BuzzIndex = 0; BuzzIndex < NUMBER_OF_BUZZ_EX_4; BuzzIndex++)
  {
    BuzzEx4[BuzzIndex].IsOn = BuzzEx4[BuzzIndex].Count = BuzzEx4[BuzzIndex].Times = 0;
    TurnBuzzEx4(BuzzIndex, 0);
  }
}
void Buzz_Process_4(void Finish(reg8 BuzzIndex))
{
  for (reg8 BuzzIndex = 0; BuzzIndex < NUMBER_OF_BUZZ_EX_4; BuzzIndex++)
  {
    if (BuzzEx4[BuzzIndex].Times)
    {
      if (++BuzzEx4[BuzzIndex].Count > (&BuzzEx4[BuzzIndex].LowPeriod)[BuzzEx4[BuzzIndex].IsOn])
      {
        BuzzEx4[BuzzIndex].Count = 0;
        TurnBuzzEx4(BuzzIndex, (BuzzEx4[BuzzIndex].IsOn = !BuzzEx4[BuzzIndex].IsOn));
        if (BuzzEx4[BuzzIndex].Times != BUZZ_ALWAYS_RING)
        {
          if (!(--BuzzEx4[BuzzIndex].Times) && Finish)
            Finish(BuzzIndex);
        }
      }
    }
  }
}
void Buzz_Ring_4(reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod)
{
  TurnBuzzEx4(BuzzIndex, (BuzzEx4[BuzzIndex].IsOn = 0));
  BuzzEx4[BuzzIndex].Count = 0xFE;
  if (Times > 100)
    BuzzEx4[BuzzIndex].Times = BUZZ_ALWAYS_RING;
  else
    BuzzEx4[BuzzIndex].Times = Times * 2;
  BuzzEx4[BuzzIndex].HighPeriod = HighPeriod;
  BuzzEx4[BuzzIndex].LowPeriod = LowPeriod;
}