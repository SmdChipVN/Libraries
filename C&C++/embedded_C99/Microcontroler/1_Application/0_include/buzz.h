/*
MODE 0:
  +) Config:
    #define TURN_BUZZ_0(IsOn)     BUZZ_PIN=IsOn
  +) Declare:
    __no_init Buzz_TypeDef Buzz0;
  +) Using:
    void Buzz_Begin_0();
    void Buzz_Process_0(void Finish());
    void Buzz_Ring_0(reg8 Times, reg8 Period);
MODE 1:
  +) Config:
    #define NUMBER_OF_BUZZ_1    2
  +) Declare
    __no_init Buzz_TypeDef Buzz1[NUMBER_OF_BUZZ_1];
    void TurnBuzz1(reg8 BuzzIndex, reg8 IsOn);
  +) Using:
    void Buzz_Begin_1();
    void Buzz_Process_1(void Finish(reg8 BuzzIndex));
    void Buzz_Ring_1(reg8 BuzzIndex, reg8 Times, reg8 Period);
MODE 2:
  +) Config:
  +) Declare:
  +) Using:
    void Buzz_Begin_2(const BuzzFunction_TypeDef* BuzzFunction);
    void Buzz_Process_2(const BuzzFunction_TypeDef* BuzzFunction);
    void Buzz_Ring_2(const BuzzFunction_TypeDef* BuzzFunction, reg8 BuzzIndex, reg8 Times, reg8 Period);
MODE 3:
  +) Config:
    #define TURN_BUZZ_EX_3(IsOn)        BUZZ_PIN=IsOn
  +) Declare:
    __no_init BuzzEx_TypeDef BuzzEx3;
  +) Using:
    void Buzz_Begin_3();
    void Buzz_Process_3(void Finish());
    void Buzz_Ring_3(reg8 Times, reg8 HighPeriod, reg8 LowPeriod);
MODE 4:
  +) Config:
    #define NUMBER_OF_BUZZ_EX_4         2
  +) Declare
    __no_init BuzzEx_TypeDef BuzzEx4[NUMBER_OF_BUZZ_EX_4];
    void TurnBuzzEx4(reg8 BuzzIndex, reg8 IsOn);
  +) Using:
    void Buzz_Begin_4();
    void Buzz_Process_4(void Finish(reg8 BuzzIndex));
    void Buzz_Ring_4(reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod);
MODE 5:
  +) Config:
  +) Declare:
  +) Using:
    void Buzz_Begin_5(const BuzzExFunction_TypeDef* BuzzExFunction);
    void Buzz_Process_5(const BuzzExFunction_TypeDef* BuzzExFunction);
    void Buzz_Ring_5(const BuzzExFunction_TypeDef* BuzzExFunction, reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod);
*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _BUZZ_H_
#define _BUZZ_H_

#define BUZZ_ALWAYS_RING        0xFF

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char Count;
  unsigned char Period;
} Buzz_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  Buzz_TypeDef* Buzz;
  unsigned char NumberOfBuzz;
  void(*TurnBuzz)(reg8 BuzzIndex, reg8 IsOn);
  void(*Finish)(reg8 BuzzIndex);
} BuzzFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_0();
void Buzz_Process_0(void Finish());
void Buzz_Ring_0(reg8 Times, reg8 Period);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_1();
void Buzz_Process_1(void Finish(reg8 BuzzIndex));
void Buzz_Ring_1(reg8 BuzzIndex, reg8 Times, reg8 Period);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_2(const BuzzFunction_TypeDef* BuzzFunction);
void Buzz_Process_2(const BuzzFunction_TypeDef* BuzzFunction);
void Buzz_Ring_2(const BuzzFunction_TypeDef* BuzzFunction, reg8 BuzzIndex, reg8 Times, reg8 Period);
//==============================================================================================================================================================
typedef struct
{
  unsigned char IsOn;
  unsigned char Times;
  unsigned char Count;
  unsigned char LowPeriod;
  unsigned char HighPeriod;
} BuzzEx_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  BuzzEx_TypeDef* BuzzEx;
  unsigned char NumberOfBuzz;
  void(*TurnBuzz)(reg8 BuzzIndex, reg8 IsOn);
  void(*Finish)(reg8 BuzzIndex);
} BuzzExFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_3();
void Buzz_Process_3(void Finish());
void Buzz_Ring_3(reg8 Times, reg8 HighPeriod, reg8 LowPeriod);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_4();
void Buzz_Process_4(void Finish(reg8 BuzzIndex));
void Buzz_Ring_4(reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Buzz_Begin_5(const BuzzExFunction_TypeDef* BuzzExFunction);
void Buzz_Process_5(const BuzzExFunction_TypeDef* BuzzExFunction);
void Buzz_Ring_5(const BuzzExFunction_TypeDef* BuzzExFunction, reg8 BuzzIndex, reg8 Times, reg8 HighPeriod, reg8 LowPeriod);

#endif