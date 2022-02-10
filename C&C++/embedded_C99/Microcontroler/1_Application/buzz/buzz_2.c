#include <buzz.h>

void Buzz_Begin_2(const BuzzFunction_TypeDef* BuzzFunction)
{
  Buzz_TypeDef* buzz = BuzzFunction->Buzz;
  reg8 number_of_buzz = BuzzFunction->NumberOfBuzz;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzFunction->TurnBuzz;
  for (reg8 BuzzIndex = 0; BuzzIndex < number_of_buzz; BuzzIndex++)
  {
    buzz[BuzzIndex].IsOn = buzz[BuzzIndex].Count = buzz[BuzzIndex].Times = 0;
    turn_buzz(BuzzIndex, 0);
  }
}
void Buzz_Process_2(const BuzzFunction_TypeDef* BuzzFunction)
{
  Buzz_TypeDef* buzz = BuzzFunction->Buzz;
  reg8 number_of_buzz = BuzzFunction->NumberOfBuzz;
  void(*finish_buzz)(reg8 BuzzIndex) = BuzzFunction->Finish;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzFunction->TurnBuzz;
  for (reg8 BuzzIndex = 0; BuzzIndex < number_of_buzz; BuzzIndex++)
  {
    if (buzz[BuzzIndex].Times)
    {
      if (++buzz[BuzzIndex].Count > buzz[BuzzIndex].Period)
      {
        buzz[BuzzIndex].Count = 1;
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
void Buzz_Ring_2(const BuzzFunction_TypeDef* BuzzFunction, reg8 BuzzIndex, reg8 Times, reg8 Period)
{
  Buzz_TypeDef* buzz = BuzzFunction->Buzz;
  void(*turn_buzz)(reg8 BuzzIndex, reg8 IsOn) = BuzzFunction->TurnBuzz;
  turn_buzz(BuzzIndex, buzz[BuzzIndex].IsOn = 0);
  buzz[BuzzIndex].Count = 0xFE;
  if (Times > 100)
    buzz[BuzzIndex].Times = BUZZ_ALWAYS_RING;
  else
    buzz[BuzzIndex].Times = Times * 2;
  buzz[BuzzIndex].Period = Period;
}