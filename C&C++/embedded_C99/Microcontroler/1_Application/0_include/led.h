/*
MODE 0:
  +) Config:
    #define TURN_LED_0(IsOn)     LED_PIN=IsOn
  +) Declare:
    __no_init Led_TypeDef Led0;
  +) Using:
    void Led_Begin_0();
    void Led_Process_0(void Finish());
    void Led_Blink_0(reg8 Times, reg8 EdgeTime);
MODE 1:
  +) Config:
    #define LED_QUANTITY_1     2
  +) Declare
    __no_init Led_TypeDef Led1[LED_QUANTITY_1];
    void TurnLed1(reg8 LedIndex, reg8 IsOn);
  +) Using:
    void Led_Begin_1();
    void Led_Process_1(void Finish(reg8 LedIndex));
    void Led_Blink_1(reg8 LedIndex, reg8 Times, reg8 EdgeTime);
MODE 2:
  +) Config:
  +) Declare:
  +) Using:
    void Led_Begin_2(const LedFunction_TypeDef __code* LedFunction);
    void Led_Process_2(const LedFunction_TypeDef __code* LedFunction);
    void Led_Blink_2(const LedFunction_TypeDef __code* LedFunction, reg8 LedIndex, reg8 Times, reg8 EdgeTime);
MODE 3:
  +) Config:
    #define TURN_LED_EX_3(IsOn)     LED_PIN=IsOn
  +) Declare:
    __no_init LedEx_TypeDef LedEx3;
  +) Using:
    void Led_Begin_3();
    void Led_Process_3(void Finish());
    void Led_Blink_3(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
MODE 4:
  +) Config:
    #define LED_QUANTITY_EX_4  2
  +) Declare
    __no_init LedEx_TypeDef LedEx4[LED_QUANTITY];
    void TurnLedEx4(reg8 LedIndex, reg8 IsOn);
  +) Using:
    void Led_Begin_4();
    void Led_Process_4(void Finish(reg8 LedIndex));
    void Led_Blink_4(reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
MODE 5:
  +) Config:
  +) Declare:
  +) Using:
    void Led_Begin_5(const LedFunction_TypeDef* LedExFunction);
    void Led_Process_5(const LedFunction_TypeDef* LedExFunction);
    void Led_Blink_5(const LedFunction_TypeDef* LedExFunction, reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _LED_H_
#define _LED_H_

#define LED_ALWAYS_BLINK        0xFF

#include <common.h>
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char CountEdgeTime;
  unsigned char EdgeTime;
} Led_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char CountEdgeTime;
  unsigned char EdgeTime[2];
} LedEx_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  union
  {
    Led_TypeDef* Led;
    LedEx_TypeDef* LedEx;
  };
  unsigned char NumberOfLed;
  void(*LedTurn)(reg8 LedIndex, reg8 IsOn);
  void(*Finish)(reg8 LedIndex);
} LedFunction_TypeDef;
//==============================================================================================================================================================
void Led_Begin_0();
void Led_Process_0(void Finish());
void Led_Blink_0(reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Begin_1(); 
void Led_Process_1(void Finish(reg8 LedIndex));
void Led_ProcessIndex_1(reg8 LedIndex, void Finish(reg8 LedIndex));
void Led_Blink_1(reg8 LedIndex, reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Begin_2(const LedFunction_TypeDef __code* LedFunction);
void Led_Process_2(const LedFunction_TypeDef __code* LedFunction);
void Led_Blink_2(const LedFunction_TypeDef __code* LedFunction, reg8 Times, reg8 EdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Led_Begin_3(const LedFunction_TypeDef __code* LedFunction);
void Led_Process_3(const LedFunction_TypeDef __code* LedFunction);
void Led_ProcessIndex_3(const LedFunction_TypeDef __code* LedFunction, reg8 LedIndex);
void Led_Blink_3(const LedFunction_TypeDef __code* LedFunction, reg8 LedIndex, reg8 Times, reg8 EdgeTime);
//==============================================================================================================================================================
void LedEx_Begin_0(); 
void LedEx_Process_0(void Finish());
void LedEx_Blink_0(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void LedEx_Begin_1(); 
void LedEx_Process_1(void Finish(reg8 LedIndex));
void LedEx_ProcessIndex_1(void Finish(reg8 LedIndex));
void LedEx_Blink_1(reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void LedEx_Begin_2(const LedFunction_TypeDef* LedExFunction);
void LedEx_Process_2(const LedFunction_TypeDef* LedExFunction);
void LedEx_Blink_2(const LedFunction_TypeDef* LedExFunction, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void LedEx_Begin_3(const LedFunction_TypeDef* LedExFunction);
void LedEx_Process_3(const LedFunction_TypeDef* LedExFunction);
void LedEx_ProcessIndex_3(const LedFunction_TypeDef* LedExFunction, reg8 LedIndex);
void LedEx_Blink_3(const LedFunction_TypeDef* LedExFunction, reg8 LedIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime);

#endif