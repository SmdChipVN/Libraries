#ifndef _GPIO_H_
#define _GPIO_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
#define P0_DAT_ADDRESS                  0x80
SFRxB(P0_DAT, 0x80, , 0, 7, 1);                 //              0x00            Port 0 data
SFRxB(P0_IFG, 0x89, , 0, 7, 1);                 //              0x00            Port 0 interrupt status flag
SFRxB(P0_INP, 0x8F, , 0, 7, 1);                 //              0x00            Port 0 input mode               0: pull (see P2_INP)    1: float
SFRxB(P0_IEN, 0xAB, , 0, 7, 1);                 //              0x00            Port 0 interrupt mask
SFRxB(P0_SEL, 0xF3, , 0, 7, 1);                 //              0x00            Port 0 function select          0: GPIO                 1: Peripheral
SFRxB(P0_DIR, 0xFD, , 0, 7, 1);                 //              0x00            Port 0 direction                0: input                1: output
//==============================================================================================================================================================
#define P1_DAT_ADDRESS                  0x90
SFRxB(P1_DAT, 0x90, , 0, 7, 1);
SFRxB(P1_IFG, 0x8A, , 0, 7, 1);
SFRxB(P1_INP, 0xF6, , 0, 7, 1);
SFRxB(P1_IEN, 0x8D, , 0, 7, 1);
SFRxB(P1_SEL, 0xF4, , 0, 7, 1);
SFRxB(P1_DIR, 0xFE, , 0, 7, 1);
//==============================================================================================================================================================
#define P2_DAT_ADDRESS                  0xA0
SFRxB(P2_DAT, 0xA0, , 0, 7, 1);
SFRxB(P2_IFG, 0x8B, , 0, 7, 1);
SFRB(P2_INP, 0xF7, ,                            //              0x00
  MDP2                                  , 4,    //0:4           0               P2.4 to P2.0 I/O input mode     0: P 2.0->2.4 pull      1: float
  PDUP0                                 , 1,    //5             0               all P0 input pull               0: pull-up              1: pull-down
  PDUP1                                 , 1,    //6             0               all P1 input pull               0: pull-up              1: pull-down
  PDUP2                                 , 1);   //7             0               all P2 input pull               0: pull-up              1: pull-down
SFRxB(P2_IEN, 0xAC, , 0, 7, 1);
SFRxB(P2_SEL, 0xF5, , 0, 7, 1);
SFRxB(P2_DIR, 0xFF, , 0, 7, 1);
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
typedef enum
{
  GPIO_MODE_PERIPHERAL_PIN              = 0xFF,
                                                //      OUTPUT  HIGH    PULL    IT
  GPIO_MODE_INPUT_FLOAT                 = 0x00, //         0      0       0     0
  GPIO_MODE_INPUT_FLOAT_IT              = 0x01, //         0      0       0     1
  GPIO_MODE_INPUT_PULLDOWN              = 0x02, //         0      0       1     0
  GPIO_MODE_INPUT_PULLDOWN_IT           = 0x03, //         0      0       1     1
  GPIO_MODE_INPUT_PULLUP                = 0x06, //         0      1       1     0
  GPIO_MODE_INPUT_PULLUP_IT             = 0x07, //         0      1       1     1

  GPIO_MODE_OUTPUT_LOW                  = 0x08, //         1      0       0     0
  GPIO_MODE_OUTPUT_LOW_IT               = 0x09, //         1      0       0     1
  GPIO_MODE_OUTPUT_HIGH                 = 0x0C, //         1      1       0     0
  GPIO_MODE_OUTPUT_HIGH_IT              = 0x0D, //         1      1       0     1
} GPIO_MODE;
#define GPIO_Mode(Port, Pin, Mode)      GPIO_Mode##Port(Pin, Mode)
void GPIO_Mode0(unsigned char Pin, GPIO_MODE Mode);
void GPIO_Mode1(unsigned char Pin, GPIO_MODE Mode);
void GPIO_Mode2(unsigned char Pin, GPIO_MODE Mode);

#endif