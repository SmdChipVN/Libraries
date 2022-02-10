#include <digital_input.h>
#include <config.h>
//==============================================================================================================================================================
void DigitalInput_BeginStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction)
{
  DigitalInput_TypeDef* DigitalInput;
  reg8 sum_sample = 0;
  {
    reg8 index = DigitalInputFunction->DigitalInputIndex;
    DigitalInput = &DigitalInputFunction->DigitalInput[index];
    {
      reg8 (*digital_input_read)(reg8 DigitalInputIndex) = DigitalInputFunction->DigitalInputRead;
      reg8 fill_sample;
      for (fill_sample = 0; fill_sample < DigitalInputFunction->SampleTimes; fill_sample++)
      {
        sum_sample <<= 1;
        sum_sample |= digital_input_read(index);
      }
    }
  }
  DigitalInput->SumSample = sum_sample;
#ifdef DIGITAL_INPUT_QUICK_STACK_2
  DigitalInput->Logic = BitCompare5[sum_sample];
#else
  DigitalInput->Logic = SetBitCount[sum_sample] >= DigitalInputFunction->SampleDivider;
#endif
  DigitalInput->Status = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction)
{
  DigitalInput_TypeDef* DigitalInput;
  reg8 now_logic;
  {
    reg8 sum_sample;
    {
      reg8 index = DigitalInputFunction->DigitalInputIndex;
      DigitalInput = &DigitalInputFunction->DigitalInput[index];
      sum_sample = DigitalInput->SumSample << 1;
      sum_sample |= DigitalInputFunction->DigitalInputRead(index);
    }
#ifdef DIGITAL_INPUT_QUICK_STACK_2
    now_logic = BitCompare5[sum_sample & 0x1F];
#else
    now_logic = SetBitCount[sum_sample & BitGroup.NonReverse.LSB[DigitalInputFunction->SampleTimes]] >= DigitalInputFunction->SampleDivider;
#endif
  }
  if (now_logic != DigitalInput->Logic)
  {
    DigitalInput->Logic = now_logic;
    DigitalInput->Status = now_logic + 1;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Begin_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction)
{
  DigitalInput_TypeDef* DigitalInput = DigitalInputFunction->DigitalInput;
  DigitalInput->Logic = DigitalInputFunction->DigitalInputRead(DigitalInputFunction->DigitalInputIndex);
  DigitalInput->Status = DigitalInput->SumSample = 0;
  return DigitalInputFunction->SampleTimes;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Process_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction, unsigned char* CountSample)
{
  reg8 index = DigitalInputFunction->DigitalInputIndex;
  DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[index];
  reg8 sum_sample = DigitalInput->SumSample;
  reg8 count_sample = *CountSample;
  reg8 ret = 0;
  if (!count_sample)
  {
    reg8 now_logic = sum_sample / DigitalInputFunction->SampleDivider;
    if (now_logic !=  DigitalInput->Logic)
    {
      DigitalInput->Logic = now_logic;
      DigitalInput->Status = now_logic + 1;
      ret = 1;
    }
    sum_sample = 0;
    count_sample = DigitalInputFunction->SampleTimes;
  }
  sum_sample += DigitalInputFunction->DigitalInputRead(index);
  DigitalInput->SumSample = sum_sample;
  *CountSample = count_sample - 1;
  return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Check_2(DigitalInput_TypeDef* DigitalInput, reg8 Status, reg8 ClearStatus)
{
  if (DigitalInput->Status == Status)
  {
    DigitalInput->Status |= ClearStatus;
    return 1;
  }
  return 0;
}