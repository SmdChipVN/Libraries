#include <buzz.h>

void Buzz_Begin_5(const BuzzExFunction_TypeDef* BuzzExFunction)
{
  BuzzEx_TypeDef* buzz = BuzzExFunction->BuzzEx;
  reg8 number_of_buzz = BuzzExFunction->NumberOfBuzz;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzExFunction->TurnBuzz;
  for (reg8 BuzzIndex = 0; BuzzIndex < number_of_buzz; BuzzIndex++)
  {
    buzz[BuzzIndex].IsOn = buzz[BuzzIndex].Count = buzz[BuzzIndex].Times = 0;
    turn_buzz(BuzzIndex, 0);
  }
}
//==============================================================================================================================================================
void Buzz_Process_5(const BuzzExFunction_TypeDef* BuzzExFunction)
{
  BuzzEx_TypeDef* buzz = BuzzExFunction->BuzzEx;
  reg8 number_of_buzz = BuzzExFunction->NumberOfBuzz;
  void(*finish_buzz)(reg8 BuzzIndex) = BuzzExFunction->Finish;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzExFunction->TurnBuzz;
  for (reg8 BuzzIndex = 0; BuzzIndex < number_of_buzz; BuzzIndex++)
  {
    if (buzz[BuzzIndex].Times)
    {
      if (++buzz[BuzzIndex].Count > (&buzz[BuzzIndex].LowPeriod)[buzz[BuzzIndex].IsOn])
      {
        buzz[BuzzIndex].Count = 0;
        turn_buzz(BuzzIndex, (buzz[BuzzIndex].IsOn = !buzz[BuzzIndex].IsOn));
        if (buzz[BuzzIndex].Times != BUZZ_ALWAYS_RING)
        {
          if (!(--buzz[BuzzIndex].Times) && finish_buzz)
            finish_buzz(BuzzIndex);
        }
      }
    }
  }
}
//==============================================================================================================================================================
void Buzz_Ring_5(const BuzzExFunction_TypeDef* BuzzExFunction, reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod)
{
  BuzzEx_TypeDef* buzz = BuzzExFunction->BuzzEx;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzExFunction->TurnBuzz;
  turn_buzz(BuzzIndex, (buzz[BuzzIndex].IsOn = 0));
  buzz[BuzzIndex].Count = 0xFE;
  if (Times > 100)
    buzz[BuzzIndex].Times = BUZZ_ALWAYS_RING;
  else
    buzz[BuzzIndex].Times = Times * 2;
  buzz[BuzzIndex].HighPeriod = HighPeriod;
  buzz[BuzzIndex].LowPeriod = LowPeriod;
}