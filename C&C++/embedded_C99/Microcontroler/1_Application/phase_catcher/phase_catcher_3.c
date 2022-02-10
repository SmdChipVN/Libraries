#include <phase_catcher.h>
#include <common.h>
#include <config.h>
//==============================================================================================================================================================
void PhaseCatcher_Begin_3()
{
  reg8 fill_sample, sum_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= PHASE_CATCHER_READ_3();
  }
  PhaseCatcher_f3.Status = PHASE_CATCHER_STATUS_CALIB;
  PhaseCatcher_f3.Capture.Logic = BitCompare5[sum_sample & 0x1F];
  PhaseCatcher_f3.Capture.SumSample = sum_sample;
  PhaseCatcher_f3.Capture.Counter.Time = 254;
  PhaseCatcher_f3.Capture.Counter.Error = PhaseCatcher_f3.Capture.Counter.Ok = 255;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Catch_3()
{
  static unsigned char offset_time = 0;
  #if (PHASE_CATCHER_OFFSET_3 != 0)
    static unsigned char count_offset = 0;
    if (count_offset)
    {
      if (!(--count_offset))
      {
        extern void PhaseCatch_3();
        PhaseCatch_3();
        PhaseCatcher_f3.Capture.Counter.Time = 255;
      }
    }
  #endif
  if (PhaseCatcher_f3.Capture.Counter.Time != 254)
    PhaseCatcher_f3.Capture.Counter.Time++;
  if (PhaseCatcher_f3.Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher_f3.Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PHASE_CATCHER_READ_3();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher_f3.Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher_f3.Capture.Logic)
    {
      reg8 time = offset_time;
      if (PhaseCatcher_f3.Capture.Stage)
      {
        if (time == ((PHASE_CATCHER_WIDTH_TIME_3 / PHASE_CATCHER_TRIG_TIME_3) - 1))
        {
          time = 255;
          PhaseCatcher_f3.Capture.Stage = 0;
          if (PhaseCatcher_f3.Status == PHASE_CATCHER_STATUS_READY)
          {
            extern void PhaseCatch_3();
            #if (PHASE_CATCHER_OFFSET_3 == 0)
              PhaseCatch_3();
              PhaseCatcher_f3.Capture.Counter.Time = 0;
            #else
              count_offset = PHASE_CATCHER_OFFSET_3;
            #endif
          }
        }
      }
      else if (time >= ((PHASE_CATCHER_WIDTH_TIME_0 + 200) / PHASE_CATCHER_TRIG_TIME_0))
      {
        time = 255;
        PhaseCatcher_f3.Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher_f3.Capture.Counter.Error))
          PhaseCatcher_f3.Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
      time++;
      offset_time = time;
    }
    else
    {
      PhaseCatcher_f3.Capture.Logic = logic;
      if (logic == PHASE_CATCHER_EDGE_3)
      {
        reg8 status = PhaseCatcher_f3.Status;
        PhaseCatcher_f3.Capture.Stage = 1;
        if (status == PHASE_CATCHER_STATUS_CALIB)
          status = PHASE_CATCHER_STATUS_READY;
        else
        {
          if (offset_time > ((PHASE_CATCHER_WIDTH_TIME_3 - 300) / PHASE_CATCHER_TRIG_TIME_3))
          {
            PhaseCatcher_f3.Capture.Counter.Error = 255;
            if (status == PHASE_CATCHER_STATUS_READY)
            {
              extern void PhaseCatch_3();
              #if (PHASE_CATCHER_OFFSET_3 == 0)
                PhaseCatch_3();
                PhaseCatcher_f3.Capture.Counter.Time = 0;
              #else
                count_offset = PHASE_CATCHER_OFFSET_3;
              #endif
            }
            if (!(--PhaseCatcher_f3.Capture.Counter.Ok))
              status = PHASE_CATCHER_STATUS_READY;
          }
          else
          {
            PhaseCatcher_f3.Capture.Counter.Ok = 255;
            if (!(--PhaseCatcher_f3.Capture.Counter.Error))
              status = PHASE_CATCHER_STATUS_AC_ERROR;
          }
        }
        PhaseCatcher_f3.Status = (PHASE_CATCHER_STATUS)status;
        offset_time = 0;
      }
    }
  }
}