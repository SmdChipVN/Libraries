#include <USBP.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
__no_init USBManager_TypeDef USBManager;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_Init(USBEndpointBuffer_TypeDef* USBEndpointBuffer)
{
#ifndef USBP_BY_INTERRUPT
  USBManager.Status = USBP_STATUS_NONE;
#endif
  USBManager.Address.REG = 0;
  USBManager.EndpointBuffer = USBEndpointBuffer;
  USBManager.Event.REG = 0;
  USBManager.PlugState = 0;
  //USBManager.ConfigIndex = 0;
  //USBManager.InterfaceIndex = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_Process()
{
#ifndef USBP_BY_INTERRUPT
  reg8 endpoint_index = USBManager.EndpointRequest;
  if (USBManager.Status == USBP_STATUS_SETUP)                                                                   //PID_SETUP, only for endpoint 0 (endpoint_index = 0, control transfer)
  {
    USBH_SETUP_TypeDef* Setup = (USBH_SETUP_TypeDef*)(USBManager.EndpointBuffer[endpoint_index].RXData);        
    switch (Setup->bmRequestType.BITS.Recipient)
    {
      case USB_RECIPIENT_DEVICE: USBP_DeviceSetup_Process(Setup); break;
      case USB_RECIPIENT_INTERFACE: USBP_InterfaceSetup_Process(Setup); break;
      case USB_RECIPIENT_ENDPOINT: USBP_EndpointSetup_Process(Setup); break;
      default: USBP_UserSetup_Process(Setup);                                                                   //User define
    }
    USBManager.Status = USBP_STATUS_NONE;
  }
  else if (USBManager.Status == USBP_STATUS_DATA_OUT)                                                           //PID_OUT
  {
    if (USBP_Received(endpoint_index, USBManager.EndpointBuffer[endpoint_index].RXData, USBManager.EndpointBuffer[endpoint_index].RXLength))
      USBP_ConfigEndpoint(endpoint_index, USB_ENDPOINT_STATUS_NAK, USB_ENDPOINT_STATUS_VALID);
    USBManager.Status = USBP_STATUS_NONE;
  }
  else if (USBManager.Status == USBP_STATUS_DATA_IN)
  {
    if (USBManager.EndpointBuffer[endpoint_index].TXLength)
      USBP_Send(endpoint_index, USBManager.EndpointBuffer[endpoint_index].TXData, USBManager.EndpointBuffer[endpoint_index].TXLength);
    else if (USBP_PIDIn(endpoint_index))
    {
      if (USBManager.EndpointBuffer[endpoint_index].TXData)
        USBP_Send(endpoint_index, NULL, 0);
    }
    USBManager.Status = USBP_STATUS_NONE;
  }
#endif
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_DeviceSetup_Process(USBH_SETUP_TypeDef* Setup)
{
  switch (Setup->bmRequestType.BITS.Type)
  {
    case USB_REQUEST_TYPE_STANDARD:
      switch (Setup->Device.Standard.bRequest)
      {
//        case USB_DEVICE_STANDARD_REQUEST_GET_STATUS:                          //Self Powered: bit 0, Remote Wakeup: bit 1 (have not met)
//          USB_Send(0, "\0\0", 2); break;
//        case USB_DEVICE_STANDARD_REQUEST_CLEAR_FEATURE: break;                //not support
//        case USB_DEVICE_STANDARD_REQUEST_SET_FEATURE: break;                  //not support
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_DEVICE_STANDARD_REQUEST_SET_ADDRESS:
          USBManager.Address.REG = BIT7 | Setup->Device.Standard.SET_ADDRESS.Address;
          USBP_Send(0, NULL, 0); break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_DEVICE_STANDARD_REQUEST_GET_DESCRIPTOR:
          switch (Setup->Device.Standard.GET_DESCRIPTOR.Type)
          {
            case USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE:
              USBP_Send(0, USBDescriptors.Device.Data, USBDescriptors.Device.Length); break;
            //--------------------------------------------------------------------------------------------------------------------------------------------------
            case USB_DEVICE_STANDARD_DESCRIPTOR_CONFIGURATION:
            case USB_DEVICE_STANDARD_DESCRIPTOR_STRING:
              {
                const struct
                {
                  const unsigned char Number;
                  const USBDescriptor_TypeDef __code* Data;
                } __code* pointer;
                reg16 length = Setup->Device.Standard.GET_DESCRIPTOR.MaxLength;
                reg8 index = Setup->Device.Standard.GET_DESCRIPTOR.Index;
                if (Setup->Device.Standard.GET_DESCRIPTOR.Type == USB_DEVICE_STANDARD_DESCRIPTOR_CONFIGURATION)
                  pointer = (void __code*)&USBDescriptors.Configuration;
                else
                  pointer = (void __code*)&USBDescriptors.String;
                if (index < pointer->Number)
                {
                  if (length > pointer->Data[index].Length)
                    length = pointer->Data[index].Length;
                  USBP_Send(0, pointer->Data[index].Data, length);
                }
                else
                {
                  USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_STALL, USB_ENDPOINT_STATUS_NAK);
                }
              } break;
            //--------------------------------------------------------------------------------------------------------------------------------------------------
//            case USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE: break;             //cannot be accessed directly by a GetDescriptor/SetDescriptor Request
//            case USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT: break;              //cannot be accessed directly by a GetDescriptor/SetDescriptor Request
//            case USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE_QUALIFIER: break;      //only for support both full and high speed, if not, stall
//            case USB_DEVICE_STANDARD_DESCRIPTOR_OTHER_SPEED: break;           //only for support both full and high speed, if not, stall
//            case USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE_POWER: break;       //It was proposed by Microsoft 1998 but hasn’t been implemented
//            case USB_DEVICE_STANDARD_DESCRIPTOR_OTG: break;                   //required for devices that support OTG Host Negotiation Protocol (HNP) or Session Request Protocol             
            //--------------------------------------------------------------------------------------------------------------------------------------------------
            default:
              USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_STALL, USB_ENDPOINT_STATUS_NAK);
          }
          break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
//        case USB_DEVICE_STANDARD_REQUEST_SET_DESCRIPTOR: break;               //is forbidden
//        case USB_DEVICE_STANDARD_REQUEST_GET_CONFIGURATION:                   //have not met
//          USB_Send(0, &USBManager.ConfigIndex, 1); break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        case USB_DEVICE_STANDARD_REQUEST_SET_CONFIGURATION:
          //USBManager.ConfigIndex = Setup->Device.Standard.SET_CONFIGURATION.Configuration;
          USBP_Send(0, NULL, 0);
          break;
        //------------------------------------------------------------------------------------------------------------------------------------------------------
        default:
          USBP_ConfigEndpoint(0, USB_ENDPOINT_STATUS_STALL, USB_ENDPOINT_STATUS_NAK);
      }
      break;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
//    case USB_REQUEST_TYPE_CLASS:
//      break;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
//    case USB_REQUEST_TYPE_VENDER:
//      break;
  }
}