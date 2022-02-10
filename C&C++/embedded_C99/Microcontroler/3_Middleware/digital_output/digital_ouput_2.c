#include <digital_output.h>
//==============================================================================================================================================================
void DigitalOutput_Begin_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction)
{
  DigitalOutput_TypeDef* DigitalOutput = DigitalOutputFunction->DigitalOutput;
  DigitalOutput->IsOn = DigitalOutput->CountEdgeTime = DigitalOutput->Times = 0;
  DigitalOutputFunction->DigitalOutputTurn(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction)
{
  void (*Finish)(reg8 DigitalOutputIndex) = DigitalOutputFunction->Finish;
  DigitalOutput_TypeDef* DigitalOutput = DigitalOutputFunction->DigitalOutput;
  if (DigitalOutput->Times)
  {
    if (++DigitalOutput->CountEdgeTime > DigitalOutput->EdgeTime)
    {
      DigitalOutput->CountEdgeTime = 1;
      DigitalOutputFunction->DigitalOutputTurn(0, (DigitalOutput->IsOn = !DigitalOutput->IsOn));
      if (DigitalOutput->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutput->Times) && Finish)
          Finish(0);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 Times, reg8 EdgeTime)
{
  DigitalOutput_TypeDef* DigitalOutput = DigitalOutputFunction->DigitalOutput;
  DigitalOutputFunction->DigitalOutputTurn(0, DigitalOutput->IsOn = 0);
  DigitalOutput->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutput->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutput->Times = Times << 1;
  DigitalOutput->EdgeTime = EdgeTime;
}