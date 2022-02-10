#ifndef _USBP_TYPE_DEF_H_
#define _USBP_TYPE_DEF_H_

#include <USBP_ENUM.h>
#include <common.h>
#include <define.h>
//==============================================================================================================================================================
//=======================================================       HOST TO DEVICE      ============================================================================
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef
BUNION(USBP_EP_REQUEST_TypeDef, unsigned short,
  Address                               , 4,
  _reserved                             , 3,
  IsOut                                 , 1,
  _reserved1                            , 8);
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
    union
    {
      struct
      {
        USB_DEVICE_STANDARD_REQUEST bRequest;
        __packed union
        {
          RSTRUCT(GET_STATUS, unsigned short,_0[2], _2);                        //require USBD_RESPOND -> Device -> GET_STATUS        
          RSTRUCT(CLEAR_FEATURE, unsigned short, Feature, _0[2]);               //clear unsigned char (DEVICE_REMOTE_WAKEUP and TEST_MODE); require USBD_RESPOND(NULL)
          RSTRUCT(SET_FEATURE, unsigned short, Feature, _0[2]);                 //set unsigned char (DEVICE_REMOTE_WAKEUP and TEST_MODE); require USBD_RESPOND(NULL)
          RSTRUCT(SET_ADDRESS, unsigned short, Address, _0[2]);                 //set Device's Address, require USBD_RESPOND(NULL)
          STRUCT(,                                                
            unsigned char                       Index           ;
            USB_DEVICE_STANDARD_DESCRIPTOR      Type            ;
            unsigned short                      LanguageID      ;
            unsigned short                      MaxLength       ;)
            GET_DESCRIPTOR,                                                     //require USBD_RESPOND -> Device -> GET_DESCRIPTOR
            SET_DESCRIPTOR;                                                     //send Descriptor; require USBD_RESPOND(NULL)
          RSTRUCT(GET_CONFIGURATION, unsigned short, _0[2], _1);                //require USBD_RESPOND -> Device -> GET_CONFIGURATION
          RSTRUCT(SET_CONFIGURATION, unsigned short, Configuration, _0[2]);     //require USBD_RESPOND(NULL)
        };
      } Standard;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_DEVICE_CLASS_REQUEST bRequest;
      } Class;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_DEVICE_VENDER_REQUEST bRequest;
      } Vender;
    } Device;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    union
    {
      struct
      {
        USB_INTERFACE_STANDARD_REQUEST bRequest;
        __packed union
        {
          RSTRUCT(GET_STATUS, unsigned short, _0, InterfaceID, _2);             //require USBD_RESPOND -> Interface -> GET_STATUS
          RSTRUCT(CLEAR_FEATURE, unsigned short, Feature, InterfaceID, _0);     //clear unsigned char for Interface; require USBD_RESPOND(NULL)
          RSTRUCT(SET_FEATURE, unsigned short, Feature, InterfaceID, _0);       //set unsigned char for Interface; require USBD_RESPOND(NULL)
          RSTRUCT(GET_INTERFACE, unsigned short, _0, InterfaceID, _1);          //require USBD_RESPOND -> Interface -> GET_INTERFACE
          RSTRUCT(SET_INTERFACE, unsigned short,                                //????????????????
            Alternative,
            InterfaceID,
            _0);
        };
      } Standard;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_INTERFACE_CLASS_REQUEST bRequest;
      } Class;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_INTERFACE_VENDER_REQUEST bRequest;
      } Vender;
    } Interface;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    union
    {
      struct
      {
        USB_ENDPOINT_STANDARD_REQUEST bRequest;
        __packed union
        {
          STRUCT(GET_STATUS,                                                    //require USBD_RESPOND -> Endpoint -> GET_STATUS
            unsigned short                      _0              ;
            USBP_EP_REQUEST_TypeDef             Endpoint        ;
            unsigned short                      _2              ;);
          STRUCT(,                                                 
            unsigned short                      Feature         ;
            USBP_EP_REQUEST_TypeDef             Endpoint        ;
            unsigned short                      _0              ;)
            CLEAR_FEATURE,                                                      //require USBD_RESPOND(NULL)
            SET_FEATURE;                                                        //require USBD_RESPOND(NULL)                           
          STRUCT(SYNCH_FRAME,                                                   //?????????????????
            unsigned short                      _0              ; 
            USBP_EP_REQUEST_TypeDef             Endpoint        ; 
            unsigned short                      _2              ;);
        };
      } Standard;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_ENDPOINT_CLASS_REQUEST bRequest;
      } Class;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        USB_ENDPOINT_VENDER_REQUEST bRequest;
      } Vender;
    } Endpoint;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    union
    {
      unsigned char UserData[7];
    } Another;
  };
} USBH_SETUP_TypeDef;
//==============================================================================================================================================================
//=======================================================       DEVICE TO HOST      ============================================================================
//==============================================================================================================================================================
typedef union
{
  union Device
  {
    union Standard
    {
      BUNION(GET_STATUS, unsigned short,
        IsSelfPowered     , 1,
        IsRemoteWakeup    , 1,
        _reserved         , 14);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        unsigned char bLength;
        USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType;
        union
        {
          STRUCT(DEVICE,                                        //bLength = 18, bDescriptorType = 0x01
            unsigned short      bcdUSB                  ;       //USB Specification Number which device complies too
            USB_CLASS           bDeviceClass            ;       //Class Code (Assigned by USB Org)
            unsigned char       bDeviceSubClass         ;       //Subclass Code (Assigned by USB Org)
            unsigned char       bDeviceProtocol         ;       //Protocol Code (Assigned by USB Org)
            unsigned char       bMaxPacketSize          ;       //Maximum Packet Size for Zero Endpoint. Valid Sizes are 8, 16, 32, 64
            unsigned short      idVendor                ;       //Vendor ID (Assigned by USB Org)
            unsigned short      idProduct               ;       //Product ID (Assigned by Manufacturer)
            unsigned short      bcdDevice               ;       //Device Release Number
            unsigned char       iManufacturer           ;       //Manufacturer String Descriptor = GET_STRING(index = iManufacturer)
            unsigned char       iProduct                ;       //Product String Descriptor = GET_STRING(index = iProduct)
            unsigned char       iSerialNumber           ;       //Serial Number String Descriptor = GET_STRING(index = iSerialNumber)
            unsigned char       bNumConfigurations      ;);     //Number of Possible Configurations
          //----------------------------------------------------------------------------------------------------------------------------------------------------
          STRUCT(CONFIGURATION,                                 //bLength = 9, bDescriptorType = 0x02
            unsigned short      wTotalLength            ;       //Total length in bytes of data returned
            unsigned char       bNumInterfaces          ;       //Number of Interfaces
            unsigned char       bConfigurationValue     ;       //Value to use as an argument to select this configuration
            unsigned char       iConfiguration          ;       //Configuration Descriptor = GET_STRING(index = iConfiguration)
            BUNION(bmAttributes, unsigned char,
              _reserved         , 5,
              IsRemoteWakeup    , 1,
              IsSelfPowered     , 1,
              _reserved1        , 1);
            unsigned char       bMaxPower               ;);     //Maximum Power Consumption in 2mA units
          //----------------------------------------------------------------------------------------------------------------------------------------------------
          STRUCT(INTERFACE,                                     //bLength = 9, bDescriptorType = 0x04
            unsigned char       bInterfaceNumber        ;       //Number of this Interface
            unsigned char       bAlternateSetting       ;       //Value used to select alternative setting
            unsigned char       bNumEndpoints           ;       //Number of Endpoints used for this interface
            USB_CLASS           bInterfaceClass         ;       //Class Code (Assigned by USB Org)
            unsigned char       bInterfaceSubClass      ;       //Subclass Code (Assigned by USB Org)
            unsigned char       bInterfaceProtocol      ;       //Protocol Code (Assigned by USB Org)
            unsigned char       iInterface              ;);     //Index of String Descriptor Describing this Interface Descriptor = GET_STRING(index = iInterface)
          //----------------------------------------------------------------------------------------------------------------------------------------------------
          STRUCT(ENDPOINT,                                      //bLength = 7, bDescriptorType = 0x05
            BUNION(bEndpointAddress, unsigned char,
              Address           , 4,
              _reserved         , 3,
              IsIn              , 1);
            BUNIONT(bmAttributes, unsigned char REG;,
                USB_ENDPOINT_TYPE               Type                    : 2;
                USB_SYNCHRONISATION_TYPE        SynchronisationType     : 2;    //in Iso mode
                USB_USAGE_TYPE                  UsageType               : 2;    //in Iso mode
                unsigned char                   _reserved               : 2;);
            unsigned short      wMaxPacketSize;                 //Maximum Packet Size this endpoint is capable of sending or receiving
            unsigned char       bInterval;);                    //Interval for polling endpoint data transfers
          //----------------------------------------------------------------------------------------------------------------------------------------------------
          UNION(STRING,
            unsigned short wLANGID[8];                          //Supported Language Code (e.g. 0x0409 English - United States), bLength = n, bDescriptorType = 0x03
            unsigned char  bString[16];);                       //Unicode Encoded String, bLength = n, bDescriptorType = 0x03
        };
      } GET_DESCRIPTOR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct {unsigned short UN_DEFINE; } GET_CONFIGURATION;
    };
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Class;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Vender;
  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  union
  {
    union
    {
      struct { unsigned short UN_DEFINE; } GET_STATUS;
      struct { unsigned short UN_DEFINE; } GET_INTERFACE;
    } Standard;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Class;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Vender;
  } Interface;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  union
  {
    union
    {
      struct { unsigned short IsHalt; } GET_STATUS;
    } Standard;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Class;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct {unsigned short UN_DEFINE; } Vender;
  } Endpoint;
} USBD_RESPOND_TypeDef;
//==============================================================================================================================================================
//=======================================================          SUPPORT          ============================================================================
//==============================================================================================================================================================
typedef struct
{
  const unsigned char __code* Data;
  unsigned char Length;
  const void __code* Child;
} USBDescriptor_TypeDef;
//==============================================================================================================================================================
typedef struct
{
  USBDescriptor_TypeDef Device;
  struct
  {
    unsigned char Number;
    const USBDescriptor_TypeDef __code* Descriptors;
  } Configuration;
  struct
  {
    unsigned char Number;
    const USBDescriptor_TypeDef __code* Descriptors;
  } String;
  const void __code* Class;
} USBDescriptors_TypeDef;
//==============================================================================================================================================================
typedef struct
{
  unsigned char Address;
  USB_ENDPOINT_TYPE Type;
  struct
  {
    USB_ENDPOINT_STATUS Status;
    unsigned char DataID;
  } TX;
  struct
  {
    USB_ENDPOINT_STATUS Status;
    unsigned char DataID;
  } RX;
} USBEndpoint_TypeDef;

#endif