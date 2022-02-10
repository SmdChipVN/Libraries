#include <USB_HID.h>

__no_init USB_HID_Manager_TypeDef USB_HID_Manager;
//==============================================================================================================================================================
void USB_HID_Init(unsigned char* RxBuffer)
{
  USB_HID_Manager.RxBuffer = RxBuffer;
  USB_HID_Manager.RxIndex = 0;
  USB_HID_Manager.RxSize = 0;
  USB_HID_Manager.Request = USB_HID_REQUEST_NULL;
  USB_HID_Manager.TxPointer = NULL;
  USB_HID_Manager.TxSize = 0;
}
//==============================================================================================================================================================
void USBP_InterfaceSetup_Process(USBH_SETUP_TypeDef* Setup)
{
  USB_HID_Descriptors_TypeDef __code* hid_des;
  USB_HID_REQUEST_TypeDef* Setup_HID = (USB_HID_REQUEST_TypeDef*)Setup;
  switch (Setup_HID->bmRequestType.BITS.Type)
  {
    case USB_REQUEST_TYPE_STANDARD:
      switch (Setup_HID->Standard.bRequest)
      {
        case USB_HID_INTERFACE_STANDARD_REQUEST_GET_DESCRIPTOR:
          hid_des = (USB_HID_Descriptors_TypeDef __code*)USBDescriptors.Class;
          switch (Setup_HID->Standard.GET_DESCRIPTOR.Type)
          {
//            case USB_HID_DESCRIPTOR_PHYSICAL: break;                                                                  //not have
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
            case USB_HID_DESCRIPTOR_HID:
              USBP_Send(0, hid_des->HID.Data, hid_des->HID.Length); break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
            case USB_HID_DESCRIPTOR_REPORT:
              USBP_Send(0, hid_des->Report.Data, hid_des->Report.Length); break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
            default:
              USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_STALL, USB_ENDPOINT_STATUS_VALID);
          } break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//        case USB_HID_INTERFACE_STANDARD_REQUEST_SET_DESCRIPTOR  : break;                                              //have not met
      }
      break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
    case USB_REQUEST_TYPE_CLASS:
      switch (Setup_HID->Class.bRequest)
      {
//        case USB_HID_INTERFACE_CLASS_REQUEST_GET_PROTOCOL: break;                                                     //have not met
//        case USB_HID_INTERFACE_CLASS_REQUEST_SET_PROTOCOL: break;                                                     //have not met
//        case USB_HID_INTERFACE_CLASS_REQUEST_GET_IDLE: break;                                                         //have not met
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_HID_INTERFACE_CLASS_REQUEST_GET_REPORT:
          USB_HID_Manager.Request = USB_HID_REQUEST_DATA_OUT;
          if (USB_HID_Manager.TxPointer)
            USBP_Send(0, USB_HID_Manager.TxPointer, Setup_HID->Class.GET_REPORT.Length > USB_HID_Manager.TxSize ? 
                     USB_HID_Manager.TxSize : Setup_HID->Class.GET_REPORT.Length);
          else
            USBP_Send(0, NULL, 0);
          break;
        case USB_HID_INTERFACE_CLASS_REQUEST_SET_REPORT:
          //xx = 1;
          //USBP_ConfigDataPoint(0, 2, 0);
          USB_HID_Manager.Request = USB_HID_REQUEST_DATA_IN;
          USB_HID_Manager.RxIndex = 0;
          USB_HID_Manager.RxSize = Setup_HID->Class.SET_REPORT.Length;
          USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_NAK, USB_ENDPOINT_STATUS_VALID);
            break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_HID_INTERFACE_CLASS_REQUEST_SET_IDLE:
          USBP_Send(0, NULL, 0); break;
      }
      break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
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
  if (EndpointIndex)
    return USB_HID_Received(EndpointIndex, Data, Length);
  else
  {
    if (USB_HID_Manager.Request == USB_HID_REQUEST_DATA_IN)
    {
      reg16 j = USB_HID_Manager.RxIndex;
      for (reg16 i = 0; i < Length && j < USB_HID_Manager.RxSize; i++, j++)
        USB_HID_Manager.RxBuffer[j] = Data[i];
      if (j == USB_HID_Manager.RxSize)
      {
        USB_HID_Manager.Request = USB_HID_REQUEST_NULL;
        USBP_Send(0, NULL, 0);
        USB_HID_Received(0, USB_HID_Manager.RxBuffer, USB_HID_Manager.RxSize);
        return 0;
      }
      else
        USB_HID_Manager.RxIndex = j;
    }
    else if (USB_HID_Manager.Request == USB_HID_REQUEST_DATA_OUT && Length == 0)
    {
      USB_HID_Manager.Request = USB_HID_REQUEST_NULL;
      USB_HID_Manager.TxPointer = NULL;
    }
  }
  return 1;
}
//==============================================================================================================================================================
reg8 USBP_PIDIn(reg8 EndpointIndex)
{
  return 1;
}
//==============================================================================================================================================================
void USBP_OpenAnotherEndpoint()
{
  USBP_OpenEndpoint(1, (USBEndpoint_TypeDef){
    .Address = 1,
    .Type = USB_ENDPOINT_TYPE_INTERRUPT,
    .TX = {.Status = USB_ENDPOINT_STATUS_NAK, .DataID = 0},
    .RX = {.Status = USB_ENDPOINT_STATUS_VALID, .DataID = 0},
  });
}