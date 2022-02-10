#include <USB_MASS.h>
#include <USB_MASS_SCSI.h>
//==============================================================================================================================================================
__no_init USB_MASS_Manager_TypeDef USB_MASS_Manager;
//==============================================================================================================================================================
void USB_MASS_Init(void)
{
  USB_MASS_Manager.State = USB_MASS_STATE_READY;
  USB_MASS_Manager.bCSWStatus = 0x00;
}
//==============================================================================================================================================================
void USBP_InterfaceSetup_Process(USBH_SETUP_TypeDef* Setup)
{
  USB_MASS_REQUEST_TypeDef* Setup_MASS = (USB_MASS_REQUEST_TypeDef*)Setup;
  switch (Setup_MASS->bmRequestType.BITS.Type)
  {
//    case USB_REQUEST_TYPE_STANDARD:
//      break;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
    case USB_REQUEST_TYPE_CLASS:
      switch (Setup_MASS->Class.bRequest)
      {
        case USB_MASS_INTERFACE_CLASS_REQUEST_GET_MAX_LUN:
          USB_MASS_Manager.State = USB_MASS_STATE_READY;
          USBP_Send(0, "\0", 1);
          break;
        case USB_MASS_INTERFACE_CLASS_REQUEST_RESET:
          USBP_Send(0, NULL, 0);
          break;
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
static const unsigned char Inquiry_Data[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (0x24 - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};
static const unsigned char Capacity_Data[] = 
{
  0x00, 0x00, 0x0F, 0xFF,               //last block address
  0x00, 0x00, 0x02, 0x00,               //block size in bytes
};
static const unsigned char FormatCapacities_Data[] = 
{
  0x00, 0x00, 0x00, 8,
  0x00, 0x00, 0x0F, 0xFF,
  0x02,
  0x00, 0x02, 0x00,
};
static unsigned char buffer[512];
#include <flashIC.h>
reg8 USBP_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length)
{
  static unsigned int write_buffer_index = 0;
  if (EndpointIndex)
  {
    if (USB_MASS_Manager.State)         //received data after command write
    {
      static unsigned char buff[4096];
      GPIOB_BITBAND.ODR.b8 = 1;
      while (Length-- && write_buffer_index < 512)
        buffer[write_buffer_index++] = *Data++;
      GPIOB_BITBAND.ODR.b8 = 0;
      if (write_buffer_index == 512)
      {
        unsigned int addr = (USB_MASS_Manager.DataAddress / 4096) * 4096;
        FlashIC_Read_0(buff, addr, 4096);
        for (unsigned int i = 0; i < 512; i++)
          buff[(USB_MASS_Manager.DataAddress % 4096) + i] = buffer[i];
        FlashIC_EraseSector_0(addr);
        while (FlashIC_IsBusy_0());
        for (unsigned int i = 0; i < 16; i++)
        {
          FlashIC_Write_0(&buff[i * 256], addr, 256);
          addr += 256;
          while (FlashIC_IsBusy_0());
        }
        write_buffer_index = 0;
        USB_MASS_Manager.DataAddress += 512;
        USB_MASS_Manager.Sequences--;
        if (!USB_MASS_Manager.Sequences)
        {
          USB_MASS_Manager.dCSWDataResidue = 0;
          unsigned char csw[13] = {'U', 'S', 'B', 'C', };
          for (reg8 i = 0; i < 9; i++)
            (&csw[4])[i] = ((unsigned char*)&USB_MASS_Manager.dCBWTag)[i];
          USBP_Send(1, csw, 13);
          USB_MASS_Manager.State = USB_MASS_STATE_READY;
          return 0;
        }
      }
    }
    else                                //ready to received command block wrapper
    {
      USB_MASS_CBW_TypeDef* cbw = (USB_MASS_CBW_TypeDef*)Data;
      USB_MASS_Manager.dCBWTag[0] = cbw->dCBWTag[0];
      USB_MASS_Manager.dCBWTag[1] = cbw->dCBWTag[1];
      USB_MASS_Manager.dCBWTag[2] = cbw->dCBWTag[2];
      USB_MASS_Manager.dCBWTag[3] = cbw->dCBWTag[3];
      USB_MASS_Manager.dCSWDataResidue = cbw->dCBWDataTransferLength;
      {
        USB_MASS_SCSI_Command_TypeDef* command = (USB_MASS_SCSI_Command_TypeDef*)cbw->CBWCB;
        if (command->Command == SCSI_COMMAND_READ10)
        {
          USB_MASS_Manager.Sequences = (((command->READ_10.Length[0] << 8) + command->READ_10.Length[1]) * (512 / 64)) - 1;
          USB_MASS_Manager.DataAddress = command->READ_10.LogicalBlockAddress[0];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[1];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[2];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[3];
          USB_MASS_Manager.DataAddress *= 512;

          extern unsigned char sd_card;
          if (sd_card)
          {
            FlashIC_Read_0(buffer, USB_MASS_Manager.DataAddress, 64);
            USBP_Send(1, buffer, 64);
            USB_MASS_Manager.bCSWStatus = 0x00;
          }
          else
          {
            USBP_Send(1, "SD_FAILED", 64);
            USB_MASS_Manager.bCSWStatus = 0x01;
          }
          USB_MASS_Manager.DataAddress += 64;
          USB_MASS_Manager.State = USB_MASS_STATE_PREPARE_READ;
        }
        else if (command->Command == SCSI_COMMAND_WRITE10)
        {
          USB_MASS_Manager.Sequences = (command->READ_10.Length[0] << 8) + command->READ_10.Length[1];
          USB_MASS_Manager.DataAddress = command->READ_10.LogicalBlockAddress[0];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[1];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[2];
          USB_MASS_Manager.DataAddress <<= 8; USB_MASS_Manager.DataAddress |= command->READ_10.LogicalBlockAddress[3];
          USB_MASS_Manager.DataAddress *= 512;
          USB_MASS_Manager.State = USB_MASS_STATE_PREPARE_WRITE;
          write_buffer_index = 0;
          return 1;
        }
        else if (command->Command == SCSI_COMMAND_TEST_UNIT_READY)
        {
          USB_MASS_Manager.State = USB_MASS_STATE_RESPOND_STATUS;
          USBP_PIDIn(255);
        }
        else
        {
          USB_MASS_Manager.dCSWDataResidue = 0;
          USBP_ConfigDataPoint(EndpointIndex, 2, 2);
          switch (command->Command)
          {
//            case SCSI_COMMAND_FORMAT_UNIT:
//              break;
            case SCSI_COMMAND_INQUIRY:
              USBP_Send(1, Inquiry_Data, sizeof(Inquiry_Data));
              break;
            case SCSI_COMMAND_READ_CAPACITY10:
              USBP_Send(1, Capacity_Data, sizeof(Capacity_Data));
              break;
            case SCSI_COMMAND_READ_FORMAT_CAPACITIES:
              USBP_Send(1, FormatCapacities_Data, sizeof(FormatCapacities_Data));
              break;
//            case SCSI_COMMAND_VERIFY10:
//              break;
            case SCSI_COMMAND_MODE_SENSE6:
              USBP_Send(1, "\0\0\0\0\0\0\0\0", 8);
              break;
          }
          USB_MASS_Manager.State = USB_MASS_STATE_RESPOND_STATUS;
        }
      }
      return 0;
    }
  }
  return 1;
}
//==============================================================================================================================================================
reg8 USBP_PIDIn(reg8 EndpointIndex)
{
  if (EndpointIndex)
  {
    if (USB_MASS_Manager.State == USB_MASS_STATE_RESPOND_STATUS)
    {
      unsigned char csw[13] = {'U', 'S', 'B', 'C', };
      for (reg8 i = 0; i < 9; i++)
        (&csw[4])[i] = ((unsigned char*)&USB_MASS_Manager.dCBWTag)[i];
      USBP_Send(1, csw, 13);
      USB_MASS_Manager.State = USB_MASS_STATE_READY;
    }
    else if (USB_MASS_Manager.State == USB_MASS_STATE_PREPARE_READ)
    {
      
      extern unsigned char sd_card;
      if (sd_card)
      {
        FlashIC_Read_0(buffer, USB_MASS_Manager.DataAddress, 64);
        USBP_Send(1, buffer, 64);
        USB_MASS_Manager.bCSWStatus = 0x00;
      }
      else
      {
        USBP_Send(1, "SD_FAILED", 64);
        USB_MASS_Manager.bCSWStatus = 0x01;
      }
      USB_MASS_Manager.DataAddress += 64;
      USB_MASS_Manager.Sequences--;
      if (!USB_MASS_Manager.Sequences)
      {
        USB_MASS_Manager.dCSWDataResidue = 0;
        USB_MASS_Manager.State = USB_MASS_STATE_RESPOND_STATUS;
      }
    }
    return 0;
  }
  return 1;
}
//==============================================================================================================================================================
void USBP_OpenAnotherEndpoint()
{
  USBP_OpenEndpoint(1, (USBEndpoint_TypeDef){
    .Address = 1,
    .Type = USB_ENDPOINT_TYPE_BULK,
    .TX = {.Status = USB_ENDPOINT_STATUS_NAK, .DataID = 0},
    .RX = {.Status = USB_ENDPOINT_STATUS_VALID, .DataID = 0},
  });
}