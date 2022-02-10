#ifndef _AES_H_
#define _AES_H_

typedef struct
{
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char EN                  : 1;    //Enable
      unsigned char MOD                 : 2;    //AES mode of operation
      unsigned char CCFC                : 1;    //Computation complete flag clear
      unsigned char ERRFC               : 1;    //Error flags clear
      unsigned char CCIE                : 1;    //Computation complete interrupt enable
      unsigned char ERRIE               : 1;    //Error interrupt enable
      unsigned char DMAEN               : 1;    //DMA enable
    } BITS;
  } CR;                                         //AES control register
  union
  {
    const unsigned char REG;
    struct
    {
      const unsigned char CCF           : 1;    //Computation complete flag
      const unsigned char RDERR         : 1;    //Read error flag
      const unsigned char WRERR         : 1;    //Write error flag
      const unsigned char _Reserved     : 5;
    } BITS;
  } SR;                                         //AES status register
  unsigned char DINR;                           //AES data input register
  unsigned char DOUTR;                          //AES data output register
} AES_TypeDef;

#endif