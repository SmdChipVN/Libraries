#include <USB_CDC.h>
//==============================================================================================================================================================
__no_init USB_CDC_Manager_TypeDef USB_CDC_Manager;
//==============================================================================================================================================================
void USB_CDC_Init()
{
  USB_CDC_Manager.Request = USB_CDC_REQUEST_NULL;
  USB_CDC_Manager.Event.REG = 0;
  USB_CDC_Manager.Info.bDataBits = 8;
  USB_CDC_Manager.Info.bParityType = USB_CDC_PARITY_TYPE_NONE;
  USB_CDC_Manager.Info.bStopBits = USB_CDC_STOP_BITS_1;
  USB_CDC_Manager.Info.dwDTERate = 9600;
}
//==============================================================================================================================================================
void USBP_InterfaceSetup_Process(USBH_SETUP_TypeDef* Setup)
{
  USB_CDC_REQUEST_TypeDef* Setup_CDC = (USB_CDC_REQUEST_TypeDef*)Setup;
  switch (Setup_CDC->bmRequestType.BITS.Type)
  {
    case USB_REQUEST_TYPE_CLASS:
      switch (Setup_CDC->Class.bRequest)
      {
        case USB_CDC_INTERFACE_CLASS_REQUEST_SET_LINE_CODING:
          USB_CDC_Manager.Request = USB_CDC_REQUEST_SET_LINE_CODING;
          USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_NAK, USB_ENDPOINT_STATUS_VALID);
          break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_CDC_INTERFACE_CLASS_REQUEST_GET_LINE_CODING:
          USBP_Send(0, (const unsigned char*)&USB_CDC_Manager.Info, 7); break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_CDC_INTERFACE_CLASS_REQUEST_SET_CONTROL_LINE_STATE:
          {
            reg8 new_state = Setup_CDC->Class.SET_CONTROL_LINE_STATE.CSB.BITS.DTE;
            if (new_state != USB_CDC_Manager.PortState)
            {
              USB_CDC_Manager.PortState = new_state;
              USB_CDC_Manager.Event.BITS.ChangeState = 1;
            }
          }
          USBP_Send(0, NULL, 0); break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
//        default:
//          USB_ConfigEndpointByIndex(0, (USBEndpoint_TypeDef){
//            .TX = {.Status = USB_ENDPOINT_STATUS_STALL},
//            .RX = {.Status = USB_ENDPOINT_STATUS_NAK},
//            });
//          break;
      }
      break;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//    case USB_REQUEST_TYPE_VENDER:
//      break;
  }
}
//==============================================================================================================================================================
void USBP_EndpointSetup_Process(USBH_SETUP_TypeDef* Setup)
{
//  switch (Setup_CDC->bmRequestType.BITS.Type)
//  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//    case USB_REQUEST_TYPE_CLASS:
//      break;
//    case USB_REQUEST_TYPE_VENDER:
//      break;
//  }
}
//==============================================================================================================================================================
void USBP_UserSetup_Process(USBH_SETUP_TypeDef* Setup)
{
//  switch (Setup_CDC->bmRequestType.BITS.Type)
//  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//    case USB_REQUEST_TYPE_CLASS:
//      break;
//    case USB_REQUEST_TYPE_VENDER:
//      break;
//  }
}
//==============================================================================================================================================================
reg8 USBP_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length)
{
  if (USB_CDC_Manager.Request == USB_CDC_REQUEST_SET_LINE_CODING)
  {
    USB_CDC_Manager.Request = USB_CDC_REQUEST_NULL;
    *((unsigned long*)&USB_CDC_Manager.Info) = *((unsigned long*)Data);
    *((unsigned short*)&USB_CDC_Manager.Info.bStopBits) = *((unsigned long*)&Data[4]);
    USB_CDC_Manager.Info.bDataBits = Data[6];
    USBP_Send(0, NULL, 0);
    USB_CDC_Manager.Event.BITS.ChangeInfo = 1;
    return 0;
  }
  else
    return USB_CDC_Received(EndpointIndex, Data, Length);
}
//==============================================================================================================================================================
reg8 USBP_PIDIn(reg8 EndpointIndex)
{
  return 1;
}
//==============================================================================================================================================================
void USBP_OpenAnotherEndpoint()
{
  USBP_OpenEndpoint(2, (USBEndpoint_TypeDef){
    .Address = 2,
    .Type = USB_ENDPOINT_TYPE_INTERRUPT,
    .TX = {.Status = USB_ENDPOINT_STATUS_NAK, .DataID = 0},
    .RX = {.Status = USB_ENDPOINT_STATUS_VALID, .DataID = 0},
  });
  USBP_OpenEndpoint(1, (USBEndpoint_TypeDef){
    .Address = 1,
    .Type = USB_ENDPOINT_TYPE_BULK,
    .TX = {.Status = USB_ENDPOINT_STATUS_NAK, .DataID = 0},
    .RX = {.Status = USB_ENDPOINT_STATUS_VALID, .DataID = 0},
  });
}