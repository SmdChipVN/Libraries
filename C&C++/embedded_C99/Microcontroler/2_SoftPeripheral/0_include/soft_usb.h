#ifndef _SOFT_USB_H_
#define _SOFT_USB_H_

#include <config.h>

typedef struct
{
  struct
  {
    unsigned char Send          : 1;
    unsigned char Receive       : 1;
    unsigned char _Reserved     : 6;
  } Status;
  unsigned char CountCramming;
  unsigned char Length;
  unsigned char Buffer[64];
} USBObject_TypeDef;

#ifdef USB_OBJECT
  void SUSB_Process(void(*SUSB_Received)(unsigned char* Data, unsigned short Length));
  void SUSB_WriteBytes(unsigned char* Data, unsigned short Length);
#else
  void SUSB_Process(USBObject_TypeDef* USBObject, void(*SUSB_Received)(unsigned char* Data, unsigned short Length));
  void SUSB_WriteBytes(USBObject_TypeDef* USBObject, unsigned char* Data, unsigned short Length);
#endif
  
#endif