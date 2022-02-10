#include <math.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg16 Math_Round(reg16 RefValue, reg16 RoundTo)
{
  RefValue += RoundTo * 5;
  RoundTo *= 10;
  RefValue /= RoundTo;
  RefValue *= RoundTo;
  return RefValue;
}