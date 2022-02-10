#include <digital_output.h>
//==============================================================================================================================================================
void DigitalOutput_Begin_7(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction)
{
  void(*DigitalOutputTurn)(reg8 DigitalOutputIndex, reg8 IsOn) = DigitalOutputExFunction->DigitalOutputTurn;
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DigitalOutputExFunction->NumberOfDigitalOutput; DigitalOutputIndex++)
  {
    DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputExFunction->DigitalOutputEx[DigitalOutputIndex];
    DigitalOutputEx->IsOn = DigitalOutputEx->CountEdgeTime = DigitalOutputEx->Times = 0;
    DigitalOutputTurn(DigitalOutputIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessIndex_7(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction, reg8 DigitalOutputIndex)
{
  void (*Finish)(reg8 DigitalOutputIndex) = DigitalOutputExFunction->Finish;
  DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputExFunction->DigitalOutputEx[DigitalOutputIndex];
  if (DigitalOutputEx->Times)
  {
    if (++DigitalOutputEx->CountEdgeTime > DigitalOutputEx->EdgeTime[DigitalOutputEx->IsOn])
    {
      DigitalOutputEx->CountEdgeTime = 1;
      DigitalOutputExFunction->DigitalOutputTurn(DigitalOutputIndex, (DigitalOutputEx->IsOn = !DigitalOutputEx->IsOn));
      if (DigitalOutputEx->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutputEx->Times) && Finish)
          Finish(DigitalOutputIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_7(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction)
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DigitalOutputExFunction->NumberOfDigitalOutput; DigitalOutputIndex++)
    DigitalOutput_ProcessIndex_7(DigitalOutputExFunction, DigitalOutputIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_7(const DigitalOutputFunction_TypeDef __code* DigitalOutputExFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputExFunction->DigitalOutputEx[DigitalOutputIndex];
  DigitalOutputExFunction->DigitalOutputTurn(DigitalOutputIndex, (DigitalOutputEx->IsOn = 0));
  DigitalOutputEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutputEx->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutputEx->Times = Times * 2;
  DigitalOutputEx->EdgeTime[1] = HighEdgeTime;
  DigitalOutputEx->EdgeTime[0] = LowEdgeTime;
}