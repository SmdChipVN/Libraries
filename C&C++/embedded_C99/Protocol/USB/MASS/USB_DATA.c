#include <USB_MASS.h>

static __code const unsigned char _USB_DeviceDescriptor_Data[] = {
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > DEVICE,
              MEMBER(unsigned char bLength, 18),
              MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE),
                       MEMBER(unsigned short bcdUSB, 0x00, 0x02),
                       MEMBER(USB_CLASS      bDeviceClass, USB_CLASS_DEVICE),
                       MEMBER(unsigned char  bDeviceSubClass, 0x00),
                       MEMBER(unsigned char  bDeviceProtocol, 0x00),
                       MEMBER(unsigned char  bMaxPacketSize, 64),
                       MEMBER(unsigned short idVendor, 0x44, 0x55),
                       MEMBER(unsigned short idProduct, 0x22, 0x33),
                       MEMBER(unsigned short bcdDevice, 0x00, 0x02),
                       MEMBER(unsigned char  iManufacturer, 1),
                       MEMBER(unsigned char  iProduct, 2),
                       MEMBER(unsigned char  iSerialNumber, 3),
                       MEMBER(unsigned char  bNumConfigurations, 1))};
//==============================================================================================================================================================
static __code const unsigned char _USB_ConfigurationDescription_Data[] = {
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > CONFIGURATION,
          MEMBER(unsigned char bLength, 9),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_CONFIGURATION),
              MEMBER(unsigned short wTotalLength, 9 + 9 + 7 + 7, 0x00),
              MEMBER(unsigned char  bNumInterfaces, 1),
              MEMBER(unsigned char  bConfigurationValue, 1),
              MEMBER(unsigned char  iConfiguration, 0),
              BVALUE(bmAttributes,
                       _Reserved           , 5, 0,
                       IsRemoteWakeup      , 1, 0,
                       IsSelfPowered       , 1, 0,
                       _Reserved1          , 1, 0),
              MEMBER(unsigned char  bMaxPower, 50)),
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > INTERFACE,
          MEMBER(unsigned char bLength, 9),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE),
                 MEMBER(unsigned char bInterfaceNumber, 0),
                 MEMBER(unsigned char bAlternateSetting, 0),
                 MEMBER(unsigned char bNumEndpoints, 2),
                 MEMBER(USB_CLASS     bInterfaceClass, USB_CLASS_MASS_STORAGE),
                 MEMBER(unsigned char bInterfaceSubClass, 0x06),
                 MEMBER(unsigned char bInterfaceProtocol, 0x50),
                 MEMBER(unsigned char iInterface, 4)),
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > ENDPOINT,
          MEMBER(unsigned char bLength, 7),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT),
              BVALUE(bEndpointAddress,
                       Address     , 4, 1,
                       _Reserved   , 3, 0,
                       IsIn        , 1, 1),
              BVALUE(bmAttributes,
                       USB_ENDPOINT_TYPE        Type                      , 2, USB_ENDPOINT_TYPE_BULK,
                       USB_SYNCHRONISATION_TYPE SynchronisationType       , 2, 0,
                       USB_USAGE_TYPE           UsageType                 , 2, 0,
                       unsigned char            _Reserved                 , 2, 0),
              MEMBER(unsigned short wMaxPacketSize, 64, 0),
              MEMBER(unsigned char  bInterval, 0)),
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
  SVALUE(USBD_RESPOND_TypeDef > Device > Standard > GET_DESCRIPTOR > ENDPOINT,
          MEMBER(unsigned char bLength, 7),
          MEMBER(USB_DEVICE_STANDARD_DESCRIPTOR bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT),          
              BVALUE(bEndpointAddress,
                       Address     , 4, 1,
                       _Reserved   , 3, 0,
                       IsIn        , 1, 0),
              BVALUE(bmAttributes,
                       USB_ENDPOINT_TYPE        Type                      , 2, USB_ENDPOINT_TYPE_BULK,
                       USB_SYNCHRONISATION_TYPE SynchronisationType       , 2, 0,
                       USB_USAGE_TYPE           UsageType                 , 2, 0,
                       unsigned char            _Reserved                 , 2, 0),
              MEMBER(unsigned short wMaxPacketSize, 64, 0),
              MEMBER(unsigned char  bInterval, 0))
};
//==============================================================================================================================================================
static __code const unsigned char _USB_StringDescriptor_SupportLanguage_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 4),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(English, 0x09, 0x04)))
};
//==============================================================================================================================================================
static __code const unsigned char _USB_StringDescriptor_Manufacturer_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 10),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(Char[0], 'L', 0x00),
                          MEMBER(Char[1], 'i', 0x00),
                          MEMBER(Char[2], 'e', 0x00),
                          MEMBER(Char[3], 's', 0x00)))
};
//==============================================================================================================================================================
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
                          MEMBER(Char[5], 'M', 0x00),
                          MEMBER(Char[6], 'a', 0x00),
                          MEMBER(Char[7], 's', 0x00),
                          MEMBER(Char[8], 's', 0x00)))
};
//==============================================================================================================================================================
static __code const unsigned char _USB_StringDescriptor_SerialNumber_Data[] = {
  SVALUE(USBD_DESCRIPTOR_TypeDef,
              MEMBER(bLength, 10),
              MEMBER(bDescriptorType, USB_DEVICE_STANDARD_DESCRIPTOR_STRING),
              SVALUE(STRING,
                          MEMBER(Char[0], 'F', 0x00),
                          MEMBER(Char[1], 'F', 0x00),
                          MEMBER(Char[2], 'F', 0x00),
                          MEMBER(Char[3], 'F', 0x00)))
};
//==============================================================================================================================================================
//config[0] -> interface[0] -> endpoint
static __code const USBDescriptor_TypeDef _USB_EndpointDescriptor[] = {
  {.Data = _USB_ConfigurationDescription_Data + 9 + 9, .Length = 7, .Child = NULL},
  {.Data = _USB_ConfigurationDescription_Data + 9 + 9 + 7, .Length = 7, .Child = NULL},
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
//======================================================================================================================
__code const USBDescriptors_TypeDef USBDescriptors = {
  .Device = {.Data = _USB_DeviceDescriptor_Data, .Length = sizeof(_USB_DeviceDescriptor_Data)},
  .Configuration = {.Number = sizeof(_USB_ConfigurationDescriptor) / sizeof(USBDescriptor_TypeDef), .Descriptors = _USB_ConfigurationDescriptor},
  .String = {.Number = sizeof(_USB_StringDescriptor) / sizeof(USBDescriptor_TypeDef), .Descriptors = _USB_StringDescriptor},
  .Class = NULL,
};