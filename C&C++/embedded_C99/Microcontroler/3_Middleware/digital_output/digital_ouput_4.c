#include <digital_output.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalOutputEx_TypeDef DigitalOutputEx_f4;
//==============================================================================================================================================================
void DigitalOutput_Begin_4()
{
  DigitalOutputEx_f4.IsOn = DigitalOutputEx_f4.CountEdgeTime = DigitalOutputEx_f4.Times = 0;
  DIGITAL_OUTPUT_EX_TURN_4(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_4(void Finish())
{
  if (DigitalOutputEx_f4.Times)
  {
    if (++DigitalOutputEx_f4.CountEdgeTime > DigitalOutputEx_f4.EdgeTime[DigitalOutputEx_f4.IsOn])
    {
      DigitalOutputEx_f4.CountEdgeTime = 1;
      DIGITAL_OUTPUT_EX_TURN_4((DigitalOutputEx_f4.IsOn = !DigitalOutputEx_f4.IsOn));
      if (DigitalOutputEx_f4.Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutputEx_f4.Times) && Finish)
          Finish();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_4(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  DigitalOutputEx_f4.IsOn = 0;
  DIGITAL_OUTPUT_EX_TURN_4(0);
  DigitalOutputEx_f4.CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutputEx_f4.Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutputEx_f4.Times = Times << 1;
  DigitalOutputEx_f4.EdgeTime[1] = HighEdgeTime;
  DigitalOutputEx_f4.EdgeTime[0] = LowEdgeTime;
}