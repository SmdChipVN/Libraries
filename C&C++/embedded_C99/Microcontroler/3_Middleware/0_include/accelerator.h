#ifndef _ACCELERATOR_H_
#define _ACCELERATOR_H_

#include <common.h>
typedef struct
{
  unsigned char SumSample;
} Accelerator_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  reg8 (*ReadSignal)(Accelerator_TypeDef* Accelerator);
  unsigned char SampleTimes;
  unsigned char SampleDivider;
} AcceleratorFunction_TypeDef;
//==============================================================================================================================================================
void Accelerator_Begin(const AcceleratorFunction_TypeDef __code* AcceleratorFunction, Accelerator_TypeDef* Accelerator);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Accelerator_Process(const AcceleratorFunction_TypeDef __code* AcceleratorFunction, Accelerator_TypeDef* Accelerator);
//==============================================================================================================================================================
//use-count:              1    3*/        1*          1*
#define ACCELERATOR_BEGIN(For, SumSample, ReadSignal, SampleTimes)\
For\
{\
  reg8 fill_sample;\
  SumSample = 0;\
  for (fill_sample = 0; fill_sample < SampleTimes; fill_sample++)\
  {\
    SumSample <<= 1;\
    SumSample |= ReadSignal;\
  }\
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//use-count:                1    3*/        1*          1*           1*
#define ACCELERATOR_PROCESS(For, SumSample, ReadSignal, SampleTimes, Function)\
For\
{\
  SumSample &= BitArray.Reverse.LSB[SampleTimes];\
  SumSample <<= 1;\
  SumSample |= ReadSignal;\
  Function\
}

#endif