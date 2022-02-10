#ifndef _ADC_H_
#define _ADC_H_

#include <define.h>

//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned char,     //0             0x00            ADC configuration register 1
    ADON                , 1,    //0             0               A/D converter ON / OFF
    START               , 1,    //1             0               Conversion start
    CONT                , 1,    //2             0               Continuous conversion
    EOCIE               , 1,    //3             0               Interrupt enable for EOC
    AWDIE               , 1,    //4             0               Analog watchdog interrupt enable
    RESOLUTION          , 2,    //5-6           0               Configurable resolution
    OVERIE              , 1);   //7             0               Overrun interrupt enable  
  BUNION(CR2, unsigned char,     //1             0x00            ADC configuration register 2
    SMPT1               , 3,    //0:2           0               Sampling time selection
    EXTSE               , 2,    //3-4           0               External event selection
    TRIG_EDGE           , 2,    //5-6           0               Active edge for external triggers
    PRESC               , 1);   //7             0               Clock prescaler
  BUNION(CR3, unsigned char,     //2             0x1F            ADC configuration register 3
    CHSEL               , 5,    //0:4           31              Channel selection
    SMPT2               , 3);   //5:7           0               Sampling time selection
  BUNION(SR, unsigned char,      //3             0x00            ADC status register
    EOC                 , 1,    //0             0               End of conversion
    AWD                 , 1,    //1             0               Analog watchdog flag
    OVER                , 1,    //2             0               Overrun flag
    _reserved           , 5);
  BRUNION_16x8(DR, const, HIGH, LOW,    //4-5           0x0000          ADC data register
      b11_8             , 4,
      _reserved         , 4,
      b7_0              , 8);
  BRUNION_16x8(HTR, , HIGH, LOW,    //6-7           0x0FFF          ADC high threshold register
      b11_8             , 4,
      _reserved         , 4,
      b7_0              , 8);
  BRUNION_16x8(LTR, , HIGH, LOW,    //8-9           0x0000          ADC low threshold register
      b11_8             , 4,
      _reserved         , 4,
      b7_0              , 8);
  BRUNION_32x8(SQR, , r1, r2, r3, r4,   //10:13         0x00(4)         ADC channel select scan
    xBITS_B(cn, 24, 27, 1),
        VREFINT         , 1,    //4             0               Selection of channel VREFINT for scan
        TS              , 1,    //5             0               Selection of channel TS for scan
        _reserved       , 1,
        DMAOFF          , 1,   //7             0               DMA disable for a single conversion
    xBITS_B(cn, 16, 23, 1),
    xBITS_B(cn, 8, 15, 1),
    xBITS_B(cn, 0, 7, 1));
  BRUNION_32x8(TRIGR, , r1, r2, r3, r4,   //14:17         0x00(4)         ADC trigger disable
    xBITS_B(trg, 24, 27, 1),
        VREFINT         , 1,    //4             0               Selection of channel VREFINT for scan
        TS              , 1,    //5             0               Selection of channel TS for scan
        _reserved       , 2,
    xBITS_B(trg, 16, 23, 1),
    xBITS_B(trg, 8, 15, 1),
    xBITS_B(trg, 0, 7, 1));
} ADC_TypeDef;

#endif