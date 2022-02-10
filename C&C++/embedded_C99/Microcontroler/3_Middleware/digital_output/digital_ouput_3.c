#include <digital_output.h>
//==============================================================================================================================================================
void DigitalOutput_Begin_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction)
{
  void (*DigitalOutputTurn)(reg8 DigitalOutputIndex, reg8 IsOn) = DigitalOutputFunction->DigitalOutputTurn;
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DigitalOutputFunction->NumberOfDigitalOutput; DigitalOutputIndex++)
  {
    DigitalOutput_TypeDef* DigitalOutput = &DigitalOutputFunction->DigitalOutput[DigitalOutputIndex];
    DigitalOutput->IsOn = DigitalOutput->CountEdgeTime = DigitalOutput->Times = 0;
    DigitalOutputTurn(DigitalOutputIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessIndex_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex)
{
  DigitalOutput_TypeDef* DigitalOutput = &DigitalOutputFunction->DigitalOutput[DigitalOutputIndex];
  void(*Finish)(reg8 DigitalOutputIndex) = DigitalOutputFunction->Finish;
  if (DigitalOutput->Times)
  {
    if (++DigitalOutput->CountEdgeTime > DigitalOutput->EdgeTime)
    {
      DigitalOutput->CountEdgeTime = 1;
      DigitalOutputFunction->DigitalOutputTurn(DigitalOutputIndex, (DigitalOutput->IsOn = !DigitalOutput->IsOn));
      if (DigitalOutput->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutput->Times) && Finish)
          Finish(DigitalOutputIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction)
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DigitalOutputFunction->NumberOfDigitalOutput; DigitalOutputIndex++)
    DigitalOutput_ProcessIndex_3(DigitalOutputFunction, DigitalOutputIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime)
{
  DigitalOutput_TypeDef* DigitalOutput = &DigitalOutputFunction->DigitalOutput[DigitalOutputIndex];
  DigitalOutputFunction->DigitalOutputTurn(DigitalOutputIndex, DigitalOutput->IsOn = 0);
  DigitalOutput->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutput->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutput->Times = Times * 2;
  DigitalOutput->EdgeTime = EdgeTime;
}