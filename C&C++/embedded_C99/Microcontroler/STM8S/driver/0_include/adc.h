#ifndef _ADC_H_
#define _ADC_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  RUNION_16x8(DB0R, const, HIGH, LOW);          //              0x00            ADC data buffer register
  unsigned char _reserved[0x0D - 0x02 + 1];
  RUNION_16x8(DB7R, const, HIGH, LOW);          //              0x00
  RUNION_16x8(DB8R, const, HIGH, LOW);          //              0x00
  RUNION_16x8(DB9R, const, HIGH, LOW);          //              0x00
  unsigned char _reserved1[0x1F - 0x14 + 1];
  BUNION(CSR, unsigned char,                    //              0x00            ADC control/status register
    CH                                  , 4,    //0:3           0               Channel selection bits
    AWDIE                               , 1,    //4             0               Analog watchdog interrupt enable
    EOCIE                               , 1,    //5             0               Interrupt enable for EOC
    AWD                                 , 1,    //6             0               Analog Watchdog flag
    EOC                                 , 1);   //7             0               End of conversion
  BUNION(CR1, unsigned char,                    //              0x00            ADC configuration register 1
    ADON                                , 1,    //0             0               A/D converter ON / OFF
    CONT                                , 1,    //1             0               Continuous conversion
    _reserved                           , 2,
    SPSEL                               , 3,    //4:6           0               Prescaler selection
    _reserved1                          , 1);
  BUNION(CR2, unsigned char,                    //              0x00            ADC configuration register 2
    _reserved                           , 1,
    SCAN                                , 1,    //1             0               Scan mode enable
    _reserved1                          , 1,
    ALIGN                               , 1,    //3             0               Data alignment
    EXTSEL                              , 2,    //4-5           0               External event selection
    EXTTRIG                             , 1,    //6             0               External trigger enable
    _reserved2                          , 1);
  BUNION(CR3, unsigned char,                    //              0x00            ADC configuration register 3
    _reserved       , 5,
    OVR             , 1,                        //6             0               Overrun flag
    DBUF            , 1);                       //7             0               Data buffer enable
  RUNION_16x8(DR, const, HIGH, LOW);            //              0x----          ADC data register
  RUNION_16x8(TDR, , HIGH, LOW);                //              0x0000          ADC Schmitt trigger disable register
  RUNION_16x8(HTH, , HIGH, LOW);                //              0x03FF          ADC high threshold register
  RUNION_16x8(LTH, , HIGH, LOW);                //              0x0000          ADC low threshold register
  RUNION_16x8(AWSR, , HIGH, LOW);               //              0x0000          ADC watchdog status register
  RUNION_16x8(AWCR, , HIGH, LOW);               //              0x0000          ADC watchdog control register
} ADC1_TypeDef;
//==============================================================================================================================================================
void ADC_Init(volatile ADC1_TypeDef* ADC1);
void ADC_Start(volatile ADC1_TypeDef* ADC1, unsigned char Channel);
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
typedef struct
{
  BUNION(CSR, unsigned char,                    //              0x00            ADC control/status register
    CH                                  , 4,    //0:3           0               Channel selection bits
    AWDIE                               , 1,    //4             0               Analog watchdog interrupt enable
    EOCIE                               , 1,    //5             0               Interrupt enable for EOC
    AWD                                 , 1,    //6             0               Analog Watchdog flag
    EOC                                 , 1);   //7             0               End of conversion
  BUNION(CR1, unsigned char,                    //              0x00            ADC configuration register 1
    ADON                                , 1,    //0             0               A/D converter ON / OFF
    CONT                                , 1,    //1             0               Continuous conversion
    _reserved                           , 2,
    SPSEL                               , 3,    //4:6           0               Prescaler selection
    _reserved1                          , 1);
  BUNION(CR2, unsigned char,                    //              0x00            ADC configuration register 2
    _reserved                           , 1,
    SCAN                                , 1,    //1             0               Scan mode enable
    _reserved1                          , 1,
    ALIGN                               , 1,    //3             0               Data alignment
    EXTSEL                              , 2,    //4-5           0               External event selection
    EXTTRIG                             , 1,    //6             0               External trigger enable
    _reserved2                          , 1);
  BUNION(CR3, unsigned char,                    //              0x00            ADC configuration register 3
    _reserved                           , 5,
    OVR                                 , 1,    //6             0               Overrun flag
    DBUF                                , 1);   //7             0               Data buffer enable
  RUNION_16x8(DR, const, HIGH, LOW);            //              0x----          ADC data register
  RUNION_16x8(TDR, , HIGH, LOW);                //              0x0000          ADC Schmitt trigger disable register
} ADC2_TypeDef;

#endif