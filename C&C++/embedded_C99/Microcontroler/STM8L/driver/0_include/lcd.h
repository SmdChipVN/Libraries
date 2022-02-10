#ifndef _LCD_H_
#define _LCD_H_

typedef struct
{
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char B2                  : 1;    //Bias selector
      unsigned char DUTY                : 2;    //Duty ratio selection
      unsigned char BLINKF              : 3;    //Blink frequency 
      unsigned char BLINK               : 2;    //Blink enable
    } BITS;
  } CR1;                                        //Control register 1
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char VSEL                : 1;    //The VSEL bit determines the LCD voltage source
      unsigned char CC                  : 3;    //Contrast control
      unsigned char HD                  : 1;    //High drive enable
      unsigned char PON                 : 3;    //Pulse ON duration
    } BITS;
  } CR2;                                        //Control register 2
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char DEAD                : 3;    //Dead time enable
      unsigned char SOFC                : 1;    //SOF flag clear
      unsigned char SOF                 : 1;    //Start of frame flag
      unsigned char SOFIE               : 1;    //Interrupt enable
      unsigned char LCDEN               : 1;    //LCD enable
      unsigned char _Reserved           : 1;
    } BITS;
  } CR3;                                        //Control register 3
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char DIV                 : 4;    //Divider from 16 to 31
      unsigned char PS                  : 4;    //CLK 16-bit prescaler
    } BITS;
  } FRQ;                                        //Frequency selection register
  union
  {
    struct
    {
      unsigned char _0;
      unsigned char _1;
      unsigned char _2;
      unsigned char _3;
      unsigned char _4;
      unsigned char _5;
    } REGS;
    struct
    {
      unsigned char PM_SEG_7_0;
      unsigned char PM_SEG_15_8;
      unsigned char PM_SEG_23_16;
#if (LOW_DENSITY)
      unsigned char _Reserved;
#else
      unsigned char PM_SEG_31_24;
#endif      
      unsigned char PM_SEG_39_32;
#if (MEDIUM_PLUS_DENSITY || HIGH_DENSITY)
      unsigned char PM_SEG_43_40        : 4;
      unsigned char _Reserved1          : 4;
#else
      unsigned char _Reserved1;
#endif
    } BITS;
  } PM;                                         //Port mask registers
  unsigned char _Reserved[2];
  union
  {
    struct
    {
      unsigned char _0; unsigned char _1; unsigned char _2; 
      unsigned char _3; unsigned char _4; unsigned char _5;
      unsigned char _6; unsigned char _7; unsigned char _8;
      unsigned char _9; unsigned char _10; unsigned char _11;
      unsigned char _12; unsigned char _13; unsigned char _14;
      unsigned char _15; unsigned char _16; unsigned char _17;
      unsigned char _18; unsigned char _19; unsigned char _20;
      unsigned char _21;
    } REGS;
    struct
    {
      unsigned char S0_7_0; unsigned char S0_15_8; unsigned char S0_23_16; unsigned char S0_27_24 : 4;
      unsigned char S1_3_0 : 4; unsigned char S1_11_4; unsigned char S1_19_12; unsigned char S1_27_20;
      unsigned char S2_7_0; unsigned char S2_15_8; unsigned char S2_23_16; unsigned char S2_27_24 : 4;
      unsigned char S3_3_0 : 4; unsigned char S3_11_4; unsigned char S3_19_12; unsigned char S0_27_20;
      unsigned char S0_35_28; unsigned char S0_43_36;
      unsigned char S1_35_28; unsigned char S1_43_36;
      unsigned char S2_35_28; unsigned char S2_43_36;
      unsigned char S3_35_28; unsigned char S3_43_36;      
    } BITS;
  } RAM;
#if (MEDIUM_PLUS_DENSITY || HIGH_DENSITY)
  unsigned char _Reserved1[13];
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char B4                  : 1;    //1/4 bias enable
      unsigned char DUTY8               : 1;    //1/8 duty enable
      unsigned char PAGE_COM            : 1;    //LCD_RAM page selector
      unsigned char _Reserved           : 5; 
    } BITS;
  } CR4;                                        //Control register 4
#else
  unsigned char _Reserved1[14];
#endif
} LCD_TypeDef;

#endif