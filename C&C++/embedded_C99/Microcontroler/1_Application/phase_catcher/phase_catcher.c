#include <phase_catcher.h>
#include <common.h>
//==============================================================================================================================================================
const unsigned char __code PhaseCatcher_PowerOpenPoint[] = {
//0
  255,
//1     2     3     4     5     6     7     8     9     10
  185,  180,  176,  172,  169,  166,  164,  161,  159,  157,
//11    12    13    14    15    16    17    18    19    20
  155,  153,  151,  149,  147,  146,  144,  142,  141,  139,
//21    22    23    24    25    26    27    28    29    30
  137,  136,  134,  133,  131,  130,  128,  127,  126,  124,
//31    32    33    34    35    36    37    38    39    40
  123,  121,  120,  119,  117,  116,  115,  113,  112,  111,
//41    42    43    44    45    46    47    48    49    50
  110,  108,  107,  106,  104,  103,  102,  101,  99,   98,
//51    52    53    54    55    56    57    58    59    60
  97,   95,   94,   93,   92,   90,   89,   88,   86,   85,
//61    62    63    64    65    66    67    68    69    70
  84,   83,   81,   80,   79,   77,   76,   75,   73,   72,
//71    72    73    74    75    76    77    78    79    80
  70,   69,   68,   66,   65,   63,   62,   60,   59,   57,
//81    82    83    84    85    86    87    88    89    90
  55,   54,   52,   50,   49,   47,   45,   43,   41,   39,
//91    92    93    94    95    96    97    98    99    100
  37,   35,   32,   30,   27,   24,   20,   16,   11,   0
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Begin(PhaseCatcher_TypeDef* PhaseCatcher, reg8 (ReadSignal)())
{
  reg8 fill_sample, sum_sample;
  for (fill_sample = 0; fill_sample < 5; fill_sample++)
  {
    sum_sample <<= 1;
    sum_sample |= ReadSignal();
  }
  PhaseCatcher->Status = PHASE_CATCHER_STATUS_CALIB;
  PhaseCatcher->Capture.Logic = BitCompare5[sum_sample & 0x1F];
  PhaseCatcher->Capture.SumSample = sum_sample;
  PhaseCatcher->Capture.Counter.Time = 254;
  PhaseCatcher->Capture.Counter.Error = PhaseCatcher_f0.Capture.Counter.Ok = 255;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_Catch(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction)
{
  if (PhaseCatcherFunction->Counter->Offset)
  {
    if (!(--PhaseCatcherFunction->Counter->Offset))
    {
      PhaseCatcherFunction->PhaseCatch();
      PhaseCatcher->Capture.Counter.Time = 255;
    }
  }
  if (PhaseCatcher->Capture.Counter.Time != 254)
    PhaseCatcher->Capture.Counter.Time++;
  if (PhaseCatcher->Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher->Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PhaseCatcherFunction->ReadSignal();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher->Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher->Capture.Logic)
    {
      if (PhaseCatcherFunction->Counter->Time < PhaseCatcherFunction->Edge.MaxWidth)
        PhaseCatcherFunction->Counter->Time++;
      else
      {
        PhaseCatcherFunction->Counter->Time = 0;
        PhaseCatcher->Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher->Capture.Counter.Error))
          PhaseCatcher->Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
    }
    else
    {
      PhaseCatcher->Capture.Logic = logic;
      if (PhaseCatcher->Status == PHASE_CATCHER_STATUS_CALIB)
        PhaseCatcher->Status = PHASE_CATCHER_STATUS_READY;
      else
      {
        if (PhaseCatcherFunction->Counter->Time > PhaseCatcherFunction->Edge.MinWidth)
        {
          PhaseCatcher->Capture.Counter.Error = 255;
          if (PhaseCatcher->Status == PHASE_CATCHER_STATUS_READY)
          {
            if (PhaseCatcherFunction->Offset[logic])
              PhaseCatcherFunction->Counter->Offset = PhaseCatcherFunction->Offset[logic];
            else
            {
              PhaseCatcherFunction->PhaseCatch();
              PhaseCatcher->Capture.Counter.Time = 0;
            }
          }
          if (!(--PhaseCatcher->Capture.Counter.Ok))
            PhaseCatcher->Status = PHASE_CATCHER_STATUS_READY;
        }
        else
        {
          PhaseCatcher->Capture.Counter.Ok = 255;
          if (!(--PhaseCatcher->Capture.Counter.Error))
            PhaseCatcher->Status = PHASE_CATCHER_STATUS_AC_ERROR;
        }
      }
      PhaseCatcherFunction->Counter->Time = 0;
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void PhaseCatcher_CatchEdge(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction)
{
  if (PhaseCatcherFunction->Counter->Offset)
  {
    if (!(--PhaseCatcherFunction->Counter->Offset))
    {
      PhaseCatcherFunction->PhaseCatch();
      PhaseCatcher->Capture.Counter.Time = 255;
    }
  }
  if (PhaseCatcher->Capture.Counter.Time != 254)
    PhaseCatcher->Capture.Counter.Time++;
  if (PhaseCatcher->Status)
  {
    reg8 logic;
    {
      reg8 sum_sample = PhaseCatcher->Capture.SumSample;
      sum_sample <<= 1;
      sum_sample |= PhaseCatcherFunction->ReadSignal();
      logic = BitCompare5[sum_sample & 0x1F];
      PhaseCatcher->Capture.SumSample = sum_sample;
    }
    if (logic == PhaseCatcher->Capture.Logic)
    {
      reg8 time = PhaseCatcherFunction->Counter->Time;
      if (PhaseCatcher->Capture.Stage)
      {
        if (time == PhaseCatcherFunction->Edge.WidthTime)
        {
          time = 255;
          PhaseCatcher->Capture.Stage = 0;
          if (PhaseCatcher->Status == PHASE_CATCHER_STATUS_READY)
          {
            if (PhaseCatcherFunction->Offset[0])
              PhaseCatcherFunction->Counter->Offset = PhaseCatcherFunction->Offset[0];
            else
            {
              PhaseCatcherFunction->PhaseCatch();
              PhaseCatcher->Capture.Counter.Time = 0;
            }
          }
        }
      }
      else if (time >= PhaseCatcherFunction->Edge.MaxWidth)
      {
        time = 255;
        PhaseCatcher->Capture.Counter.Ok = 255;
        if (!(--PhaseCatcher->Capture.Counter.Error))
          PhaseCatcher->Status = PHASE_CATCHER_STATUS_AC_ERROR;
      }
      time++;
      PhaseCatcherFunction->Counter->Time = time;
    }
    else
    {
      PhaseCatcher->Capture.Logic = logic;
      if (logic == PhaseCatcherFunction->Edge.CatchAt)
      {
        reg8 status = PhaseCatcher->Status;
        PhaseCatcher->Capture.Stage = 1;
        if (status == PHASE_CATCHER_STATUS_CALIB)
          status = PHASE_CATCHER_STATUS_READY;
        else
        {
          if (PhaseCatcherFunction->Counter->Time > PhaseCatcherFunction->Edge.MinWidth)
          {
            PhaseCatcher->Capture.Counter.Error = 255;
            if (status == PHASE_CATCHER_STATUS_READY)
            {
              if (PhaseCatcherFunction->Offset[0])
                PhaseCatcherFunction->Counter->Offset = PhaseCatcherFunction->Offset[0];
              else
              {
                PhaseCatcherFunction->PhaseCatch();
                PhaseCatcher->Capture.Counter.Time = 0;
              }
            }
            if (!(--PhaseCatcher->Capture.Counter.Ok))
              status = PHASE_CATCHER_STATUS_READY;
          }
          else
          {
            PhaseCatcher->Capture.Counter.Ok = 255;
            if (!(--PhaseCatcher->Capture.Counter.Error))
              status = PHASE_CATCHER_STATUS_AC_ERROR;
          }
        }
        PhaseCatcher->Status = (PHASE_CATCHER_STATUS)status;
        PhaseCatcherFunction->Counter->Time = 0;
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
reg8 PhaseCatcher_PowerProcessAdvanced(PhaseCatcher_TypeDef* PhaseCatcher, const PhaseCatcherFunction_TypeDef __code* PhaseCatcherFunction, reg8 PowerPercent)
{
  if (PowerPercent && PhaseCatcher->Status == PHASE_CATCHER_STATUS_READY)
  {
    reg8 point = PhaseCatcher_PowerOpenPoint[PowerPercent] * PhaseCatcherFunction->Edge.WidthTime / 200;
    if (PhaseCatcher->Capture.Counter.Time == point)
      return 1;
    else if (PhaseCatcher->Capture.Counter.Time == point + 4)
      return 2;
  }
  return 0;
}