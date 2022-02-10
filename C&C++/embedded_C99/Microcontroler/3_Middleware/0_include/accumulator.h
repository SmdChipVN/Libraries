#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_

#include <common.h>
typedef struct
{
  unsigned char SumSample;
  unsigned char CountSample;
} Accumulator_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  reg8 (*ReadSignal)(Accumulator_TypeDef* Accumulator);
  unsigned char SampleTimes;
  unsigned char SampleDivider;
} AccumulatorFunction_TypeDef;
//==============================================================================================================================================================
void Accumulator_Begin(const AccumulatorFunction_TypeDef __code* AccumulatorFunction, Accumulator_TypeDef* Accumulator);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 Accumulator_Process(const AccumulatorFunction_TypeDef __code* AccumulatorFunction, Accumulator_TypeDef* Accumulator);
//==============================================================================================================================================================
//use-count:              1    1          1            1
#define ACCUMULATOR_BEGIN(For, SumSample, CountSample, SampleTimes)\
For\
{\
  SumSample = 0;\
}\
CountSample = SampleTimes
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//use-count:                2    3*/        2*           1           1              1            1
#define ACCUMULATOR_PROCESS(For, SumSample, CountSample, ReadSignal, SampleDivider, SampleTimes, Function)\
if (!CountSample)\
{\
  For\
  {\
    SumSample /= SampleDivider;\
    Function\
    SumSample = 0;\
  }\
  CountSample = SampleTimes;\
}\
For\
{\
SumSample += ReadSignal;\
}\
CountSample--

#endif