#include <digital_output.h>
//==============================================================================================================================================================
void DigitalOutput_Begin_6(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction)
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = DigitalOutputExFunction->DigitalOutputEx;
  DigitalOutputEx->IsOn = DigitalOutputEx->CountEdgeTime = DigitalOutputEx->Times = 0;
  DigitalOutputExFunction->DigitalOutputTurn(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_6(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction)
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = DigitalOutputExFunction->DigitalOutputEx;
  if (DigitalOutputEx->Times)
  {
    if (++DigitalOutputEx->CountEdgeTime > DigitalOutputEx->EdgeTime[DigitalOutputEx->IsOn])
    {
      DigitalOutputEx->CountEdgeTime = 1;
      DigitalOutputExFunction->DigitalOutputTurn(0, (DigitalOutputEx->IsOn = !DigitalOutputEx->IsOn));
      if (DigitalOutputEx->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutputEx->Times) && DigitalOutputExFunction->Finish)
          DigitalOutputExFunction->Finish(0);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_6(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = DigitalOutputExFunction->DigitalOutputEx;
  DigitalOutputExFunction->DigitalOutputTurn(0, (DigitalOutputEx->IsOn = 0));
  DigitalOutputEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutputEx->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutputEx->Times = Times << 1;
  DigitalOutputEx->EdgeTime[1] = HighEdgeTime;
  DigitalOutputEx->EdgeTime[0] = LowEdgeTime;
}