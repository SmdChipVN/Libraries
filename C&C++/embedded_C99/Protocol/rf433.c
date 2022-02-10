#include <rf433.h>
#include <config.h>
#include <common.h>

__no_init RF433_TypeDef __data RF433;
__no_init static struct
{
  unsigned char TimeIndex;
  unsigned char CountSample;
  unsigned char SumSample;
  unsigned char Logic;
  unsigned char Reset;
} __data Capture;
__no_init static unsigned char Capture_TimeBuffer[65];

void RF433_Begin()
{
  reg8 sum_sample;
  reg8 fill_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= RF();
  }
  Capture.SumSample = sum_sample;
  Capture.TimeIndex = 0;
  Capture.Logic = 2;
  Capture.CountSample = 0;
}
void RF433_Capture()
{
  reg8 logic, count_sample;
  if (Capture.Reset)
    return;
  {
    reg8 sum_sample = Capture.SumSample;
    sum_sample <<= 1;
    sum_sample |= RF();
    logic = BitCompare5[sum_sample & 0x1F];
    Capture.SumSample = sum_sample;
  }
  count_sample = Capture.CountSample;
  if (logic == Capture.Logic)
  {
    if (count_sample == (4000 / RF433_TRIG_TIME))
    {
      if (!logic)
        Capture.Reset = Capture.TimeIndex & 0xFE;
    }
    else
      count_sample++;
  }
  else
  {
    if (count_sample != (4000 / RF433_TRIG_TIME) && Capture.TimeIndex < 65)
      Capture_TimeBuffer[Capture.TimeIndex++] = count_sample;
    count_sample = 0;
    Capture.Logic = logic;
  }
  Capture.CountSample = count_sample;
}
unsigned char RF433_Process()
{
  if (Capture.Reset)
  {
    reg8 size;
    if (Capture.Reset == 1)
    {
      Capture.Reset = 0;
      return 0;
    }
    size = 0;
    Capture.TimeIndex = 0;
    {
      reg8 i, data, byte_index = 0;
      reg8 last_cycle = Capture_TimeBuffer[0] + Capture_TimeBuffer[1];      
      for (i = 0; i < Capture.Reset; i += 2, size++)
      {
        reg8 cycle = Capture_TimeBuffer[i] + Capture_TimeBuffer[i + 1];
        reg8 delta = last_cycle - cycle;
        if (delta > (160 / RF433_TRIG_TIME) && delta < (256 - (200 / RF433_TRIG_TIME)))
        {
          Capture.Reset = 0;
          return 0;
        }
        last_cycle = cycle;
        data <<= 1;
        data |= Capture_TimeBuffer[i] > Capture_TimeBuffer[i + 1];
        if ((size & 7) == 7)
          RF433.Data[byte_index++] = data;
      }
      //RF433.Data[byte_index] = data;
    }
    Capture.Reset = 0;
    return size;
  }
  return 0;
}