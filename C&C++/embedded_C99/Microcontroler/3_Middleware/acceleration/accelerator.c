#include <accelerator.h>
void Accelerator_Begin(const AcceleratorFunction_TypeDef __code* AcceleratorFunction, Accelerator_TypeDef* Accelerator)
{
  reg8 fill_sample;
  Accelerator->SumSample = 0;
  for (fill_sample = 0; fill_sample < AcceleratorFunction->SampleTimes; fill_sample++)
  {
    Accelerator->SumSample <<= 1;
    Accelerator->SumSample |= AcceleratorFunction->ReadSignal(Accelerator);
  }
}
reg8 Accelerator_Process(const AcceleratorFunction_TypeDef __code* AcceleratorFunction, Accelerator_TypeDef* Accelerator)
{
  Accelerator->SumSample &= BitArray.Reverse.LSB[AcceleratorFunction->SampleTimes];
  Accelerator->SumSample <<= 1;
  Accelerator->SumSample |= AcceleratorFunction->ReadSignal(Accelerator);
  return ((SetBitCount[Accelerator->SumSample & 127] + (Accelerator->SumSample > 127)) >= AcceleratorFunction->SampleDivider);
}