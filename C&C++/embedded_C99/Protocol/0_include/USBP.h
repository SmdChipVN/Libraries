#ifndef _USB_PROTOCOL_H_
#define _USB_PROTOCOL_H_

#include <USBP_TYPEDEF.h>
#include <config.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
extern const __code USBDescriptors_TypeDef USBDescriptors;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned short RXLength;
  unsigned short TXLength;
  unsigned char* RXData;
  const unsigned char __gptr* TXData;
} USBEndpointBuffer_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
#ifndef USBP_BY_INTERRUPT
  enum
  {
    USBP_STATUS_NONE            = 0,
    USBP_STATUS_SETUP           = 1,
    USBP_STATUS_DATA_OUT        = 2,
    USBP_STATUS_DATA_IN         = 3,
  } Status;
  unsigned char EndpointRequest;
#endif
  BUNION(Address, unsigned char,
    Value           , 7,
    Setting         , 1);
  BUNION(Event, unsigned char,
    ChangePlug                          , 1,
    _reserved                           , 7);
  unsigned char PlugState;
  //unsigned char ConfigIndex;
  //unsigned char InterfaceIndex;
  USBEndpointBuffer_TypeDef* EndpointBuffer;
} USBManager_TypeDef;
extern __no_init USBManager_TypeDef USBManager;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//need to be declare by hardware
void USBP_OpenEndpoint(reg8 EndpointIndex, USBEndpoint_TypeDef Value);
void USBP_ConfigEndpoint(reg8 EndpointIndex, USB_ENDPOINT_STATUS TXStatus, USB_ENDPOINT_STATUS RXStatus);
void USBP_ConfigDataPoint(reg8 EndpointIndex, reg8 TXDataID, reg8 RXDataID);            //0 or 1: force, 2: un-change, 3-toggle
void USBP_Send(reg8 EnpointIndex, const unsigned char __gptr* Data, reg16 Length);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//publish function
void USBP_Init(USBEndpointBuffer_TypeDef* USBEndpointBuffer);                           //for init variables of USBManager
void USBP_DeviceSetup_Process(USBH_SETUP_TypeDef* Setup);                               //for interview stages
void USBP_Process();                                                                    //only for process event without interrupt (#ifndef USBP_BY_INTERRUPT)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//need to be declare by class, refer USB_HID.c or another
void USBP_InterfaceSetup_Process(USBH_SETUP_TypeDef* Setup);
void USBP_EndpointSetup_Process(USBH_SETUP_TypeDef* Setup);
void USBP_UserSetup_Process(USBH_SETUP_TypeDef* Setup);
reg8 USBP_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length);
reg8 USBP_PIDIn(reg8 EndpointIndex);
void USBP_OpenAnotherEndpoint();

#endif