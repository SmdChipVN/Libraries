#include <USB_HID.h>

static __code const unsigned char _USB_HID_ReportDecriptor_Data[] = {
  USB_HID_REPORT_GLOBAL_USAGE                   | 2, 0x00, 0xFF,        //usage page = vendor-defined
  USB_HID_REPORT_LOCAL_USAGE                    | 1, 0x01,              //<usage 1st>
    USB_HID_REPORT_MAIN_COLLECTION              | 1, 0x01,              //begin <usage 1st> <collection 1st>    
      USB_HID_REPORT_GLOBAL_LOGICAL_MIN         | 1, 0x00,              //value of each field min = 0x00
      USB_HID_REPORT_GLOBAL_LOGICAL_MAX         | 1, 0xFF,              //value of each field max = 0xFF      
      USB_HID_REPORT_GLOBAL_REPORT_SIZE         | 1, 8,                 //8 bit in each field
      USB_HID_REPORT_GLOBAL_REPORT_COUNT        | 1, 64,                //64 fields
      USB_HID_REPORT_LOCAL_USAGE_MIN            | 1, 1,
      USB_HID_REPORT_LOCAL_USAGE_MAX            | 1, 1,
      USB_HID_REPORT_MAIN_INPUT                 | 1, USB_HID_REPORT_IN_OUT_DATA | USB_HID_REPORT_IN_OUT_VARIABLE | USB_HID_REPORT_IN_OUT_ABSOLUTE,      
      USB_HID_REPORT_LOCAL_USAGE_MIN            | 1, 1,
      USB_HID_REPORT_LOCAL_USAGE_MAX            | 1, 1,
      USB_HID_REPORT_MAIN_OUTPUT                | 1, USB_HID_REPORT_IN_OUT_DATA | USB_HID_REPORT_IN_OUT_VARIABLE | USB_HID_REPORT_IN_OUT_ABSOLUTE,      
  USB_HID_REPORT_MAIN_COLLECTION_END            | 0,                    //end <usage 1st> <collection 1st>
};
static __code const unsigned char _USB_DeviceDescriptor_Data[] = {
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > DEVICE,
              MEMBER(unsigned char bLength, 18),
              MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE),
                       MEMBER(unsigned short bcdUSB, 0x00, 0x02),
                       MEMBER(USB_CLASS      bDeviceClass, USB_CLASS_DEVICE),
                       MEMBER(unsigned char  bDeviceSubClass, 0x00),
                       MEMBER(unsigned char  bDeviceProtocol, 0x00),
                       MEMBER(unsigned char  bMaxPacketSize, 64),
                       MEMBER(unsigned short idVendor, 0x88, 0x77),
                       MEMBER(unsigned short idProduct, 0x66, 0x55),
                       MEMBER(unsigned short bcdDevice, 0x00, 0x02),
                       MEMBER(unsigned char  iManufacturer, 1),
                       MEMBER(unsigned char  iProduct, 2),
                       MEMBER(unsigned char  iSerialNumber, 3),
                       MEMBER(unsigned char  bNumConfigurations, 1))};
static __code const unsigned char _USB_ConfigurationDescription_Data[] = {
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > CONFIGURATION,
          MEMBER(unsigned char bLength, 9),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_CONFIGURATION),
              MEMBER(unsigned short wTotalLength, 9 + 9 + 9 + 7 + 7, 0x00),
              MEMBER(unsigned char  bNumInterfaces, 1),
              MEMBER(unsigned char  bConfigurationValue, 1),
              MEMBER(unsigned char  iConfiguration, 0),
              BVALUE(bmAttributes,
                       _Reserved           , 5, 0,
                       IsRemoteWakeup      , 1, 0,
                       IsSelfPowered       , 1, 0,
                       _Reserved1          , 1, 0),
              MEMBER(unsigned char  bMaxPower, 50)),
//-----------------------------------
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > INTERFACE,
          MEMBER(unsigned char bLength, 9),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE),
                 MEMBER(unsigned char bInterfaceNumber, 0),
                 MEMBER(unsigned char bAlternateSetting, 0),
                 MEMBER(unsigned char bNumEndpoints, 2),
                 MEMBER(USB_CLASS     bInterfaceClass, USB_CLASS_HID),
                 MEMBER(unsigned char bInterfaceSubClass, 0x00),
                 MEMBER(unsigned char bInterfaceProtocol, 0x00),
                 MEMBER(unsigned char iInterface, 4)),
//-----------------------------------
  SVALUE(USB_HID_RESPOND_TypeDef > Standard > GET_DESCRIPTOR > HID,
        MEMBER(unsigned char bLength, 9),
        MEMBER(USB_HID_DESCRIPTOR bDescriptorType, USB_HID_DESCRIPTOR_HID),
            MEMBER(unsigned short bcdHID, 0x01, 0x01),
            MEMBER(unsigned char bCountryCode, 0x00),
            MEMBER(unsigned char bNumDescriptors, 1),
//          struct
//          {
              MEMBER(USB_HID_DESCRIPTOR bDescriptorType, USB_HID_DESCRIPTOR_REPORT),
              MEMBER(unsigned short TotalSize, sizeof(_USB_HID_ReportDecriptor_Data), 0)),
//          } arrays[bNumDescriptors];
//-----------------------------------
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > ENDPOINT,
          MEMBER(unsigned char bLength, 7),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT),
              BVALUE(bEndpointAddress,
                       Address     , 4, 1,
                       _Reserved   , 3, 0,
                       IsIn        , 1, 0),
              BVALUE(bmAttributes,
                       USB_ENDPOINT_TYPE        Type                      , 2, USB_ENDPOINT_TYPE_INTERRUPT,
                       USB_SYNCHRONISATION_TYPE SynchronisationType       , 2, 0,
                       USB_USAGE_TYPE           UsageType                 , 2, 0,
                       unsigned char            _Reserved                 , 2, 0),
              MEMBER(unsigned short wMaxPacketSize, 64, 0),
              MEMBER(unsigned char  bInterval, 5)),
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > ENDPOINT,
          MEMBER(unsigned char bLength, 7),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT),          
              BVALUE(bEndpointAddress,
                       Address     , 4, 1,
                       _Reserved   , 3, 0,
                       IsIn        , 1, 1),
              BVALUE(bmAttributes,
                       USB_ENDPOINT_TYPE        Type                      , 2, USB_ENDPOINT_TYPE_INTERRUPT,
                       USB_SYNCHRONISATION_TYPE SynchronisationType       , 2, 0,
                       USB_USAGE_TYPE           UsageType                 , 2, 0,
                       unsigned char            _Reserved                 , 2, 0),
              MEMBER(unsigned short wMaxPacketSize, 64, 0),
              MEMBER(unsigned char  bInterval, 5))};
static __code const unsigned char _USB_StringDescriptor_SupportLanguage_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 4),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(English, 0x09, 0x04)))};
static __code const unsigned char _USB_StringDescriptor_Manufacturer_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 10),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(Char[0], 'L', 0x00),
                          MEMBER(Char[1], 'i', 0x00),
                          MEMBER(Char[2], 'e', 0x00),
                          MEMBER(Char[3], 's', 0x00)))};
static __code const unsigned char _USB_StringDescriptor_Product_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 20),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(Char[0], 'S', 0x00),
                          MEMBER(Char[1], 'T', 0x00),
                          MEMBER(Char[2], 'M', 0x00),
                          MEMBER(Char[3], '3', 0x00),
                          MEMBER(Char[4], '2', 0x00),
                          MEMBER(Char[5], 'B', 0x00),
                          MEMBER(Char[6], 'o', 0x00),
                          MEMBER(Char[7], 'o', 0x00),
                          MEMBER(Char[8], 't', 0x00)))};
static __code const unsigned char _USB_StringDescriptor_SerialNumber_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 10),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(Char[0], 'F', 0x00),
                          MEMBER(Char[1], 'F', 0x00),
                          MEMBER(Char[2], 'F', 0x00),
                          MEMBER(Char[3], 'F', 0x00)))};

//config[0] -> interface[0] -> endpoint
static __code const USBDescriptor_TypeDef _USB_EndpointDescriptor[] = {
  {.Data = _USB_ConfigurationDescription_Data + 9 + 9 + 9, .Length = 7, .Child = NULL},
  {.Data = _USB_ConfigurationDescription_Data + 9 + 9 + 9 + 7, .Length = 7, .Child = NULL},
};
//config[0] -> interface
static __code const USBDescriptor_TypeDef _USB_InterfaceDescriptor[] = {
  {.Data = _USB_ConfigurationDescription_Data + 9, .Length = 9 + 9 + 7 + 7, .Child = _USB_EndpointDescriptor},
};
//config
static __code const USBDescriptor_TypeDef _USB_ConfigurationDescriptor[] = {
  {.Data = _USB_ConfigurationDescription_Data, sizeof(_USB_ConfigurationDescription_Data), .Child = _USB_InterfaceDescriptor},
};
//string
static __code const USBDescriptor_TypeDef _USB_StringDescriptor[4] = {
  {.Data = _USB_StringDescriptor_SupportLanguage_Data, .Length = sizeof(_USB_StringDescriptor_SupportLanguage_Data)},
  {.Data = _USB_StringDescriptor_Manufacturer_Data, .Length = sizeof(_USB_StringDescriptor_Manufacturer_Data)},
  {.Data = _USB_StringDescriptor_Product_Data, .Length = sizeof(_USB_StringDescriptor_Product_Data)},
  {.Data = _USB_StringDescriptor_SerialNumber_Data, .Length = sizeof(_USB_StringDescriptor_SerialNumber_Data)},
};
static __code const USB_HID_Descriptors_TypeDef _USB_HID_Descriptors = {
  .HID = {.Data = _USB_ConfigurationDescription_Data + 9 + 9, .Length = 9, .Child = NULL},
  .Report = {.Data = _USB_HID_ReportDecriptor_Data, .Length = sizeof(_USB_HID_ReportDecriptor_Data), .Child = NULL},
  .Physical = {.Data = NULL, .Length = 0, .Child = NULL},
};
//======================================================================================================================
__code const USBDescriptors_TypeDef USBDescriptors = {
  .Device = {.Data = _USB_DeviceDescriptor_Data, .Length = sizeof(_USB_DeviceDescriptor_Data)},
  .Configuration = {.Number = sizeof(_USB_ConfigurationDescriptor) / sizeof(USBDescriptor_TypeDef), .Descriptors = _USB_ConfigurationDescriptor},
  .String = {.Number = sizeof(_USB_StringDescriptor) / sizeof(USBDescriptor_TypeDef), .Descriptors = _USB_StringDescriptor},
  .Class = &_USB_HID_Descriptors,
};