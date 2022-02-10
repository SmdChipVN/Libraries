#include <common.h>
#include <bitband.h>
#include <usb.h>
#include <USBP.h>

#define USB_HW_ENDPOINT_TYPE_BULK               0
#define USB_HW_ENDPOINT_TYPE_CONTROL            1
#define USB_HW_ENDPOINT_TYPE_ISO                2
#define USB_HW_ENDPOINT_TYPE_INTERRUPT          3

#define USB_HW_ENDPOINT_STATUS_DISABLED         0
#define USB_HW_ENDPOINT_STATUS_STALL            1
#define USB_HW_ENDPOINT_STATUS_NAK              2
#define USB_HW_ENDPOINT_STATUS_VALID            3
//==============================================================================================================================================================
typedef BUNION(HWEndpoint_TypeDef, unsigned int,
  EA                                  , 4,    //0:3           0               Endpoint address
  STAT_TX                             , 2,    //4:5           0               Status bits, for transmission transfers
  DTOG_TX                             , 1,    //6             0               Data Toggle, for transmission transfers
  CTR_TX                              , 1,    //7             0               Correct Transfer for transmission
  EP_KIND                             , 1,    //8             0               Endpoint kind
  EP_TYPE                             , 2,    //9:10          0               Endpoint type
  const SETUP                         , 1,    //11            0               Setup transaction completed
  STAT_RX                             , 2,    //12:13         0               Status bits, for reception transfers
  DTOG_RX                             , 1,    //14            0               Data Toggle, for reception transfers
  CTR_RX                              , 1,    //15            0               Correct Transfer for reception
  _reserved                           , 16);
//==============================================================================================================================================================
static void _ConfigEndpoint(unsigned int EndpointIndex, HWEndpoint_TypeDef NewValue);
static unsigned int _GetEndpointRX(unsigned int EndpointIndex);
static void _SetEndpointTX(unsigned int EndpointIndex, const unsigned char* Data, unsigned int Length);
//==============================================================================================================================================================
static void _OpenEndpoint(unsigned int EndpointIndex, HWEndpoint_TypeDef Value)
{
  volatile unsigned int* reg = &USB.Endpoint[EndpointIndex].REG;
  HWEndpoint_TypeDef old_value;
  old_value.REG = *reg;
  old_value.REG &= (Value.REG & (BIT15 | BIT7)) | (~(BIT15 | BIT7));                    //CTR_TX & CTR_RX: clear by write 0, write 1 is no effect
  old_value.REG &= ~(BIT10 | BIT9 | BIT8 | BIT3 | BIT2 | BIT1 | BIT0);
  old_value.REG |= Value.REG & (BIT10 | BIT9 | BIT8 | BIT3 | BIT2 | BIT1 | BIT0);       //EP_TYPE, EP_KIND, EA read&write
  old_value.REG ^= Value.REG & (BIT14 | BIT13 | BIT12 | BIT6 | BIT5 | BIT4);            //DTOG_RX, STAT_RX, DTOG_TX, STAT_TX write 1 is toggle
  *reg = old_value.REG;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void _ConfigEndpoint(unsigned int EndpointIndex, HWEndpoint_TypeDef NewValue)
{
  HWEndpoint_TypeDef old_value;
  volatile unsigned int* reg = &USB.Endpoint[EndpointIndex].REG;
  old_value.REG = *reg;
  old_value.REG &= (NewValue.REG & (BIT15 | BIT7)) | (~(BIT15 | BIT7));                 //CTR_TX & CTR_RX: clear by write 0, write 1 is no effect
  old_value.REG &= ~(BIT14 | BIT6);                                                     //DTOG_RX, DTOG_TX write 1 is toggle (not change)
  old_value.REG ^= NewValue.REG & (BIT13 | BIT12 | BIT5 | BIT4);                        //STAT_RX, STAT_TX write 1 is toggle
  *reg = old_value.REG;
}
//==============================================================================================================================================================
static unsigned int _GetEndpointRX(unsigned int EndpointIndex)
{
  unsigned int OutLength = (((USBEndpoint_ADDR_TypeDef*)0x40006000)[EndpointIndex]).RX.COUNT[0].BITS.VALUE;
  unsigned int* rx_pointer = (unsigned int*)(0x40006000 + (((USBEndpoint_ADDR_TypeDef*)0x40006000)[EndpointIndex]).RX.ADDR[0] * 2);
  for (unsigned int i = 0; i < ((OutLength + (OutLength & 1)) / 2); i++)
    ((unsigned short*)USBManager.EndpointBuffer[EndpointIndex].RXData)[i] = rx_pointer[i];
  return OutLength;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static void _SetEndpointTX(unsigned int EndpointIndex, const unsigned char* Data, unsigned int Length)
{
  unsigned int* tx_pointer = (unsigned int*)(0x40006000 + (((USBEndpoint_ADDR_TypeDef*)0x40006000)[EndpointIndex]).TX.ADDR[0] * 2);
  for (unsigned int i = 0; i < ((Length + (Length & 1)) / 2); i++)
    tx_pointer[i] = ((const unsigned short*)Data)[i];
  (((USBEndpoint_ADDR_TypeDef*)0x40006000)[EndpointIndex]).TX.COUNT[0] = Length;
}
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
void USB_LP_CAN1_RX0_IRQHandler()
{
  GPIOB_BITBAND.ODR.b7 = 1;
  if (USB_BITBAND.ISTR.CTR)                                                                                             //Correct transfer
  {
    unsigned int endpoint_index = USB.ISTR.BITS.EP_ID;
#ifndef USBP_BY_INTERRUPT       ///USBP_BY_INTERRUPT
    USBManager.EndpointRequest = endpoint_index;
    if (USB_BITBAND.ISTR.DIR)                                                                                           //Host -> Device (PID_SETUP / PID_OUT)
    {
      _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
        .BITS = {
          .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_TX      = 0,
          .STAT_RX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_RX      = 0,
        }});
      USBManager.EndpointBuffer[endpoint_index].RXLength = _GetEndpointRX(endpoint_index);
      if (USB_BITBAND.Endpoint[endpoint_index].SETUP)                                                                   //PID_SETUP, only for endpoint 0 (endpoint_index = 0, control transfer)
        USBManager.Status = USBP_STATUS_SETUP;
      else
        USBManager.Status = USBP_STATUS_DATA_OUT;
    }
    else                                                                                                                //Device -> Host (PID_IN)
    {
      _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
        .BITS = {
          .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_TX      = 0,
          .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
          .CTR_RX      = 1,
        }});
      if (USBManager.Address.BITS.Setting)
      {
        USB.DADDR.REG = BIT7 | USBManager.Address.BITS.Value;
        USBManager.Address.BITS.Setting = 0;
      }
      else USBManager.Status = USBP_STATUS_DATA_IN;
    }
#else                           ///USBP_BY_INTERRUPT
    if (USB_BITBAND.ISTR.DIR)                                                                                           //Host -> Device (PID_SETUP / PID_OUT)
    {
      _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
        .BITS = {
          .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_TX      = 0,
          .STAT_RX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_RX      = 0,
        }});
      USBManager.EndpointBuffer[endpoint_index].RXLength = _GetEndpointRX(endpoint_index);      
      if (USB_BITBAND.Endpoint[endpoint_index].SETUP)                                                                   //PID_SETUP, only for endpoint 0 (endpoint_index = 0, control transfer)
      {
        USBH_SETUP_TypeDef* Setup = (USBH_SETUP_TypeDef*)(USBManager.EndpointBuffer[endpoint_index].RXData);        
        switch (Setup->bmRequestType.BITS.Recipient)
        {
          case USB_RECIPIENT_DEVICE: USBP_DeviceSetup_Process(Setup); break;
          case USB_RECIPIENT_INTERFACE: USBP_InterfaceSetup_Process(Setup); break;
          case USB_RECIPIENT_ENDPOINT: USBP_EndpointSetup_Process(Setup); break;
          default: USBP_UserSetup_Process(Setup);                                                                       //User define
        }
      }
      else                                                                                                              //PID_OUT
      {
        if (USBP_Received(endpoint_index, USBManager.EndpointBuffer[endpoint_index].RXData, USBManager.EndpointBuffer[endpoint_index].RXLength))
        {
          _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
            .BITS = {
              .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
              .CTR_TX      = 0,
              .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
              .CTR_RX      = 1,
            }});
        }
      }
    }
    else                                                                                                                //Device -> Host (PID_IN)
    {
      _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
        .BITS = {
          .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
          .CTR_TX      = 0,
          .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
          .CTR_RX      = 1,
        }});
      if (USBManager.Address.BITS.Setting)
      {
        USB.DADDR.REG = BIT7 | USBManager.Address.BITS.Value;
        USBManager.Address.BITS.Setting = 0;
      }
      else if (USBManager.EndpointBuffer[endpoint_index].TXLength)
        USBP_Send(endpoint_index, USBManager.EndpointBuffer[endpoint_index].TXData, USBManager.EndpointBuffer[endpoint_index].TXLength);
      else if (USBP_PIDIn(endpoint_index))
      {
        if (USBManager.EndpointBuffer[endpoint_index].TXData)
          USBP_Send(endpoint_index, NULL, 0);
        else if (!((USBEndpoint_ADDR_TypeDef*)0x40006000)[endpoint_index].TX.COUNT[0])
        {
          _ConfigEndpoint(endpoint_index, (HWEndpoint_TypeDef){
            .BITS = {
              .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
              .CTR_TX      = 0,
              .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
              .CTR_RX      = 1,
            }});
        }
      }
    }
#endif                          ///USBP_BY_INTERRUPT
  }
  if (USB_BITBAND.ISTR.RESET)                                                                                          //USB reset request
  {
    USBManager.Event.BITS.ChangePlug = 1;
    USBManager.PlugState = 1;
    USB_BITBAND.ISTR.RESET = 0;
    //open endpoint 0 (require)
    _OpenEndpoint(0, (HWEndpoint_TypeDef){
      .BITS = {
        .EA          = 0,
        .STAT_TX     = USB_HW_ENDPOINT_STATUS_NAK,
        .DTOG_TX     = 1,
        .CTR_TX      = 0,
        .EP_KIND     = 0,
        .EP_TYPE     = USB_HW_ENDPOINT_TYPE_CONTROL,
        .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
        .DTOG_RX     = 0,
        .CTR_RX      = 1,
      }});
    //open another endpoint
    USBP_OpenAnotherEndpoint();
    //set address = 0
    USB.DADDR.REG = BIT7;
  }
//  if (USB_BITBAND.ISTR.PMAOVR)                                                                                       //Packet memory area over / underrun (sure never)
//  {
//    USB_BITBAND.ISTR.PMAOVR = 0;
//  }
//  if (USB_BITBAND.ISTR.ERR)                                                                                          //Error (sure never)
//  {
//    USB_BITBAND.ISTR.ERR = 0;
//  }
  if (USB_BITBAND.ISTR.WKUP)                                                                                           //Wakeup
  {
    USB_BITBAND.CNTR.FSUSP = 0;
    USB_BITBAND.ISTR.WKUP = 0;
  }
  if (USB_BITBAND.ISTR.SUSP)                                                                                           //Suspend mode request
  {
    unsigned short endpoint_buff[2];
    for (unsigned int i = 0; i < 2; i++)
      endpoint_buff[i] = USB.Endpoint[i].REG;    
    USB_BITBAND.CNTR.FRES = 1;
    USB_BITBAND.CNTR.FRES = 0;
    while (!USB_BITBAND.ISTR.RESET);
    USB_BITBAND.ISTR.RESET = 0;
    for (unsigned int i = 0; i < 2; i++)
      USB.Endpoint[i].REG = endpoint_buff[i];
    USB_BITBAND.CNTR.FSUSP = 1;
    USB_BITBAND.ISTR.SUSP = 0;
    
    USBManager.Event.BITS.ChangePlug = 1;
    USBManager.PlugState = 0;
  }
//  if (USB_BITBAND.ISTR.SOF)                                                                                            //Start of frame
//  {
//    USB_BITBAND.ISTR.SOF = 0;
//  }
//  if (USB_BITBAND.ISTR.ESOF)                                                                                           //Expected start of frame
//  {
//    USB_BITBAND.ISTR.ESOF = 0;
//  }
  GPIOB_BITBAND.ODR.b7 = 0;
}
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
void USB_Init(const USBEndpointAddress_TypeDef* USBEndPointAddress)
{
  USB.CNTR.REG = 1;
  USB.CNTR.REG = 0;
  USB.ISTR.REG = 0;
  //USB.CNTR.REG = BIT15 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8;
  USB.CNTR.REG = BIT15 | BIT12 | BIT11 | BIT10;
  for (unsigned int i = 0; i < 2; i++)
  {
    (((USBEndpoint_ADDR_TypeDef*)0x40006000)[i]).TX.ADDR[0] = USBEndPointAddress[i].TX;
    (((USBEndpoint_ADDR_TypeDef*)0x40006000)[i]).RX.ADDR[0] = USBEndPointAddress[i].RX;
    (((USBEndpoint_ADDR_TypeDef*)0x40006000)[i]).RX.COUNT[0].REG = BIT15 | BIT10;
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_Send(reg8 EnpointIndex, const unsigned char __gptr* Data, reg16 Length)
{
  if (Length >= 64)
  {
    USBManager.EndpointBuffer[EnpointIndex].TXData = &Data[64];
    USBManager.EndpointBuffer[EnpointIndex].TXLength = Length - 64;
    Length = 64;
  }
  else
  {
    if (Length != 64)
      USBManager.EndpointBuffer[EnpointIndex].TXData = NULL;
    USBManager.EndpointBuffer[EnpointIndex].TXLength = 0;
  }
  _SetEndpointTX(EnpointIndex, Data, Length);
  _ConfigEndpoint(EnpointIndex, (HWEndpoint_TypeDef){
    .BITS = {
      .STAT_TX     = USB_HW_ENDPOINT_STATUS_VALID,
      .CTR_TX      = 1,
      .STAT_RX     = USB_HW_ENDPOINT_STATUS_VALID,
      .CTR_RX      = 1,
    }});
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static const unsigned short convert_tx_status[] = {USB_HW_ENDPOINT_STATUS_DISABLED << 4, USB_HW_ENDPOINT_STATUS_STALL << 4, USB_HW_ENDPOINT_STATUS_NAK << 4, USB_HW_ENDPOINT_STATUS_VALID << 4};
static const unsigned short convert_rx_status[] = {USB_HW_ENDPOINT_STATUS_DISABLED << 12, USB_HW_ENDPOINT_STATUS_STALL << 12, USB_HW_ENDPOINT_STATUS_NAK << 12, USB_HW_ENDPOINT_STATUS_VALID << 12};
static const unsigned short convert_type[] = {USB_HW_ENDPOINT_TYPE_CONTROL << 9, USB_HW_ENDPOINT_TYPE_ISO << 9, USB_HW_ENDPOINT_TYPE_BULK << 9, USB_HW_ENDPOINT_TYPE_INTERRUPT << 9};
void USBP_OpenEndpoint(reg8 EndpointIndex, USBEndpoint_TypeDef Value)
{
  HWEndpoint_TypeDef hw_endpoint;
  hw_endpoint.REG = Value.Address | convert_tx_status[Value.TX.Status] |
    BIT7 | convert_type[Value.Type] | convert_rx_status[Value.RX.Status] | BIT15;
  hw_endpoint.REG |= (Value.TX.DataID << 6) | (Value.RX.DataID << 14);
  _OpenEndpoint(EndpointIndex, hw_endpoint);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_ConfigDataPoint(reg8 EndpointIndex, reg8 TXDataID, reg8 RXDataID)
{
  HWEndpoint_TypeDef old_value;
  volatile unsigned int* reg = &USB.Endpoint[EndpointIndex].REG;
  old_value.REG = *reg;
  old_value.REG &= ~(BIT13 | BIT12 | BIT5 | BIT4);                                      //STAT_RX, STAT_TX write 1 is toggle (not change)
  if (TXDataID > 1)
    old_value.BITS.DTOG_TX = TXDataID - 2;
  else
    old_value.REG ^= (TXDataID << 6);
  if (RXDataID > 1)
    old_value.BITS.DTOG_RX = RXDataID - 2;
  else
    old_value.REG ^= (RXDataID << 14);
  *reg = old_value.REG;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void USBP_ConfigEndpoint(reg8 EndpointIndex, USB_ENDPOINT_STATUS TXStatus, USB_ENDPOINT_STATUS RXStatus)
{
  HWEndpoint_TypeDef old_value;
  volatile unsigned int* reg = &USB.Endpoint[EndpointIndex].REG;
  old_value.REG = *reg;
  old_value.REG &= ~(BIT14 | BIT6);                                                     //DTOG_RX, DTOG_TX write 1 is toggle (not change)
  old_value.REG ^= convert_tx_status[TXStatus] | convert_rx_status[RXStatus];
  *reg = old_value.REG;
}