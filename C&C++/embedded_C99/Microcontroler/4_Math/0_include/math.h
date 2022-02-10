/*
TRIGONOMETRIC:
  +) Config:
      #define SIN_BOUND                 1000
        -)SinTable[Degree] = (sin(Degree) * SIN_BOUND) / 65535
      #define COS_BOUND                 1000
        -)CosTable[Degree] = (cos(Degree) * COS_BOUND) / 65535
  +) Declare:
  +) Using:
      #define Sin(Value, Degree)        (((Value) * SinTable[Degree]) / SIN_BOUND)
      #define Cos(Value, Degree)        (((Value) * CosTable[Degree]) / COS_BOUND)        
      #define Tan(Value, Degree)        (((Value) * SinTable[Degree] + CosTable[Degree] - 1) / CosTable[Degree])
      #define Cot(Value, Degree)        (((Value) * CosTable[Degree] + SinTable[Degree] - 1) / SinTable[Degree])
        -)Degree is from 0 to 90

*/
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
#ifndef _MATH_H_
#define _MATH_H_

#include <config.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
//========================================================       TRIGONOMETRIC      ============================================================================
#define Sin(Value, Degree)      (((Value) * SinTable[Degree]) / SIN_BOUND)
extern const unsigned short __code SinTable[91];
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Cos(Value, Degree)      (((Value) * CosTable[Degree]) / COS_BOUND)
extern const unsigned short __code CosTable[91];
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Tan(Value, Degree)      (((Value) * SinTable[Degree] + CosTable[Degree] - 1) / CosTable[Degree])
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Cot(Value, Degree)      (((Value) * CosTable[Degree] + SinTable[Degree] - 1) / SinTable[Degree])
//========================================================         FRACTION         ============================================================================
typedef struct
{
  unsigned char Numerator;
  unsigned char Denominator;
} Fraction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned short Real;
  unsigned short Imaginary;
} ComplexNumber_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned char Rows;
  unsigned char Columns;
  unsigned short* Data;
} Matrix_TypeDef;

#endif