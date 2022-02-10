#include <phase_catcher.h>
#include <common.h>
#include <config.h>
//==============================================================================================================================================================
void PhaseCatcher_Begin_0()
{
  reg8 fill_sample, sum_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= PHASE_CATCHER_READ_0();
  }
  PhaseCatcher_f0.Status = PHASE_CATCHER_STATUS_CALIB;
  PhaseCatcher_f0.Capture.Logic = BitCompare5[sum_sample & 0x1F];
  PhaseCatcher_f0.Capture.SumSample = sum_sample;
  PhaseCatcher_f0.Capture.Counter.Time = 254;
  PhaseCatcher_f0.Capture.Counter.Error = PhaseCatcher_f0.Capture.Counter.Ok = 255;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Catch_0()
{
  if (PhaseCatcher_f0.Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher_f0.Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PHASE_CATCHER_READ_0();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher_f0.Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher_f0.Capture.Logic)
    {
      if (PhaseCatcher_f0.Capture.Counter.Time < ((PHASE_CATCHER_WIDTH_TIME_0 + 200) / PHASE_CATCHER_TRIG_TIME_0))
        PhaseCatcher_f0.Capture.Counter.Time++;
      else
      {
        PhaseCatcher_f0.Capture.Counter.Time = 0;
        PhaseCatcher_f0.Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher_f0.Capture.Counter.Error))
          PhaseCatcher_f0.Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
    }
    else
    {
      PhaseCatcher_f0.Capture.Logic = logic;
      if (PhaseCatcher_f0.Status == PHASE_CATCHER_STATUS_CALIB)
        PhaseCatcher_f0.Status = PHASE_CATCHER_STATUS_READY;
      else
      {
        if (PhaseCatcher_f0.Capture.Counter.Time > ((PHASE_CATCHER_WIDTH_TIME_0 - 300) / PHASE_CATCHER_TRIG_TIME_0))
        {
          PhaseCatcher_f0.Capture.Counter.Error = 255;
          if (PhaseCatcher_f0.Status == PHASE_CATCHER_STATUS_READY)
          {
            extern void PhaseCatch_0();
            PhaseCatch_0();
          }
          if (!(--PhaseCatcher_f0.Capture.Counter.Ok))
            PhaseCatcher_f0.Status = PHASE_CATCHER_STATUS_READY;
        }
        else
        {
          PhaseCatcher_f0.Capture.Counter.Ok = 255;
          if (!(--PhaseCatcher_f0.Capture.Counter.Error))
            PhaseCatcher_f0.Status = PHASE_CATCHER_STATUS_AC_ERROR;
        }
      }
      PhaseCatcher_f0.Capture.Counter.Time = 0;
    }
  }
}