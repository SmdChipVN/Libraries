#ifndef _GPIO_H_
#define _GPIO_H_

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
#include <define.h>
#include <common.h>
//                              //Address       Default         Descriptor
typedef struct
{
  xBUNION(ODR, unsigned char , b, 0, 7, 1); //Port output data register
  xBUNION(IDR, unsigned char , b, 0, 7, 1); //Port input data register
  xBUNION(DDR, unsigned char , b, 0, 7, 1); //Port data direction register
  xBUNION(CR1, unsigned char , b, 0, 7, 1); //Port control register 1
  xBUNION(CR2, unsigned char , b, 0, 7, 1); //Port control register 2
} GPIO_TypeDef;
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
typedef enum
{
  GPIO_MODE_INPUT_FLOAT                 = 0,
  GPIO_MODE_INPUT_PULLUP                = BIT1,
  GPIO_MODE_INPUT_FLOAT_IT              = BIT0,
  GPIO_MODE_INPUT_PULLUP_IT             = (BIT1 | BIT0),
  GPIO_MODE_OUTPUT_OPEN                 = BIT2,
  GPIO_MODE_OUTPUT_PUSHPULL             = (BIT2 | BIT1),
  GPIO_MODE_OUTPUT_OPEN_FAST            = (BIT2 | BIT0),
  GPIO_MODE_OUTPUT_PUSHPULL_FAST        = (BIT2 | BIT1 | BIT0),
} GPIO_MODE;
void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned char PIN, GPIO_MODE mode);

#endif