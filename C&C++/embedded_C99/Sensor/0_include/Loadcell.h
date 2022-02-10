/*
  ******************************************
  **   MODIFY IN config.h / config.c     **
  ******************************************

  >>define:
#define LOADCELL_DELAY_1MS()                    delay_ms(1)
#define LOADCELL_CALIB_ABSOLUTE
#define LOADCELL_BUFF_SIZE                      4
#define LOADCELL_CALIB_MASS                     300             //(gram)
*/

#ifndef _LOADCELL_H_
#define _LOADCELL_H_

#include <common.h>
#include <config.h>

typedef struct
{
  bool (*GetValue)(signed long*);
  signed long (*ReadCalibMass)();
  void (*SaveCalibMass)(signed long Value);
  unsigned short TimeOut;
} LoadcellInfo_TypeDef;

typedef struct
{
  signed long Buffer[LOADCELL_BUFF_SIZE];
  unsigned char Index;
  signed long Accumulator;
  signed long Zero;
} Loadcell_TypeDef;

bool Loadcell_Begin(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell);
signed long Loadcell_Mass(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell);
bool Loadcell_CalibZero(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell);
bool Loadcell_CalibMass(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell);
bool Loadcell_Read(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell);

#endif