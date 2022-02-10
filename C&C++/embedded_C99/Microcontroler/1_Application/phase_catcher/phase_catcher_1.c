#include <phase_catcher.h>
#include <common.h>
#include <config.h>
//==============================================================================================================================================================
void PhaseCatcher_Begin_1()
{
  reg8 fill_sample, sum_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= PHASE_CATCHER_READ_1();
  }
  PhaseCatcher_f1.Status = PHASE_CATCHER_STATUS_CALIB;
  PhaseCatcher_f1.Capture.Logic = BitCompare5[sum_sample & 0x1F];
  PhaseCatcher_f1.Capture.SumSample = sum_sample;
  PhaseCatcher_f1.Capture.Counter.Time = 254;  
  PhaseCatcher_f1.Capture.Counter.Error = PhaseCatcher_f1.Capture.Counter.Ok = 255;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Catch_1()
{
  if (PhaseCatcher_f1.Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher_f1.Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PHASE_CATCHER_READ_1();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher_f1.Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher_f1.Capture.Logic)
    {
      reg8 time = PhaseCatcher_f1.Capture.Counter.Time;
      if (PhaseCatcher_f1.Capture.Stage)
      {
        if (time == ((PHASE_CATCHER_WIDTH_TIME_1 / PHASE_CATCHER_TRIG_TIME_1) - 1))
        {
          time = 255;
          PhaseCatcher_f1.Capture.Stage = 0;
          if (PhaseCatcher_f1.Status == PHASE_CATCHER_STATUS_READY)
          {
            extern void PhaseCatch_1();
            PhaseCatch_1();
          }
        }
      }
      else if (time >= ((PHASE_CATCHER_WIDTH_TIME_0 + 200) / PHASE_CATCHER_TRIG_TIME_0))
      {
        time = 255;
        PhaseCatcher_f1.Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher_f1.Capture.Counter.Error))
          PhaseCatcher_f1.Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
      time++;
      PhaseCatcher_f1.Capture.Counter.Time = time;
    }
    else
    {
      PhaseCatcher_f1.Capture.Logic = logic;
      if (logic == PHASE_CATCHER_EDGE_1)
      {
        reg8 status = PhaseCatcher_f1.Status;
        PhaseCatcher_f1.Capture.Stage = 1;
        if (status == PHASE_CATCHER_STATUS_CALIB)
          status = PHASE_CATCHER_STATUS_READY;
        else
        {
          if (PhaseCatcher_f1.Capture.Counter.Time > ((PHASE_CATCHER_WIDTH_TIME_1 - 300) / PHASE_CATCHER_TRIG_TIME_1))
          {
            PhaseCatcher_f1.Capture.Counter.Error = 255;
            if (status == PHASE_CATCHER_STATUS_READY)
            {
              extern void PhaseCatch_1();
              PhaseCatch_1();
            }
            if (!(--PhaseCatcher_f1.Capture.Counter.Ok))
              status = PHASE_CATCHER_STATUS_READY;
          }
          else
          {
            PhaseCatcher_f1.Capture.Counter.Ok = 255;
            if (!(--PhaseCatcher_f1.Capture.Counter.Error))
              status = PHASE_CATCHER_STATUS_AC_ERROR;
          }
        }
        PhaseCatcher_f1.Status = (PHASE_CATCHER_STATUS)status;
        PhaseCatcher_f1.Capture.Counter.Time = 0;
      }
    }
  }
}