#ifndef _GPIO_H_
#define _GPIO_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  xBUNION(ODR, unsigned char,                   //              0x00            Port output data register
    b, 0, 7, 1);
  xBUNION(IDR, unsigned char const,             //              0x--            Port intput data register
    b, 0, 7, 1);
  xBUNION(DDR, unsigned char,                   //              0x00            Port direction register: 0: in, 1: out
    b, 0, 7, 1);
  xBUNION(CR1, unsigned char,                   //              0x00            Port control register 1
    b, 0, 7, 1);
  xBUNION(CR2, unsigned char,                   //              0x00            Port control register 2
    b, 0, 7, 1);
} GPIO_TypeDef;
//==============================================================================================================================================================
typedef enum
{
  GPIO_MODE_INPUT_FLOAT                 = 0,
  GPIO_MODE_INPUT_PULLUP                = 2,
  GPIO_MODE_INPUT_FLOAT_IT              = 1,
  GPIO_MODE_INPUT_PULLUP_IT             = 3,
  GPIO_MODE_OUTPUT_OPEN                 = 4,
  GPIO_MODE_OUTPUT_PUSHPULL_2MHZ        = 6,
  GPIO_MODE_OUTPUT_OPEN_FAST            = 5,
  GPIO_MODE_OUTPUT_PUSHPULL_10MHZ       = 7,
} GPIO_MODE;
void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned char PIN, GPIO_MODE Mode);

#endif