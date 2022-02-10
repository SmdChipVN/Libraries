/*
+) Over-write:
    DIGITAL_INPUT_      -> <USER-NAME>_
    DigitalInput        -> <user-name>
+) NOTE:
    DigitalInput_Check().Status = DIGITAL_INPUT_STATUS_DOWN (BIT0) or DIGITAL_INPUT_STATUS_UP (BIT1)
    DigitalInput_Check().ClearStatus = BIT2
    -) maybe define for quick stack process compare by 5 (fix) sample times
    #define DIGITAL_INPUT_QUICK_STACK_<mode>          5
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
+) Example:
    reg8 DigitalInput_Read(reg8 DigitalInputIndex);
    {
      switch (DigitalInputIndex)
      {
        case 0: return GPIOB.IDR.BITS.b7;
      }
      return 2;
    }
    static const DigitalInputFunction_TypeDef __code DigitalInputFunction = 
    {
      .DigitalInput = ,
      .DigitalInputRead = DigitalInput_Read,
      .SampleTimes = 5,
      .SampleDivider = 4,
      .NumberOfDigitalInput = 2,
    };
//==============================================================================================================================================================
MODE 0:
  +) Config:
      #define DIGITAL_INPUT_SAMPLE_TIMES_0            5
      #define DIGITAL_INPUT_SAMPLE_DIVIDER_0          4
      #define DIGITAL_INPUT_READ_0()                  GPIOB.IDR.BITS.b7
  +) Declare:
      __no_init DigitalInput_TypeDef DigitalInput_f0;
  +) Using:
      void DigitalInput_BeginStack_0();
      void DigitalInput_ProcessStack_0();

      void DigitalInput_Begin_0();
      reg8 DigitalInput_Process_0();
      reg8 DigitalInput_Check_0(reg8 Status, reg8 ClearStatus);
//==============================================================================================================================================================
MODE 1:
  +) Config:
      #define DIGITAL_INPUT_QUANTITY_1                2
      #define DIGITAL_INPUT_SAMPLE_TIMES_1            5
      #define DIGITAL_INPUT_SAMPLE_DIVIDER_1          4
  +) Declare:
      __no_init DigitalInput_TypeDef DigitalInput_f1[DIGITAL_INPUT_QUANTITY_1];
      reg8 DigitalInput_Read_1(reg8 DigitalInputIndex);
  +) Using:
      void DigitalInput_BeginStack_1();
      reg8 DigitalInput_ProcessIndexStack_1(reg8 DigitalInputIndex);
      void DigitalInput_ProcessStack_1();

      void DigitalInput_Begin_1();
      reg8 DigitalInput_ProcessIndex_1(reg8 DigitalInputIndex, reg8 CountSample);
      reg8 DigitalInput_Process_1();
      reg8 DigitalInput_Check_1(reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus);
MODE 2:
//==============================================================================================================================================================
  +) Config:
  +) Declare:
  +) Using:     (un-use: DigitalInputFunction->NumberOfDigitalInput)
      void DigitalInput_BeginStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);
      void DigitalInput_ProcessStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);

      reg8 DigitalInput_Begin_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);
      reg8 DigitalInput_Process_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction, reg8 CountSample);
      reg8 DigitalInput_Check_2(DigitalInput_TypeDef* DigitalInput, reg8 Status, reg8 ClearStatus);
MODE 3:
//==============================================================================================================================================================
  +) Config:
  +) Declare:
  +) Using:
      void DigitalInput_BeginStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction);
      reg8 DigitalInput_ProcessIndexStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex);
      void DigitalInput_ProcessStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction);

      void DigitalInput_Begin_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample);
      reg8 DigitalInput_ProcessIndex_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 CountSample);
      reg8 DigitalInput_Process_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample);
      reg8 DigitalInput_Check_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus);
*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

#define DIGITAL_INPUT_STATUS_DOWN      BIT0     //1, voltage: 0, clear -> BIT0 | BIT2
#define DIGITAL_INPUT_STATUS_UP        BIT1     //2, voltage: VCC, clear -> BIT1 | BIT2

#include <common.h>
typedef struct
{
  unsigned char Logic;
  unsigned char SumSample;
  unsigned char Status;
} DigitalInput_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  DigitalInput_TypeDef* DigitalInput;
  reg8 (*DigitalInputRead)(reg8 DigitalInputIndex);
  unsigned char SampleTimes;
  unsigned char SampleDivider;
  union
  {
    unsigned char DigitalInputIndex;            //MODE 2
    unsigned char NumberOfDigitalInput;         //MODE 3
  };
} DigitalInputFunction_TypeDef;
//==============================================================================================================================================================
void DigitalInput_BeginStack_0();
reg8 DigitalInput_ProcessStack_0();

void DigitalInput_Begin_0();
reg8 DigitalInput_Process_0();
reg8 DigitalInput_Check_0(reg8 Status, reg8 ClearStatus);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_BeginStack_1();
reg8 DigitalInput_ProcessIndexStack_1(reg8 DigitalInputIndex);
void DigitalInput_ProcessStack_1();

void DigitalInput_Begin_1();
reg8 DigitalInput_ProcessIndex_1(reg8 DigitalInputIndex, reg8 CountSample);
reg8 DigitalInput_Process_1();
reg8 DigitalInput_Check_1(reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_BeginStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);
reg8 DigitalInput_ProcessStack_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);

reg8 DigitalInput_Begin_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction);
reg8 DigitalInput_Process_2(const DigitalInputFunction_TypeDef __gptr* DigitalInputFunction, reg8* CountSample);
reg8 DigitalInput_Check_2(DigitalInput_TypeDef* DigitalInput, reg8 Status, reg8 ClearStatus);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalInput_BeginStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction);
reg8 DigitalInput_ProcessIndexStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex);
void DigitalInput_ProcessStack_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction);

void DigitalInput_Begin_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample);
reg8 DigitalInput_ProcessIndex_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 CountSample);
reg8 DigitalInput_Process_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, unsigned char* CountSample);
reg8 DigitalInput_Check_3(const DigitalInputFunction_TypeDef __code* DigitalInputFunction, reg8 DigitalInputIndex, reg8 Status, reg8 ClearStatus);
//==============================================================================================================================================================
//======================================================        INHERIT HEADER      ============================================================================
//==============================================================================================================================================================
/*
  +) Declare:
      typedef struct
      {
        unsigned char Logic;
        unsigned char SumSample;
        unsigned char Status;
      } TypeName##_TypeDef;
*/
#define DIGITAL_INPUT_INHERIT_HEADER(TypeName)                                                                                                                  \
typedef struct                                                                                                                                                  \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName;                                                                                                                                 \
  reg8 (*TypeName##Read)(reg8 TypeName##Index);                                                                                                                 \
  unsigned char SampleTimes;                                                                                                                                    \
  unsigned char SampleDivider;                                                                                                                                  \
  union                                                                                                                                                         \
  {                                                                                                                                                             \
    unsigned char TypeName##Index;                                                                                                                              \
    unsigned char NumberOf##TypeName;                                                                                                                           \
  };                                                                                                                                                            \
} TypeName##Function_TypeDef;                                                                                                                                   \
void TypeName##_BeginStack_0();                                                                                                                                 \
reg8 TypeName##_ProcessStack_0();                                                                                                                               \
void TypeName##_Begin_0();                                                                                                                                      \
reg8 TypeName##_Process_0();                                                                                                                                    \
reg8 TypeName##_Check_0(reg8 Status, reg8 ClearStatus);                                                                                                         \
                                                                                                                                                                \
void TypeName##_BeginStack_1();                                                                                                                                 \
reg8 TypeName##_ProcessIndexStack_1(reg8 TypeName##Index);                                                                                                      \
void TypeName##_ProcessStack_1();                                                                                                                               \
void TypeName##_Begin_1();                                                                                                                                      \
reg8 TypeName##_ProcessIndex_1(reg8 TypeName##Index, reg8 CountSample);                                                                                         \
reg8 TypeName##_Process_1();                                                                                                                                    \
reg8 TypeName##_Check_1(reg8 TypeName##Index, reg8 Status, reg8 ClearStatus);                                                                                   \
                                                                                                                                                                \
void TypeName##_BeginStack_2(const TypeName##Function_TypeDef __gptr* TypeName##Function);                                                                      \
reg8 TypeName##_ProcessStack_2(const TypeName##Function_TypeDef __gptr* TypeName##Function);                                                                    \
reg8 TypeName##_Begin_2(const TypeName##Function_TypeDef __gptr* TypeName##Function);                                                                           \
reg8 TypeName##_Process_2(const TypeName##Function_TypeDef __gptr* TypeName##Function, reg8 CountSample);                                                       \
reg8 TypeName##_Check_2(TypeName##_TypeDef* Name, reg8 Status, reg8 ClearStatus);                                                                               \
                                                                                                                                                                \
void TypeName##_BeginStack_3(const TypeName##Function_TypeDef __code* TypeName##Function);                                                                      \
reg8 TypeName##_ProcessIndexStack_3(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index);                                         \
void TypeName##_ProcessStack_3(const TypeName##Function_TypeDef __code* TypeName##Function);                                                                    \
void TypeName##_Begin_3(const TypeName##Function_TypeDef __code* TypeName##Function, unsigned char* CountSample);                                               \
reg8 TypeName##_ProcessIndex_3(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index, reg8 CountSample);                            \
reg8 TypeName##_Process_3(const TypeName##Function_TypeDef __code* TypeName##Function, unsigned char* CountSample);                                             \
reg8 TypeName##_Check_3(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index, reg8 Status, reg8 ClearStatus);
//==============================================================================================================================================================
//==================================================        INHERIT SOURCE MODE 0      =========================================================================
//==============================================================================================================================================================
/*
  +) Description:
  +) Declare:
      extern __no_init TypeName##_TypeDef VarName;
  +) Param:
      LogicBuild = BitCompare5[sum_sample] for for quick stack process compare by 5 (fix) sample times
      LogicBuild = SetBitCount[sum_sample] >= TYPE_NAME##_SAMPLE_DIVIDER_0 for normal mode
*/
#define DIGITAL_INPUT_INHERIT_SOURCE_0(TYPE_NAME, TypeName, VarName, LogicBuild, Scope, MaskFunction)                                                           \
static __no_init unsigned char count_sample;                                                                                                                    \
Scope void TypeName##_BeginStack##MaskFunction()                                                                                                                \
{                                                                                                                                                               \
  reg8 sum_sample = 0;                                                                                                                                          \
  {                                                                                                                                                             \
    reg8 fill_sample;                                                                                                                                           \
    for (fill_sample = 0; fill_sample < TYPE_NAME##_SAMPLE_TIMES_0; fill_sample++)                                                                              \
    {                                                                                                                                                           \
      sum_sample <<= 1;                                                                                                                                         \
      sum_sample |= TYPE_NAME##_READ_0();                                                                                                                       \
    }                                                                                                                                                           \
  }                                                                                                                                                             \
  VarName.SumSample = sum_sample;                                                                                                                               \
  VarName.Logic = LogicBuild;                                                                                                                                   \
  VarName.Status = 0;                                                                                                                                           \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessStack##MaskFunction()                                                                                                              \
{                                                                                                                                                               \
  reg8 sum_sample;                                                                                                                                              \
  sum_sample = VarName.SumSample << 1;                                                                                                                          \
  sum_sample |= TYPE_NAME##_READ_0();                                                                                                                           \
  VarName.SumSample = sum_sample;                                                                                                                               \
  {                                                                                                                                                             \
    reg8 now_logic = LogicBuild;                                                                                                                                \
    if (now_logic != VarName.Logic)                                                                                                                             \
    {                                                                                                                                                           \
      VarName.Logic = now_logic;                                                                                                                                \
      VarName.Status = now_logic + 1;                                                                                                                           \
      return 1;                                                                                                                                                 \
    }                                                                                                                                                           \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope void TypeName##_Begin##MaskFunction()                                                                                                                     \
{                                                                                                                                                               \
  count_sample = TYPE_NAME##_SAMPLE_TIMES_0;                                                                                                                    \
  VarName.Logic = TYPE_NAME##_READ_0();                                                                                                                         \
  VarName.Status = VarName.SumSample = 0;                                                                                                                       \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Process##MaskFunction()                                                                                                                   \
{                                                                                                                                                               \
  reg8 ret = 0, sum_sample = VarName.SumSample;                                                                                                                 \
  if (!count_sample)                                                                                                                                            \
  {                                                                                                                                                             \
    count_sample = TYPE_NAME##_SAMPLE_TIMES_0;                                                                                                                  \
    sum_sample /= TYPE_NAME##_SAMPLE_DIVIDER_0;                                                                                                                 \
    ret = 1;                                                                                                                                                    \
    if (sum_sample != VarName.Logic)                                                                                                                            \
    {                                                                                                                                                           \
      VarName.Logic = sum_sample;                                                                                                                               \
      VarName.Status = sum_sample + 1;                                                                                                                          \
      ret++;                                                                                                                                                    \
    }                                                                                                                                                           \
    sum_sample = 0;                                                                                                                                             \
  }                                                                                                                                                             \
  sum_sample += TYPE_NAME##_READ_0();                                                                                                                           \
  VarName.SumSample = sum_sample;                                                                                                                               \
  count_sample--;                                                                                                                                               \
  return ret;                                                                                                                                                   \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Check##MaskFunction(reg8 Status, reg8 ClearStatus)                                                                                        \
{                                                                                                                                                               \
  if (VarName.Status == Status)                                                                                                                                 \
  {                                                                                                                                                             \
    VarName.Status |= ClearStatus;                                                                                                                              \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}
//==============================================================================================================================================================
//==================================================        INHERIT SOURCE MODE 1      =========================================================================
//==============================================================================================================================================================
/*
  +) Description:
  +) Declare:
      extern __no_init TypeName##_TypeDef VarName[TYPE_NAME_##QUANTITY##MaskFunction];
  +) Param:
      LogicBuild = BitCompare5[sum_sample] for for quick stack process compare by 5 (fix) sample times
      LogicBuild = SetBitCount[sum_sample] >= TYPE_NAME##_SAMPLE_DIVIDER_0 for normal mode
*/
#define DIGITAL_INPUT_INHERIT_SOURCE_1(TYPE_NAME, TypeName, VarName, LogicBuild, Scope, MaskFunction)                                                           \
reg8 TypeName##_Read_1(reg8 TypeName##Index);                                                                                                                   \
static __no_init unsigned char count_sample;                                                                                                                    \
                                                                                                                                                                \
Scope void TypeName##_BeginStack##MaskFunction()                                                                                                                \
{                                                                                                                                                               \
  reg8 TypeName##Index;                                                                                                                                         \
  for (TypeName##Index = 0; TypeName##Index < TYPE_NAME##_QUANTITY_1; TypeName##Index++)                                                                        \
  {                                                                                                                                                             \
    TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                   \
    reg8 sum_sample = 0;                                                                                                                                        \
    {                                                                                                                                                           \
      reg8 fill_sample;                                                                                                                                         \
      for (fill_sample = 0; fill_sample < TYPE_NAME##_SAMPLE_TIMES_1; fill_sample++)                                                                            \
      {                                                                                                                                                         \
        sum_sample <<= 1;                                                                                                                                       \
        sum_sample |= TypeName##_Read_1(TypeName##Index);                                                                                                       \
      }                                                                                                                                                         \
    }                                                                                                                                                           \
    TypeName->SumSample = sum_sample;                                                                                                                           \
    TypeName->Logic = LogicBuild;                                                                                                                               \
    TypeName->Status = 0;                                                                                                                                       \
  }                                                                                                                                                             \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessIndexStack##MaskFunction(reg8 TypeName##Index)                                                                                     \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                     \
  reg8 sum_sample = TypeName->SumSample;                                                                                                                        \
  sum_sample <<= 1;                                                                                                                                             \
  sum_sample |= TypeName##_Read_1(TypeName##Index);                                                                                                             \
  TypeName->SumSample = sum_sample;                                                                                                                             \
  {                                                                                                                                                             \
    reg8 now_logic = LogicBuild;                                                                                                                                \
    if (now_logic != TypeName->Logic)                                                                                                                           \
    {                                                                                                                                                           \
      TypeName->Logic = now_logic;                                                                                                                              \
      TypeName->Status = now_logic + 1;                                                                                                                         \
      return 1;                                                                                                                                                 \
    }                                                                                                                                                           \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope void TypeName##_ProcessStack##MaskFunction()                                                                                                              \
{                                                                                                                                                               \
  reg8 TypeName##Index;                                                                                                                                         \
  for (TypeName##Index = 0; TypeName##Index < TYPE_NAME##_QUANTITY_1; TypeName##Index++)                                                                        \
    TypeName##_ProcessIndexStack##MaskFunction(TypeName##Index);                                                                                                \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope void TypeName##_Begin##MaskFunction()                                                                                                                     \
{                                                                                                                                                               \
  reg8 TypeName##Index;                                                                                                                                         \
  count_sample = TYPE_NAME##_SAMPLE_TIMES_1;                                                                                                                    \
  for (TypeName##Index = 0; TypeName##Index < TYPE_NAME##_QUANTITY_1; TypeName##Index++)                                                                        \
  {                                                                                                                                                             \
    TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                   \
    TypeName->Logic = TypeName##_Read_1(TypeName##Index);                                                                                                       \
    TypeName->Status = TypeName->SumSample = 0;                                                                                                                 \
  }                                                                                                                                                             \
}                                                                                                                                                               \
                                                                                                                                                                \
static reg8 Process(reg8 TypeName##Index)                                                                                                                       \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                     \
  reg8 now_logic = TypeName->SumSample / TYPE_NAME##_SAMPLE_DIVIDER_1;                                                                                          \
  TypeName->SumSample = 0;                                                                                                                                      \
  if (now_logic != TypeName->Logic)                                                                                                                             \
  {                                                                                                                                                             \
    TypeName->Logic = now_logic;                                                                                                                                \
    TypeName->Status = now_logic + 1;                                                                                                                           \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Process##MaskFunction()                                                                                                                   \
{                                                                                                                                                               \
  reg8 ret = 0;                                                                                                                                                 \
  if (!count_sample)                                                                                                                                            \
  {                                                                                                                                                             \
    reg8 TypeName##Index;                                                                                                                                       \
    for (TypeName##Index = 0; TypeName##Index < TYPE_NAME##_QUANTITY_1; TypeName##Index++)                                                                      \
      Process(TypeName##Index);                                                                                                                                 \
    count_sample = TYPE_NAME##_SAMPLE_TIMES_1;                                                                                                                  \
    ret = 1;                                                                                                                                                    \
  }                                                                                                                                                             \
  {                                                                                                                                                             \
    reg8 TypeName##Index;                                                                                                                                       \
    for (TypeName##Index = 0; TypeName##Index < TYPE_NAME##_QUANTITY_1; TypeName##Index++)                                                                      \
      VarName[TypeName##Index].SumSample += TypeName##_Read_1(TypeName##Index);                                                                                 \
  }                                                                                                                                                             \
  count_sample--;                                                                                                                                               \
  return ret;                                                                                                                                                   \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessIndex##MaskFunction(reg8 TypeName##Index, reg8 CountSample)                                                                        \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                     \
  if (!CountSample)                                                                                                                                             \
  {                                                                                                                                                             \
    Process(TypeName##Index);                                                                                                                                   \
    CountSample = TYPE_NAME##_SAMPLE_TIMES_1;                                                                                                                   \
  }                                                                                                                                                             \
  TypeName->SumSample += TypeName##_Read_1(TypeName##Index);                                                                                                    \
  return CountSample - 1;                                                                                                                                       \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Check##MaskFunction(reg8 TypeName##Index, reg8 Status, reg8 ClearStatus)                                                                  \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &VarName[TypeName##Index];                                                                                                     \
  if (TypeName->Status == Status)                                                                                                                               \
  {                                                                                                                                                             \
    TypeName->Status |= ClearStatus;                                                                                                                            \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
//==============================================================================================================================================================
//==================================================        INHERIT SOURCE MODE 2      =========================================================================
//==============================================================================================================================================================
#define DIGITAL_INPUT_INHERIT_SOURCE_2(TYPE_NAME, TypeName, LogicBuild, Scope, MaskFunction)                                                                    \
Scope void TypeName##_BeginStack##MaskFunction(const TypeName##Function_TypeDef __gptr* TypeName##Function)                                                     \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName;                                                                                                                                 \
  reg8 sum_sample = 0;                                                                                                                                          \
  {                                                                                                                                                             \
    reg8 index = TypeName##Function->TypeName##Index;                                                                                                           \
    TypeName = &TypeName##Function->TypeName[index];                                                                                                            \
    {                                                                                                                                                           \
      reg8 (*digital_input_read)(reg8 TypeName##Index) = TypeName##Function->TypeName##Read;                                                                    \
      reg8 fill_sample;                                                                                                                                         \
      for (fill_sample = 0; fill_sample < TypeName##Function->SampleTimes; fill_sample++)                                                                       \
      {                                                                                                                                                         \
        sum_sample <<= 1;                                                                                                                                       \
        sum_sample |= digital_input_read(index);                                                                                                                \
      }                                                                                                                                                         \
    }                                                                                                                                                           \
  }                                                                                                                                                             \
  TypeName->SumSample = sum_sample;                                                                                                                             \
  TypeName->Logic = LogicBuild;                                                                                                                                 \
  TypeName->Status = 0;                                                                                                                                         \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessStack##MaskFunction(const TypeName##Function_TypeDef __gptr* TypeName##Function)                                                   \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName;                                                                                                                                 \
  reg8 now_logic;                                                                                                                                               \
  {                                                                                                                                                             \
    reg8 sum_sample;                                                                                                                                            \
    {                                                                                                                                                           \
      reg8 index = TypeName##Function->TypeName##Index;                                                                                                         \
      TypeName = &TypeName##Function->TypeName[index];                                                                                                          \
      sum_sample = TypeName->SumSample << 1;                                                                                                                    \
      sum_sample |= TypeName##Function->TypeName##Read(index);                                                                                                  \
    }                                                                                                                                                           \
    now_logic = LogicBuild;                                                                                                                                     \
  }                                                                                                                                                             \
  if (now_logic != TypeName->Logic)                                                                                                                             \
  {                                                                                                                                                             \
    TypeName->Logic = now_logic;                                                                                                                                \
    TypeName->Status = now_logic + 1;                                                                                                                           \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Begin##MaskFunction(const TypeName##Function_TypeDef __gptr* TypeName##Function)                                                          \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = TypeName##Function->TypeName;                                                                                                  \
  TypeName->Logic = TypeName##Function->TypeName##Read(TypeName##Function->TypeName##Index);                                                                    \
  TypeName->Status = TypeName->SumSample = 0;                                                                                                                   \
  return TypeName##Function->SampleTimes;                                                                                                                       \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Process##MaskFunction(const TypeName##Function_TypeDef __gptr* TypeName##Function, unsigned char* CountSample)                            \
{                                                                                                                                                               \
  reg8 index = TypeName##Function->TypeName##Index;                                                                                                             \
  TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[index];                                                                                          \
  reg8 sum_sample = TypeName->SumSample;                                                                                                                        \
  reg8 count_sample = *CountSample;                                                                                                                             \
  reg8 ret = 0;                                                                                                                                                 \
  if (!count_sample)                                                                                                                                            \
  {                                                                                                                                                             \
    reg8 now_logic = sum_sample / TypeName##Function->SampleDivider;                                                                                            \
    if (now_logic !=  TypeName->Logic)                                                                                                                          \
    {                                                                                                                                                           \
      TypeName->Logic = now_logic;                                                                                                                              \
      TypeName->Status = now_logic + 1;                                                                                                                         \
      ret = 1;                                                                                                                                                  \
    }                                                                                                                                                           \
    sum_sample = 0;                                                                                                                                             \
    count_sample = TypeName##Function->SampleTimes;                                                                                                             \
  }                                                                                                                                                             \
  sum_sample += TypeName##Function->TypeName##Read(index);                                                                                                      \
  TypeName->SumSample = sum_sample;                                                                                                                             \
  *CountSample = count_sample - 1;                                                                                                                              \
  return ret;                                                                                                                                                   \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Check##MaskFunction(TypeName##_TypeDef* TypeName, reg8 Status, reg8 ClearStatus)                                                          \
{                                                                                                                                                               \
  if (TypeName->Status == Status)                                                                                                                               \
  {                                                                                                                                                             \
    TypeName->Status |= ClearStatus;                                                                                                                            \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}  
//==============================================================================================================================================================
//==================================================        INHERIT SOURCE MODE 3      =========================================================================
//==============================================================================================================================================================
#define DIGITAL_INPUT_INHERIT_SOURCE_3(TYPE_NAME, TypeName, LogicBuild, Scope, MaskFunction)                                                                    \
Scope void TypeName##_BeginStack##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function)                                                     \
{                                                                                                                                                               \
  reg8 (*digital_input_read)(reg8 TypeName##Index) = TypeName##Function->TypeName##Read;                                                                        \
  reg8 TypeName##Index;                                                                                                                                         \
  for (TypeName##Index = 0; TypeName##Index < TypeName##Function->NumberOf##TypeName; TypeName##Index++)                                                        \
  {                                                                                                                                                             \
    TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                              \
    reg8 sum_sample = 0;                                                                                                                                        \
    {                                                                                                                                                           \
      reg8 fill_sample;                                                                                                                                         \
      for (fill_sample = 0; fill_sample < TypeName##Function->SampleTimes; fill_sample++)                                                                       \
      {                                                                                                                                                         \
        sum_sample <<= 1;                                                                                                                                       \
        sum_sample |= digital_input_read(TypeName##Index);                                                                                                      \
      }                                                                                                                                                         \
    }                                                                                                                                                           \
    TypeName->SumSample = sum_sample;                                                                                                                           \
    TypeName->Logic = LogicBuild;                                                                                                                               \
    TypeName->Status = 0;                                                                                                                                       \
  }                                                                                                                                                             \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessIndexStack##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index)                        \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                                \
  reg8 now_logic;                                                                                                                                               \
  {                                                                                                                                                             \
    reg8 sum_sample = TypeName->SumSample << 1;                                                                                                                 \
    sum_sample |= TypeName##Function->TypeName##Read(TypeName##Index);                                                                                          \
    TypeName->SumSample = sum_sample;                                                                                                                           \
    now_logic = LogicBuild;                                                                                                                                     \
  }                                                                                                                                                             \
  if (now_logic != TypeName->Logic)                                                                                                                             \
  {                                                                                                                                                             \
    TypeName->Logic = now_logic;                                                                                                                                \
    TypeName->Status = now_logic + 1;                                                                                                                           \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope void TypeName##_ProcessStack##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function)                                                   \
{                                                                                                                                                               \
  reg8 TypeName##Index;                                                                                                                                         \
  for (TypeName##Index = 0; TypeName##Index < TypeName##Function->NumberOf##TypeName; TypeName##Index++)                                                        \
    TypeName##_ProcessIndexStack##MaskFunction(TypeName##Function, TypeName##Index);                                                                            \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope void TypeName##_Begin##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function, unsigned char* CountSample)                              \
{                                                                                                                                                               \
  reg8 (*button_read)(reg8 TypeName##Index) = TypeName##Function->TypeName##Read;                                                                               \
  reg8 TypeName##Index;                                                                                                                                         \
  for (TypeName##Index = 0; TypeName##Index < TypeName##Function->NumberOf##TypeName; TypeName##Index++)                                                        \
  {                                                                                                                                                             \
    TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                              \
    TypeName->Logic = button_read(TypeName##Index);                                                                                                             \
    TypeName->Status = TypeName->SumSample = 0;                                                                                                                 \
  }                                                                                                                                                             \
  *CountSample = TypeName##Function->SampleTimes;                                                                                                               \
}                                                                                                                                                               \
                                                                                                                                                                \
static reg8 Process(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index)                                                          \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                                \
  reg8 now_logic = TypeName->SumSample / TypeName##Function->SampleDivider;                                                                                     \
  TypeName->SumSample = 0;                                                                                                                                      \
  if (now_logic != TypeName->Logic)                                                                                                                             \
  {                                                                                                                                                             \
    TypeName->Logic = now_logic;                                                                                                                                \
    TypeName->Status = now_logic + 1;                                                                                                                           \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Process##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function, unsigned char* CountSample)                            \
{                                                                                                                                                               \
  reg8 count_sample = *CountSample;                                                                                                                             \
  reg8 ret = 0;                                                                                                                                                 \
  if (!count_sample)                                                                                                                                            \
  {                                                                                                                                                             \
    reg8 TypeName##Index;                                                                                                                                       \
    for (TypeName##Index = 0; TypeName##Index < TypeName##Function->NumberOf##TypeName; TypeName##Index++)                                                      \
      Process(TypeName##Function, TypeName##Index);                                                                                                             \
    count_sample = TypeName##Function->SampleTimes;                                                                                                             \
    ret = 1;                                                                                                                                                    \
  }                                                                                                                                                             \
  {                                                                                                                                                             \
    reg8(*button_read)(reg8 TypeName##Index) = TypeName##Function->TypeName##Read;                                                                              \
    reg8 TypeName##Index;                                                                                                                                       \
    for (TypeName##Index = 0; TypeName##Index < TypeName##Function->NumberOf##TypeName; TypeName##Index++)                                                      \
      TypeName##Function->TypeName[TypeName##Index].SumSample += button_read(TypeName##Index);                                                                  \
  }                                                                                                                                                             \
  *CountSample = count_sample - 1;                                                                                                                              \
  return ret;                                                                                                                                                   \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_ProcessIndex##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index, reg8 CountSample)           \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                                \
  if (!CountSample)                                                                                                                                             \
  {                                                                                                                                                             \
    Process(TypeName##Function, TypeName##Index);                                                                                                               \
    CountSample = TypeName##Function->SampleTimes;                                                                                                              \
  }                                                                                                                                                             \
  TypeName->SumSample += TypeName##Function->TypeName##Read(TypeName##Index);                                                                                   \
  return CountSample - 1;                                                                                                                                       \
}                                                                                                                                                               \
                                                                                                                                                                \
Scope reg8 TypeName##_Check##MaskFunction(const TypeName##Function_TypeDef __code* TypeName##Function, reg8 TypeName##Index, reg8 Status, reg8 ClearStatus)     \
{                                                                                                                                                               \
  TypeName##_TypeDef* TypeName = &TypeName##Function->TypeName[TypeName##Index];                                                                                \
  if (TypeName->Status == Status)                                                                                                                               \
  {                                                                                                                                                             \
    TypeName->Status |= ClearStatus;                                                                                                                            \
    return 1;                                                                                                                                                   \
  }                                                                                                                                                             \
  return 0;                                                                                                                                                     \
}
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#endif