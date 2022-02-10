//need 2 endpoint

#ifndef _USBP_HID_H_
#define _USBP_HID_H_

#include <USBP.h>

//==============================================================================================================================================================
//====================================================          Host to Device          ========================================================================
//==============================================================================================================================================================
typedef enum
{
  USB_HID_INTERFACE_STANDARD_REQUEST_GET_DESCRIPTOR     = 0x06,
  USB_HID_INTERFACE_STANDARD_REQUEST_SET_DESCRIPTOR     = 0x07,
} USB_HID_INTERFACE_STANDARD_REQUEST;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_INTERFACE_CLASS_REQUEST_GET_REPORT    = 0x01,
  USB_HID_INTERFACE_CLASS_REQUEST_GET_IDLE      = 0x02,
  USB_HID_INTERFACE_CLASS_REQUEST_GET_PROTOCOL  = 0x03,
  USB_HID_INTERFACE_CLASS_REQUEST_SET_REPORT    = 0x09,  
  USB_HID_INTERFACE_CLASS_REQUEST_SET_IDLE      = 0x0A,
  USB_HID_INTERFACE_CLASS_REQUEST_SET_PROTOCOL  = 0x0B,
} USB_HID_INTERFACE_CLASS_REQUEST;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_DESCRIPTOR_HID        = 0x21,
  USB_HID_DESCRIPTOR_REPORT     = 0x22,
  USB_HID_DESCRIPTOR_PHYSICAL   = 0x23,
} USB_HID_DESCRIPTOR;
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
    struct
    {
      USB_HID_INTERFACE_STANDARD_REQUEST bRequest;
      __packed union
      {
        STRUCT(,
          unsigned char Index;
          USB_HID_DESCRIPTOR Type;
          unsigned short LanguageID;
          unsigned short Length;)
          GET_DESCRIPTOR,
          SET_DESCRIPTOR;
      };
    } Standard;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct
    {
      USB_HID_INTERFACE_CLASS_REQUEST bRequest;
      __packed union
      {
        STRUCT(,
          unsigned char Index;
          unsigned char Type;
          unsigned short Interface;
          unsigned short Length;)
          GET_REPORT,
          SET_REPORT;
        RSTRUCT(GET_IDLE, unsigned short, Index, Interface, _1);
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        STRUCT(SET_IDLE,
          unsigned char Index;
          unsigned char Duration;
          unsigned short Interface;
          unsigned short _0;);
        RSTRUCT(GET_PROTOCOL, unsigned short, _0, Interface, _1);
        RSTRUCT(SET_PROTOCOL, unsigned short, IsReportProtocol, Interface, _0);
      };
    } Class;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
//    __packed union
//    {
//      USB_HID_INTERFACE_VENDER_REQUEST UN_DEFINE;
//    } Vender;
  };
} USB_HID_REQUEST_TypeDef;
//==============================================================================================================================================================
//===========================================================          Device to Host          =================================================================
//==============================================================================================================================================================
typedef enum
{
  USB_HID_REPORT_IN_OUT_DATA            = 0,
  USB_HID_REPORT_IN_OUT_CONST           = 1,
  USB_HID_REPORT_IN_OUT_ARRAY           = 0,
  USB_HID_REPORT_IN_OUT_VARIABLE        = 2,
  USB_HID_REPORT_IN_OUT_ABSOLUTE        = 0,
  USB_HID_REPORT_IN_OUT_RELATIVE        = 4,
} USB_HID_REPORT_IN_OUT;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_REPORT_MAIN_INPUT             = (8  << 4),
  USB_HID_REPORT_MAIN_OUTPUT            = (9  << 4),
  USB_HID_REPORT_MAIN_COLLECTION        = (10 << 4),
  USB_HID_REPORT_MAIN_FEATURE           = (11 << 4),
  USB_HID_REPORT_MAIN_COLLECTION_END    = (12 << 4),
} USB_HID_REPORT_MAIN;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_REPORT_GLOBAL_USAGE           = ((0  << 4) | 4),
  USB_HID_REPORT_GLOBAL_LOGICAL_MIN     = ((1  << 4) | 4),
  USB_HID_REPORT_GLOBAL_LOGICAL_MAX     = ((2  << 4) | 4),
  USB_HID_REPORT_GLOBAL_PHYSICAL_MIN    = ((3  << 4) | 4),
  USB_HID_REPORT_GLOBAL_PHYSICAL_MAX    = ((4  << 4) | 4),
  USB_HID_REPORT_GLOBAL_UNIT_EXPONENT   = ((5  << 4) | 4),
  USB_HID_REPORT_GLOBAL_UNIT            = ((6  << 4) | 4),
  USB_HID_REPORT_GLOBAL_REPORT_SIZE     = ((7  << 4) | 4),
  USB_HID_REPORT_GLOBAL_REPORT_ID       = ((8  << 4) | 4),
  USB_HID_REPORT_GLOBAL_REPORT_COUNT    = ((9  << 4) | 4),
  USB_HID_REPORT_GLOBAL_PUSH            = ((10 << 4) | 4),
  USB_HID_REPORT_GLOBAL_POP             = ((11 << 4) | 4),
} USB_HID_REPORT_GLOBAL;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_REPORT_LOCAL_USAGE            = ((0 << 4) | 8),
  USB_HID_REPORT_LOCAL_USAGE_MIN        = ((1 << 4) | 8),
  USB_HID_REPORT_LOCAL_USAGE_MAX        = ((2 << 4) | 8),
} USB_HID_REPORT_LOCAL;
//==============================================================================================================================================================
typedef struct
{
  union
  {
    union 
    {
      struct
      {
        unsigned char bLength;                                  //Numeric expression that is the total size of the HID descriptor, include arrays[bNumDescriptors]
        USB_HID_DESCRIPTOR bDescriptorType;                     //USB_HID_DESCRIPTOR_HID = 0x21
        union
        {
          STRUCT(HID,
            unsigned short              bcdHID          ;       //HID specification release in BCD, let's use 0x0101
            unsigned char               bCountryCode    ;       //Country code of the localized hardware
            unsigned char               bNumDescriptors ;       //Number of HID class descriptors to follow
//            STRUCT(arrays[bNumDescriptors],
//              USB_HID_DESCRIPTOR        bDescriptorType ;
//              unsigned short            TotalSize       ;);     //Total size of the descriptor (i.e., HID report)
            );
        };
      } GET_DESCRIPTOR;
    } Standard;
//    union
//    {
//      
//    } Class;
//    union
//    {
//      
//    } Vender;
  };
} USB_HID_RESPOND_TypeDef;
//==============================================================================================================================================================
//==============================================================              Support             ==============================================================
//==============================================================================================================================================================
typedef struct
{
  USBDescriptor_TypeDef HID;
  USBDescriptor_TypeDef Report;
  USBDescriptor_TypeDef Physical;
} USB_HID_Descriptors_TypeDef;
//==============================================================================================================================================================
typedef enum
{
  USB_HID_REQUEST_NULL                  = 0,
  USB_HID_REQUEST_DATA_IN               = 1,
  USB_HID_REQUEST_DATA_OUT              = 2,
} USB_HID_REQUEST;
typedef struct
{
  USB_HID_REQUEST Request;
  unsigned short TxSize;
  unsigned char __gptr* TxPointer;
  unsigned short RxSize;
  unsigned short RxIndex;
  unsigned char* RxBuffer;
} USB_HID_Manager_TypeDef;
extern __no_init USB_HID_Manager_TypeDef USB_HID_Manager;
//==============================================================================================================================================================
//=========================================================        User must declare         ===================================================================
//==============================================================================================================================================================
/*
  +) return:
    -if in receiving have sending data by: return 0;
    -other: return 1;
*/
reg8 USB_HID_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length);

//using function
void USB_HID_Init(unsigned char* RxBuffer);
#define USB_HID_SendEndpoint0(Data, Size)       USB_HID_Manager.TxPointer = Data; USB_HID_Manager.TxSize = Size

#endif