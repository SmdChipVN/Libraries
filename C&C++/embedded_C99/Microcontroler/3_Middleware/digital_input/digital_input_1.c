#include <digital_input.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalInput_TypeDef DigitalInput_f1[DIGITAL_INPUT_QUANTITY_1];
reg8 DigitalInput_Read_1(reg8 DigitalInputIndex);
static __no_init unsigned char count_sample;
//==============================================================================================================================================================
void DigitalInput_BeginStack_1()
{
  reg8 DigitalInputIndex;
  for (DigitalInputIndex = 0; DigitalInputIndex < DIGITAL_INPUT_QUANTITY_1; DigitalInputIndex++)
  {
    DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
    reg8 sum_sample = 0;
    {
      reg8 fill_sample;
      for (fill_sample = 0; fill_sample < DIGITAL_INPUT_SAMPLE_TIMES_1; fill_sample++)
      {
        sum_sample <<= 1;
        sum_sample |= DigitalInput_Read_1(DigitalInputIndex);
      }
    }
    DigitalInput->SumSample = sum_sample;
#ifdef DIGITAL_INPUT_QUICK_STACK_1
    DigitalInput->Logic = BitCompare5[sum_sample];
#else
    DigitalInput->Logic = SetBitCount[sum_sample] >= DIGITAL_INPUT_SAMPLE_DIVIDER_1;
#endif
    DigitalInput->Status = 0;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessIndexStack_1(reg8 DigitalInputIndex)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
  reg8 sum_sample = DigitalInput->SumSample;
  sum_sample <<= 1;
  sum_sample |= DigitalInput_Read_1(DigitalInputIndex);
  DigitalInput->SumSample = sum_sample;
  {
#ifdef DIGITAL_INPUT_QUICK_STACK_1
    reg8 now_logic = BitCompare5[sum_sample & 0x1F];
#else
    reg8 now_logic = SetBitCount[sum_sample & BitGroup.NonReverse.LSB[DIGITAL_INPUT_SAMPLE_TIMES_1]] >= DIGITAL_INPUT_SAMPLE_DIVIDER_1;
#endif
    if (now_logic != DigitalInput->Logic)
    {
      DigitalInput->Logic = now_logic;
      DigitalInput->Status = now_logic + 1;
      return 1;
    }
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_ProcessStack_1()
{
  reg8 DigitalInputIndex;
  for (DigitalInputIndex = 0; DigitalInputIndex < DIGITAL_INPUT_QUANTITY_1; DigitalInputIndex++)
    DigitalInput_ProcessIndexStack_1(DigitalInputIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_Begin_1()
{
  reg8 DigitalInputIndex;
  count_sample = DIGITAL_INPUT_SAMPLE_TIMES_1;
  for (DigitalInputIndex = 0; DigitalInputIndex < DIGITAL_INPUT_QUANTITY_1; DigitalInputIndex++)
  {
    DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
    DigitalInput->Logic = DigitalInput_Read_1(DigitalInputIndex);
    DigitalInput->Status = DigitalInput->SumSample = 0;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static reg8 Process(reg8 DigitalInputIndex)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
  reg8 now_logic = DigitalInput->SumSample / DIGITAL_INPUT_SAMPLE_DIVIDER_1;
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
reg8 DigitalInput_Process_1()
{
  reg8 ret = 0;
  if (!count_sample)
  {
    reg8 DigitalInputIndex;
    for (DigitalInputIndex = 0; DigitalInputIndex < DIGITAL_INPUT_QUANTITY_1; DigitalInputIndex++)
      Process(DigitalInputIndex);
    count_sample = DIGITAL_INPUT_SAMPLE_TIMES_1;
    ret = 1;
  }
  {
    reg8 DigitalInputIndex;
    for (DigitalInputIndex = 0; DigitalInputIndex < DIGITAL_INPUT_QUANTITY_1; DigitalInputIndex++)
      DigitalInput_f1[DigitalInputIndex].SumSample += DigitalInput_Read_1(DigitalInputIndex);
  }
  count_sample--;
  return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessIndex_1(reg8 DigitalInputIndex, reg8 CountSample)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
  if (!CountSample)
  {
    Process(DigitalInputIndex);
    CountSample = DIGITAL_INPUT_SAMPLE_TIMES_1;
  }
  DigitalInput->SumSample += DigitalInput_Read_1(DigitalInputIndex);
  return CountSample - 1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Check_1(reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus)
{
  DigitalInput_TypeDef* DigitalInput = &DigitalInput_f1[DigitalInputIndex];
  if (DigitalInput->Status == Status)
  {
    DigitalInput->Status |= ClearStatus;
    return 1;
  }
  return 0;
}