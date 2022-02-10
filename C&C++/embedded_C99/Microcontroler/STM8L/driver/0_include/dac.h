#ifndef _DAC_H_
#define _DAC_H_

typedef union
{
  struct
  {
    unsigned char _Reserved[4];
    union
    {
      unsigned char REG;
      struct
      {
        unsigned char SWTRIG1           : 1;    //DAC channel 1 software trigger
#if (MEDIUM_DENSITY)
        unsigned char _Reserved         : 7; 
#else
        unsigned char SWTRIG2           : 1;    //DAC channel 2 software trigger
        unsigned char _Reserved         : 6;
#endif
      } BITS;
    } SWTRIGR;                                  //DAC software trigger register
    union
    {
      unsigned char REG;
      struct
      {
        unsigned char DMAUDR1           : 1;    //DAC channel DMA underrun flag
#if (MEDIUM_DENSITY)
        unsigned char _Reserved         : 7; 
#else
        unsigned char DMAUDR2           : 1;    //DAC channel DMA underrun flag
        unsigned char _Reserved         : 6;
#endif
      } BITS;
    } SR;                                       //DAC status register
    unsigned char _Reserved1[48];
  };  
  struct
  {
    union
    {
      unsigned char REG;
      struct
      {
        unsigned char EN                : 1;    //DAC channel enable
        unsigned char BOFF              : 1;    //DAC channel output buffer disable
        unsigned char TEN               : 1;    //DAC channel trigger enable
        unsigned char TSEL              : 3;    //DAC channel x trigger selection.
#if (MEDIUM_DENSITY)
        unsigned char _Reserved         : 2;
#else
        unsigned char WAVEN             : 2;    //DAC channel x noise/triangle waveform generation enable
#endif        
      } BITS;    
    } CR1;                                      //DAC channel x control register 1
    union
    {
      unsigned char REG;
      struct
      {
#if (MEDIUM_DENSITY)
        unsigned char _Reserved         : 4;
#else
        unsigned char MAMP              : 4;    //DAC channel x mask/amplitude selector
#endif        
        unsigned char DMAEN             : 1;    //DAC DMA enable
        unsigned char DMAUDRIE          : 1;    //DAC channel DMA underrun interrupt enable
        unsigned char _Reserved1        : 2;
      } BITS;
    } CR2;                                      //DAC channel x control register 2
    unsigned char _Reserved[6];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char RDHR_11_8         : 4;
        unsigned char _Reserved         : 4;
        unsigned char RDHR_7_0;
      } BITS;
    } RDHR;                                     //DAC channel x right aligned data holding register
    unsigned char _Reserved1[2];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char LDHR_15_8;
        unsigned char _Reserved         : 4;
        unsigned char LDHR_7_4          : 4;
      } BITS;
    } LDHR;                                     //DAC channel x left aligned data holding register
    unsigned char _Reserved2[2];
    unsigned char DHR8;                         //DAC channel x 8-bit data holding register
    unsigned char _Reserved3[15];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char RDHR_11_8         : 4;
        unsigned char _Reserved         : 4;
        unsigned char RDHR_7_0;
      } BITS;
    } DRDHR;                                    //DAC channel x dual mode right aligned data holding register
    unsigned char _Reserved4[2];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char LDHR_15_8;
        unsigned char _Reserved         : 4;
        unsigned char LDHR_7_4          : 4;
      } BITS;
    } DLDHR;                                    //DAC channel x dual mode left aligned data holding register
    unsigned char _Reserved5[2];
    unsigned char DDHR8;                        //DAC channel x dual mode 8-bit data holding register
    unsigned char _Reserved6[3];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char DOR_11_8          : 4;
        unsigned char _Reserved         : 4;
        unsigned char DOR_7_0;
      } BITS;
    } DOR;                                      //DAC channel x data output register
    unsigned char _Reserved7[8];
  } CH1;  
#if (HIGH_DENSITY)
  struct
  {
    unsigned char _Reserved[2];
    union
    {
      unsigned char REG;
      struct
      {
        unsigned char EN                : 1;     //DAC channel enable
        unsigned char BOFF              : 1;     //DAC channel output buffer disable
        unsigned char TEN               : 1;     //DAC channel trigger enable
        unsigned char TSEL              : 3;     //DAC channel x trigger selection.
        unsigned char WAVEN             : 2;     //DAC channel x noise/triangle waveform generation enable
      } BITS;
    } CR1;                                       //DAC channel x control register 1
    union
    {
      unsigned char REG;
      struct
      {
        unsigned char MAMP              : 4;      //DAC channel x mask/amplitude selector
        unsigned char DMAEN             : 1;      //DAC DMA enable
        unsigned char DMAUDRIE          : 1;      //DAC channel DMA underrun interrupt enable
        unsigned char _Reserved         : 2;
      } BITS;
    } CR2;                                        //DAC channel x control register 2
    unsigned char _Reserved1[16];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char RDHR_11_8         : 4;
        unsigned char _Reserved         : 4;
        unsigned char RDHR_7_0;
      } BITS;
    } RDHR;                                     //DAC channel x right aligned data holding register
    unsigned char _Reserved2[2];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char LDHR_15_8;
        unsigned char _Reserved         : 4;
        unsigned char LDHR_7_4          : 4;
      } BITS;
    } LDHR;                                     //DAC channel x left aligned data holding register
    unsigned char _Reserved3[2];
    unsigned char DHR8;                         //DAC channel x 8-bit data holding register
    unsigned char _Reserved4[5];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char RDHR_11_8         : 4;
        unsigned char _Reserved         : 4;
        unsigned char RDHR_7_0;
      } BITS;
    } DRDHR;                                    //DAC channel x dual mode right aligned data holding register
    unsigned char _Reserved5[2];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char LDHR_15_8;
        unsigned char _Reserved         : 4;
        unsigned char LDHR_7_4          : 4;
      } BITS;
    } DLDHR;                                    //DAC channel x dual mode left aligned data holding register
    unsigned char _Reserved6;
    unsigned char DDHR8;                        //DAC channel x dual mode 8-bit data holding register
    unsigned char _Reserved7[6];
    union
    {
      unsigned short REG;
      struct
      {
        unsigned char HIGH;
        unsigned char LOW;
      } REGS;
      struct
      {
        unsigned char DOR_11_8          : 4;
        unsigned char _Reserved         : 4;
        unsigned char DOR_7_0;
      } BITS;
    } DOR;                                      //DAC channel x data output register
    unsigned char _Reserved8[4];
  } CH2;
#endif
} DAC_TypeDef;

#endif