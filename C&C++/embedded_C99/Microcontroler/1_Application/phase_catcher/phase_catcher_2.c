#include <phase_catcher.h>
#include <common.h>
#include <config.h>
//==============================================================================================================================================================
void PhaseCatcher_Begin_2()
{
  reg8 fill_sample, sum_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= PHASE_CATCHER_READ_2();
  }
  PhaseCatcher_f2.Status = PHASE_CATCHER_STATUS_CALIB;
  PhaseCatcher_f2.Capture.Logic = BitCompare5[sum_sample & 0x1F];
  PhaseCatcher_f2.Capture.SumSample = sum_sample;
  PhaseCatcher_f2.Capture.Counter.Time = 254;
  PhaseCatcher_f2.Capture.Counter.Error = PhaseCatcher_f2.Capture.Counter.Ok = 255;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Catch_2()
{
  static unsigned char offset_time = 0;
  #if ((PHASE_CATCHER_OFFSET_HIGH_2 | PHASE_CATCHER_OFFSET_LOW_2) != 0)
    static unsigned char count_offset = 0;
    if (count_offset)
    {
      if (!(--count_offset))
      {
        extern void PhaseCatch_2();
        PhaseCatch_2();
        PhaseCatcher_f2.Capture.Counter.Time = 255;
      }
    }
  #endif
  if (PhaseCatcher_f2.Capture.Counter.Time != 254)
    PhaseCatcher_f2.Capture.Counter.Time++;
  if (PhaseCatcher_f2.Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher_f2.Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PHASE_CATCHER_READ_2();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher_f2.Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher_f2.Capture.Logic)
    {
      if (offset_time < ((PHASE_CATCHER_WIDTH_TIME_2 + 200) / PHASE_CATCHER_TRIG_TIME_2))
        offset_time++;
      else
      {
        offset_time = 0;
        PhaseCatcher_f2.Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher_f2.Capture.Counter.Error))
          PhaseCatcher_f2.Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
    }
    else
    {
      PhaseCatcher_f2.Capture.Logic = logic;
      if (PhaseCatcher_f2.Status == PHASE_CATCHER_STATUS_CALIB)
        PhaseCatcher_f2.Status = PHASE_CATCHER_STATUS_READY;
      else
      {
        if (offset_time > ((PHASE_CATCHER_WIDTH_TIME_2 - 300) / PHASE_CATCHER_TRIG_TIME_2))
        {
          PhaseCatcher_f2.Capture.Counter.Error = 255;
          if (PhaseCatcher_f2.Status == PHASE_CATCHER_STATUS_READY)
          {
            extern void PhaseCatch_2();
            if (logic)
            {
              #if (PHASE_CATCHER_OFFSET_HIGH_2 == 0)
                PhaseCatch_2();
                PhaseCatcher_f2.Capture.Counter.Time = 0;
              #else
                count_offset = PHASE_CATCHER_OFFSET_HIGH_2;
              #endif
            }
            else
            {
              #if (PHASE_CATCHER_OFFSET_LOW_2 == 0)
                PhaseCatch_2();
                PhaseCatcher_f2.Capture.Counter.Time = 0;
              #else
                count_offset = PHASE_CATCHER_OFFSET_LOW_2;
              #endif
            }
          }
          if (!(--PhaseCatcher_f2.Capture.Counter.Ok))
            PhaseCatcher_f2.Status = PHASE_CATCHER_STATUS_READY;
        }
        else
        {
          PhaseCatcher_f2.Capture.Counter.Ok = 255;
          if (!(--PhaseCatcher_f2.Capture.Counter.Error))
            PhaseCatcher_f2.Status = PHASE_CATCHER_STATUS_AC_ERROR;
        }
      }
      offset_time = 0;
    }
  }
}