#include <digital_output.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalOutput_TypeDef DigitalOutput_f1[DIGITAL_OUTPUT_QUANTITY_1];
void DigitalOutput_Turn_1(reg8 DigitalOutputIndex, reg8 IsOn);
//==============================================================================================================================================================
void DigitalOutput_Begin_1()
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DIGITAL_OUTPUT_QUANTITY_1; DigitalOutputIndex++)
  {
    DigitalOutput_TypeDef* DigitalOutput = &DigitalOutput_f1[DigitalOutputIndex];
    DigitalOutput->IsOn = DigitalOutput->CountEdgeTime = DigitalOutput->Times = 0;
    DigitalOutput_Turn_1(DigitalOutputIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessIndex_1(reg8 DigitalOutputIndex, void Finish(reg8 DigitalOutputIndex))
{
  DigitalOutput_TypeDef* DigitalOutput = &DigitalOutput_f1[DigitalOutputIndex];
  if (DigitalOutput->Times)
  {
    if (++DigitalOutput->CountEdgeTime > DigitalOutput->EdgeTime)
    {
      DigitalOutput->CountEdgeTime = 1;
      DigitalOutput_Turn_1(DigitalOutputIndex, (DigitalOutput->IsOn = !DigitalOutput->IsOn));
      if (DigitalOutput->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutput->Times) && Finish)
          Finish(DigitalOutputIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Process_1(void Finish(reg8 DigitalOutputIndex))
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DIGITAL_OUTPUT_QUANTITY_1; DigitalOutputIndex++)
    DigitalOutput_ProcessIndex_1(DigitalOutputIndex, Finish);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Blink_1(reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime)
{
  DigitalOutput_TypeDef* DigitalOutput = &DigitalOutput_f1[DigitalOutputIndex];
  DigitalOutput_Turn_1(DigitalOutputIndex, DigitalOutput->IsOn = 0);
  DigitalOutput->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutput->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutput->Times = Times << 1;
  DigitalOutput->EdgeTime = EdgeTime;
}