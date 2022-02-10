#ifndef _USB_MASS_H_
#define _USB_MASS_H_

#include <USBP.h>
//==============================================================================================================================================================
typedef enum
{
  USB_MASS_INTERFACE_CLASS_REQUEST_GET_MAX_LUN          = 0xFE,
  USB_MASS_INTERFACE_CLASS_REQUEST_RESET                = 0xFF,
} USB_MASS_INTERFACE_CLASS_REQUEST;
//==============================================================================================================================================================
__packed typedef struct
{
  BUNIONT(bmRequestType, unsigned char REG;,
    USB_RECIPIENT       Recipient       : 5;
    USB_REQUEST_TYPE    Type            : 2;
    unsigned char       IsDevToHost     : 1;);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  union
  {
//    struct
//    {
//      USB_HID_INTERFACE_STANDARD_REQUEST bRequest;
//    } Standard;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct
    {
      USB_MASS_INTERFACE_CLASS_REQUEST bRequest;
      __packed union
      {
        RSTRUCT(RESET, unsigned short, _00, Interface, _01);
        RSTRUCT(GET_MAX_LUN, unsigned short, _0, Interface, _1);
      };
    } Class;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
//    __packed union
//    {
//      USB_HID_INTERFACE_VENDER_REQUEST UN_DEFINE;
//    } Vender;
  };
} USB_MASS_REQUEST_TypeDef;
//==============================================================================================================================================================
typedef struct
{
  unsigned char dCBWSignature[4];               //"USBC"
  unsigned char dCBWTag[4];
  unsigned long dCBWDataTransferLength;
  BUNION(bmCBWFlags, unsigned char,
    _reserved                           , 6,
    Obsolete                            , 1,
    IsDeviceToHost                      , 1);
  unsigned char bCBWLUN;
  unsigned char bCBWCBLength;
  unsigned char CBWCB[16];
} USB_MASS_CBW_TypeDef;
////--------------------------------------------------------------------------------------------------------------------------------------------------------------
//typedef struct
//{
//  unsigned char dCBWSignature[4];               //"USBC"
//  unsigned char dCBWTag[4];
//  unsigned long dCSWDataResidue;
//  unsigned char bCSWStatus;                     //0x00: Command Passed ("good status")
//                                                //0x01: Command Failed
//                                                //0x02: Phase Error
//                                                //0x03-04: Obsolete
//                                                //0x05:FF: Reserved
//} USB_MASS_CSW_TypeDef;
//==============================================================================================================================================================
typedef enum
{
  USB_MASS_STATE_READY                  = 0,
  USB_MASS_STATE_PREPARE_READ           = 1,
  USB_MASS_STATE_PREPARE_WRITE          = 2,
  USB_MASS_STATE_RESPOND_STATUS         = 3, 
} USB_MASS_STATE;
typedef struct
{
  unsigned char dCBWTag[4];
  unsigned long dCSWDataResidue;
  unsigned char bCSWStatus;                     //0x00: Command Passed ("good status")
                                                //0x01: Command Failed
                                                //0x02: Phase Error
                                                //0x03-04: Obsolete
                                                //0x05:FF: Reserved
  USB_MASS_STATE State;
  unsigned short Sequences;
  unsigned long DataAddress;
} USB_MASS_Manager_TypeDef;
extern __no_init USB_MASS_Manager_TypeDef USB_MASS_Manager;
//==============================================================================================================================================================
void USB_MASS_Init(void);
//==============================================================================================================================================================
void USB_MASS_ProcessRequest(unsigned char* Data, reg16 Length);        //check USB_MASS_Manager.State for request, USB_MASS_STATE_PREPARE_READ or USB_MASS_STATE_PREPARE_WRITE

#endif