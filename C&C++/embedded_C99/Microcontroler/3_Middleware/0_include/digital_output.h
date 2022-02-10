/*
+) NOTE:
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
+) Example:
    void DigitalOutput_Turn(reg8 DigitalOutputIndex, reg8 IsOn)
    {
      switch (DigitalOutputIndex)
      {
        case 0: GPIOB.ODR.BITS.b12 = IsOn; break;
      }
    }
    static const DigitalOutputFunction_TypeDef __code DigitalOutputFunction = 
    {
        .DigitalOutput = ,
        .DigitalOutputEx = ,
      .DigitalOutputTurn = DigitalOutput_Turn,
      .Finish = NULL,
      .NumberOfDigitalOutput = 1,
    };
//==============================================================================================================================================================
MODE 0:
  +) Config:
      #define DIGITAL_OUTPUT_TURN_0(IsOn)             //
  +) Declare:
      __no_init DigitalOutput_TypeDef DigitalOutput_f0;
  +) Using:
      void DigitalOutput_Begin_0();
      void DigitalOutput_Process_0(void Finish());
      void DigitalOutput_Blink_0(reg8 Times, reg8 EdgeTime);
MODE 1:
  +) Config:
      #define DIGITAL_OUTPUT_QUANTITY_1               2
  +) Declare
      __no_init DigitalOutput_TypeDef DigitalOutput_f1[DIGITAL_OUTPUT_QUANTITY_1];
      void DigitalOutput_Turn_1(reg8 DigitalOutputIndex, reg8 IsOn);
  +) Using:
      void DigitalOutput_Begin_1(); 
      void DigitalOutput_Process_1(void Finish(reg8 DigitalOutputIndex));
      void DigitalOutput_ProcessIndex_1(reg8 DigitalOutputIndex, void Finish(reg8 DigitalOutputIndex));
      void DigitalOutput_Blink_1(reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime);
MODE 2:
  +) Config:
  +) Declare:
  +) Using:     (un-use: DigitalOutputFunction->NumberOfDigitalOutput)
      void DigitalOutput_Begin_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
      void DigitalOutput_Process_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
      void DigitalOutput_Blink_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 Times, reg8 EdgeTime);
MODE 3:
  +) Config:
  +) Declare:
  +) Using:
      void DigitalOutput_Begin_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
      void DigitalOutput_Process_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
      void DigitalOutput_ProcessIndex_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex);
      void DigitalOutput_Blink_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime);
MODE 4:
  +) Config:
      #define DIGITAL_OUTPUT_EX_TURN_4(IsOn)          //
  +) Declare
      __no_init DigitalOutputEx_TypeDef DigitalOutputEx_f4;
  +) Using:
      void DigitalOutput_Begin_4();
      void DigitalOutput_Process_4(void Finish());
      void DigitalOutput_Blink_4(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
MODE 5:
  +) Config:
      #define DIGITAL_OUTPUT_EX_QUANTITY_5            2
  +) Declare:
      __no_init DigitalOutputEx_TypeDef DigitalOutputEx_f5[DIGITAL_OUTPUT_EX_QUANTITY_5];
      void DigitalOutputEx_Turn_5(reg8 DigitalOutputIndex, reg8 IsOn);
  +) Using:
      void DigitalOutput_Begin_5(); 
      void DigitalOutput_Process_5(void Finish(reg8 DigitalOutputIndex));
      void DigitalOutput_ProcessIndex_5(void Finish(reg8 DigitalOutputIndex));
      void DigitalOutput_Blink_5(reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
MODE 6:
  +) Config:
  +) Declare:
  +) Using:     (un-use: DigitalOutputFunction->NumberOfDigitalOutput)
      void DigitalOutput_Begin_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
      void DigitalOutput_Process_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
      void DigitalOutput_Blink_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
MODE 7:
  +) Config:
  +) Declare:
  +) Using:
      void DigitalOutput_Begin_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
      void DigitalOutput_Process_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
      void DigitalOutput_ProcessIndex_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 DigitalOutputIndex);
      void DigitalOutput_Blink_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

#define DIGITAL_OUTPUT_ALWAYS_BLINK        0xFF

#include <common.h>
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char CountEdgeTime;
  unsigned char EdgeTime;
} DigitalOutput_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char CountEdgeTime;
  unsigned char EdgeTime[2];
} DigitalOutputEx_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  union
  {
    DigitalOutput_TypeDef* DigitalOutput;
    DigitalOutputEx_TypeDef* DigitalOutputEx;
  };
  void (*DigitalOutputTurn)(reg8 DigitalOutputIndex, reg8 IsOn);
  void (*Finish)(reg8 DigitalOutputIndex);
  unsigned char NumberOfDigitalOutput;
} DigitalOutputFunction_TypeDef;
//==============================================================================================================================================================
void DigitalOutput_Begin_0();
void DigitalOutput_Process_0(void Finish());
void DigitalOutput_Blink_0(reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_1(); 
void DigitalOutput_Process_1(void Finish(reg8 DigitalOutputIndex));
void DigitalOutput_ProcessIndex_1(reg8 DigitalOutputIndex, void Finish(reg8 DigitalOutputIndex));
void DigitalOutput_Blink_1(reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
void DigitalOutput_Process_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
void DigitalOutput_Blink_2(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
void DigitalOutput_Process_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction);
void DigitalOutput_ProcessIndex_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex);
void DigitalOutput_Blink_3(const DigitalOutputFunction_TypeDef __code* DigitalOutputFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 EdgeTime);
//==============================================================================================================================================================
void DigitalOutput_Begin_4(); 
void DigitalOutput_Process_4(void Finish());
void DigitalOutput_Blink_4(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_5(); 
void DigitalOutput_Process_5(void Finish(reg8 DigitalOutputIndex));
void DigitalOutput_ProcessIndex_5(reg8 DigitalOutputIndex, void Finish(reg8 DigitalOutputIndex));
void DigitalOutput_Blink_5(reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
void DigitalOutput_Process_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
void DigitalOutput_Blink_6(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_Begin_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
void DigitalOutput_Process_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction);
void DigitalOutput_ProcessIndex_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 DigitalOutputIndex);
void DigitalOutput_Blink_7(const DigitalOutputFunction_TypeDef* DigitalOutputExFunction, reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);

#endif