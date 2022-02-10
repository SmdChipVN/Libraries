#include <accumulator.h>
void Accumulator_Begin(const AccumulatorFunction_TypeDef __code* AccumulatorFunction, Accumulator_TypeDef* Accumulator)
{
  Accumulator->SumSample = 0;
  Accumulator->CountSample = AccumulatorFunction->SampleTimes;
}
reg8 Accumulator_Process(const AccumulatorFunction_TypeDef __code* AccumulatorFunction, Accumulator_TypeDef* Accumulator)
{
  reg8 value;
  if (!Accumulator->CountSample)
  {
    Accumulator->SumSample /= AccumulatorFunction->SampleDivider;
    value = Accumulator->SumSample;
    Accumulator->SumSample = 0;
    Accumulator->CountSample = AccumulatorFunction->SampleTimes;
  }
  Accumulator->SumSample += AccumulatorFunction->ReadSignal(Accumulator);
  Accumulator->CountSample--;
  return value;
}