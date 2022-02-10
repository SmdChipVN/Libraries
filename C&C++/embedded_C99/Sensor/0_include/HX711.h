/*
  ******************************************
  **   MODIFY IN config.h / config.c     **
  ******************************************

  >>config:
    - DOUT as INPUT_PULLUP, CK as OUTPUT
    - CK = 0

  >>define:
#define SET_HX711_CK()          CK=1
#define CLR_HX711_CK()          CK=0
#define RD_HX711_DOUT()         (DOUT)

      ____         _______ _______
DOUT:     |_______X_______X_______X                    Min   Nor  Max
                  T2                               T1  0.1   --   -- 
          |<-T1->| |       | T3 | T4 |             T2  --    --   0.1     (uS) 
                  ____      ____      ___          T3  0.2    1   50 
CK:   ___________|    |____|    |____|             T4  0.2    1   --

#define DELAY_HX711_T1()        {}
#define DELAY_HX711_T2()        delay_us(1)
#define DELAY_HX711_T3()        delay_us(1)
#define DELAY_HX711_T4()        delay_us(1)
*/

#ifndef _HX711_H_
#define _HX711_H_

#include <common.h>

void HX711_Begin();
bool HX711_Read(signed long* OutValue);

#endif