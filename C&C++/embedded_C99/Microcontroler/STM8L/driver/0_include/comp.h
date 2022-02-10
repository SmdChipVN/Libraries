#ifndef _COMPARE_H_
#define _COMPARE_H_

typedef struct
{
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char CMP1                : 2;    //Comparator 1 configuration
      unsigned char STE                 : 1;    //Schmitt trigger enable
      const unsigned char CMP1OUT       : 1;    //Comparator 1 output
      unsigned char EF1                 : 1;    //Comparator 1 event flag
      unsigned char IE1                 : 1;    //Comparator 1 interrupt enable
      unsigned char _Reserved           : 2;
    } BITS;
  } CSR1;                                       //Comparator control and status register 1
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char CMP2                : 2;    //Comparator 2 configuration
      unsigned char SPEED               : 1;    //Comparator 2 speed mode
      const unsigned char CMP2OUT       : 1;    //Comparator 2 output
      unsigned char EF2                 : 1;    //Comparator 2 event flag
      unsigned char IE2                 : 1;    //Comparator 2 Interrupt Enable
      unsigned char _Reserved           : 2;
    } BITS;
  } CSR2;                                       //Comparator control and status register 2
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char VREFOUTEN           : 1;    //V-REFINT output enable
      unsigned char WNDWE               : 1;    //Window mode enable
      unsigned char VREFEN              : 1;    //Internal reference voltage V-REFINT enable
      unsigned char INSEL               : 3;    //Comparator 2 inverting input selection
      unsigned char OUTSEL              : 2;    //Comparator 2 output selection
    } BITS;
  } CSR3;                                       //Comparator control and status register 3
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char INVTRIG             : 3;    //COMP2 inverting input
      unsigned char NINVTRIG            : 3;    //COMP2 non inverting input
      unsigned char _Reserved           : 2;
    } BITS;
  } CSR4;                                       //Comparator control and status register 4
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char VREFTRIG            : 3;    //V-REFINT outputs
      unsigned char DACTRIG             : 3;    //DAC outputs
      unsigned char _Reserved           : 2;
    } BITS;
  } CSR5;                                       //Comparator control and status register 5
} COMP_TypeDef;

#endif