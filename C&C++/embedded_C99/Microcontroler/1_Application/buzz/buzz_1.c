#include <buzz.h>
#include <config.h>

extern __no_init Buzz_TypeDef Buzz1[NUMBER_OF_BUZZ_1];
void TurnBuzz1(reg8 BuzzIndex, reg8 IsOn);
//==============================================================================================================================================================
void Buzz_Begin_1()
{
  for (reg8 BuzzIndex = 0; BuzzIndex < NUMBER_OF_BUZZ_1; BuzzIndex++)
  {
    Buzz1[BuzzIndex].IsOn = Buzz1[BuzzIndex].Count = Buzz1[BuzzIndex].Times = 0;
    TurnBuzz1(BuzzIndex, 0);
  }
}
void Buzz_Process_1(void Finish(reg8 BuzzIndex))
{
  for (reg8 BuzzIndex = 0; BuzzIndex < NUMBER_OF_BUZZ_1; BuzzIndex++)
  {
    if (Buzz1[BuzzIndex].Times)
    {
      if (++Buzz1[BuzzIndex].Count > Buzz1[BuzzIndex].Period)
      {
        Buzz1[BuzzIndex].Count = 1;
        TurnBuzz1(BuzzIndex, (Buzz1[BuzzIndex].IsOn = !Buzz1[BuzzIndex].IsOn));
        if (Buzz1[BuzzIndex].Times != BUZZ_ALWAYS_RING)
        {
          if (!(--Buzz1[BuzzIndex].Times) && Finish)
            Finish(BuzzIndex);
        }
      }
    }
  }
}
void Buzz_Blink_1(reg8 BuzzIndex, reg8 Times, reg8 Period)
{
  TurnBuzz1(BuzzIndex, Buzz1[BuzzIndex].IsOn = 0);
  Buzz1[BuzzIndex].Count = 0xFE;
  if (Times > 100)
    Buzz1[BuzzIndex].Times = BUZZ_ALWAYS_RING;
  else
    Buzz1[BuzzIndex].Times = Times * 2;
  Buzz1[BuzzIndex].Period = Period;
}