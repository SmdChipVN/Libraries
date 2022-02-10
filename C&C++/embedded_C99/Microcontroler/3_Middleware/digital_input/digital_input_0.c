#include <digital_input.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalInput_TypeDef DigitalInput_f0;
static __no_init unsigned char count_sample;
//==============================================================================================================================================================
void DigitalInput_BeginStack_0()
{
  reg8 sum_sample = 0;
  {
    reg8 fill_sample;
    for (fill_sample = 0; fill_sample < DIGITAL_INPUT_SAMPLE_TIMES_0; fill_sample++)
    {
      sum_sample <<= 1;
      sum_sample |= DIGITAL_INPUT_READ_0();
    }
  }
  DigitalInput_f0.SumSample = sum_sample;
#ifdef DIGITAL_INPUT_QUICK_STACK_0
  DigitalInput_f0.Logic = BitCompare5[sum_sample];
#else
  DigitalInput_f0.Logic = SetBitCount[sum_sample] >= DIGITAL_INPUT_SAMPLE_DIVIDER_0;
#endif
  DigitalInput_f0.Status = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_ProcessStack_0()
{
  reg8 sum_sample;
  sum_sample = DigitalInput_f0.SumSample << 1;
  sum_sample |= DIGITAL_INPUT_READ_0();
  DigitalInput_f0.SumSample = sum_sample;
  {
#ifdef DIGITAL_INPUT_QUICK_STACK_0
    reg8 now_logic = BitCompare5[sum_sample & 0x1F];
#else
    reg8 now_logic = SetBitCount[sum_sample & BitGroup.NonReverse.LSB[DIGITAL_INPUT_SAMPLE_TIMES_0]] >= DIGITAL_INPUT_SAMPLE_DIVIDER_0;
#endif
    if (now_logic != DigitalInput_f0.Logic)
    {
      DigitalInput_f0.Logic = now_logic;
      DigitalInput_f0.Status = now_logic + 1;
      return 1;
    }
  }
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_Begin_0()
{
  count_sample = DIGITAL_INPUT_SAMPLE_TIMES_0;
  DigitalInput_f0.Logic = DIGITAL_INPUT_READ_0();
  DigitalInput_f0.Status = DigitalInput_f0.SumSample = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Process_0()
{
  reg8 ret = 0, sum_sample = DigitalInput_f0.SumSample;
  if (!count_sample)
  {
    count_sample = DIGITAL_INPUT_SAMPLE_TIMES_0;
    sum_sample /= DIGITAL_INPUT_SAMPLE_DIVIDER_0;
    ret = 1;
    if (sum_sample != DigitalInput_f0.Logic)
    {
      DigitalInput_f0.Logic = sum_sample;
      DigitalInput_f0.Status = sum_sample + 1;
      ret++;
    }
    sum_sample = 0;
  }
  sum_sample += DIGITAL_INPUT_READ_0();
  DigitalInput_f0.SumSample = sum_sample;
  count_sample--;
  return ret;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 DigitalInput_Check_0(reg8 Status, reg8 ClearStatus)
{
  if (DigitalInput_f0.Status == Status)
  {
    DigitalInput_f0.Status |= ClearStatus;
    return 1;
  }
  return 0;
}