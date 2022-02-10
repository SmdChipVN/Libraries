#include <digital_input.h>
#include <config.h>
//==============================================================================================================================================================
void DigitalInput_BeginStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction)
{
  reg8 (*digital_input_read)(reg8 DigitalInputIndex) = DigitalInputFunction->DigitalInputRead;
  reg8 DigitalInputIndex;
  for (DigitalInputIndex = 0; DigitalInputIndex < DigitalInputFunction->NumberOfDigitalInput; DigitalInputIndex++)
  {
    DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
    reg8 sum_sample = 0;
    {
      reg8 fill_sample;
      for (fill_sample = 0; fill_sample < DigitalInputFunction->SampleTimes; fill_sample++)
      {
        sum_sample <<= 1;
        sum_sample |= digital_input_read(DigitalInputIndex);
      }
    }
    DigitalInput->SumSample = sum_sample;
#ifdef DIGITAL_INPUT_QUICK_STACK_2
    DigitalInput->Logic = BitCompare5[sum_sample];
#else
    DigitalInput->Logic = SetBitCount[sum_sample & BitGroup.NonReverse.LSB[DigitalInputFunction->SampleTimes]] >= DigitalInputFunction->SampleDivider;
#endif
    DigitalInput->Status = 0;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessIndexStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
  reg8 now_logic;
  {
    reg8 sum_sample = DigitalInput->SumSample << 1;
    sum_sample |= DigitalInputFunction->DigitalInputRead(DigitalInputIndex);
    DigitalInput->SumSample = sum_sample;
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
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_ProcessStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction)
{
  reg8 DigitalInputIndex;
  for (DigitalInputIndex = 0; DigitalInputIndex < DigitalInputFunction->NumberOfDigitalInput; DigitalInputIndex++)
    DigitalInput_ProcessIndexStack_3(DigitalInputFunction, DigitalInputIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_Begin_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample)
{
  reg8 (*button_read)(reg8 DigitalInputIndex) = DigitalInputFunction->DigitalInputRead;
  reg8 DigitalInputIndex;
  for (DigitalInputIndex = 0; DigitalInputIndex < DigitalInputFunction->NumberOfDigitalInput; DigitalInputIndex++)
  {
    DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
    DigitalInput->Logic = button_read(DigitalInputIndex);
    DigitalInput->Status = DigitalInput->SumSample = 0;
  }
  *CountSample = DigitalInputFunction->SampleTimes;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static reg8 Process(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
  reg8 now_logic = DigitalInput->SumSample / DigitalInputFunction->SampleDivider;
  DigitalInput->SumSample = 0;
  if (now_logic != DigitalInput->Logic)
  {
    DigitalInput->Logic = now_logic;
    DigitalInput->Status = now_logic + 1;
    return 1;
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Process_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample)
{
  reg8 count_sample = *CountSample;
  reg8 ret = 0;
  if (!count_sample)
  {
    reg8 DigitalInputIndex;
    for (DigitalInputIndex = 0; DigitalInputIndex < DigitalInputFunction->NumberOfDigitalInput; DigitalInputIndex++)
      Process(DigitalInputFunction, DigitalInputIndex);
    count_sample = DigitalInputFunction->SampleTimes;
    ret = 1;
  }
  {
    reg8(*button_read)(reg8 DigitalInputIndex) = DigitalInputFunction->DigitalInputRead;
    reg8 DigitalInputIndex;
    for (DigitalInputIndex = 0; DigitalInputIndex < DigitalInputFunction->NumberOfDigitalInput; DigitalInputIndex++)
      DigitalInputFunction->DigitalInput[DigitalInputIndex].SumSample += button_read(DigitalInputIndex);
  }
  *CountSample = count_sample - 1;
  return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessIndex_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 CountSample)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
  if (!CountSample)
  {
    Process(DigitalInputFunction, DigitalInputIndex);
    CountSample = DigitalInputFunction->SampleTimes;
  }
  DigitalInput->SumSample += DigitalInputFunction->DigitalInputRead(DigitalInputIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Check_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInputFunction->DigitalInput[DigitalInputIndex];
  if (DigitalInput->Status == Status)
  {
    DigitalInput->Status |= ClearStatus;
    return 1;
  }
  return 0;
}