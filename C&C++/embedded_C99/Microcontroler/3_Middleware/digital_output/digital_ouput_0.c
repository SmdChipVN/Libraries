#include <digital_output.h>
#include <config.h>

extern __no_init DigitalOutput_TypeDef DigitalOutput_f0;
//==============================================================================================================================================================
void DigitalOutput_Begin_0()
{
  DigitalOutput_f0.IsOn = DigitalOutput_f0.CountEdgeTime = DigitalOutput_f0.Times = 0;
  DIGITAL_OUTPUT_TURN_0(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_0(void Finish())
{
  if (DigitalOutput_f0.Times)
  {
    if (++DigitalOutput_f0.CountEdgeTime > DigitalOutput_f0.EdgeTime)
    {
      DigitalOutput_f0.CountEdgeTime = 1;
      DIGITAL_OUTPUT_TURN_0((DigitalOutput_f0.IsOn = !DigitalOutput_f0.IsOn));
      if (DigitalOutput_f0.Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutput_f0.Times) && Finish)
          Finish();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_0(reg8 Times, reg8 EdgeTime)
{
  DigitalOutput_f0.IsOn = 0;
  DIGITAL_OUTPUT_TURN_0(0);
  DigitalOutput_f0.CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutput_f0.Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutput_f0.Times = Times << 1;
  DigitalOutput_f0.EdgeTime = EdgeTime;
}