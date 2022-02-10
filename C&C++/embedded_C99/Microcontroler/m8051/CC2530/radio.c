#include <radio.h>
#include <interrupt.h>
#include <common.h>
//==============================================================================================================================================================
//error handle
#pragma vector = RFERR_IRQv
__interrupt static void RF_ERR_ISR()
{
  //ITC_IF0.BITS.RF_ERR = 0;
  RADIO_ERROR_Handle();
  RADIO_ERROR_FLAG.REG = 0;
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_RX));
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_TX));
}
//irq handle
#pragma vector = RF_IRQv
__interrupt static void RF_IRQ_ISR()
{
  ITC_IF2.REG = 0;
  RADIO_IRQ_Handle();
  RADIO_IRQ_FLAG0.REG = 0;
  RADIO_IRQ_FLAG1.REG = 0;
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_RX));
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_TX));
}
//==============================================================================================================================================================
void RADIO_Init(const RadioInit_TypeDef __code* RadioInit)
{
  unsigned char i;
  //turn off RF interrupt for re-config
  ITC_IEN2.BITS.RF = 0;
  ITC_IEN0.BITS.RF_ERR = 0;
  //clear flag
  ITC_IF0.BITS.RF_ERR = 0;
  ITC_IF2.REG = 0;
  RADIO_ERROR_FLAG.REG = 0;
  RADIO_IRQ_FLAG0.REG = 0;  
  RADIO_IRQ_FLAG1.REG = 0;
  //re-init RF
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_RX));
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_TX));
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_RF_OFF));
  //init RF have optimal performance
  RADIO.AD_TEST_TUNING.AGC.REFERENCE = 0x15;
  RADIO.AD_TEST_TUNING.TX_FILT_CFG = 0x09;
  RADIO.AD_TEST_TUNING.TUNE.FRQ_CALIB.r1 = 0x00;
  //user-config
  RADIO.RADIO_CTRL.FREQUENCE.CHANNEL = RadioInit->Channel;
  for (i = 0; i < 12; i++)
    ((unsigned char*)&RADIO.ADDRESS.LOCAL)[i] = ((const unsigned char __code*)&RadioInit->Address)[i];
  for ( i = 0; i < 9; i++)
    ((unsigned char*)&(RADIO.RX_CTRL.FRAME_FILTER))[i] = ((unsigned char*)&(RadioInit->RX_CTRL.FRAME_FILTER))[i];
  //user-interrupt enable
  RADIO.INTERRUPT_ENABLE.IRQ.r0 = RadioInit->INTERRUPT_ENABLE.IRQ.r0;
  RADIO.INTERRUPT_ENABLE.IRQ.r1 = RadioInit->INTERRUPT_ENABLE.IRQ.r1;
  RADIO.INTERRUPT_ENABLE.ERROR.REG = RadioInit->INTERRUPT_ENABLE.ERROR.REG;
  //enable RF interrupt
  if (RADIO.INTERRUPT_ENABLE.IRQ.r0 || RADIO.INTERRUPT_ENABLE.IRQ.r1)
    ITC_IEN2.BITS.RF = 1;
  if (RADIO.INTERRUPT_ENABLE.ERROR.REG)
    ITC_IEN0.BITS.RF_ERR = 1;
}
//==============================================================================================================================================================
void RADIO_Send(const RadioTX_TypeDef* RadioTX, const AddressField_TypeDef* DstAddress, const unsigned char __gptr* Data, unsigned char Size)
{
  unsigned char send_len = Size + 5, i;
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_FLUSH_TX));  
  RADIO_RFD = 0;
  RADIO_RFD = RadioTX->FCF.r0;
  RADIO_RFD = RadioTX->FCF.r1;
  RADIO_RFD = RadioTX->SequenceNumber;
  {
    static const unsigned char __code addr_size[] = {0, 4, 4, 10};
    for (i = 0; i < addr_size[RadioTX->FCF.BITS.Dest_AM]; i++)
    {
      RADIO_RFD = ((const unsigned char*)DstAddress)[i];
      send_len++;
    }
  }
  if (RadioTX->FCF.BITS.Src_AM)
  {
    RADIO_RFD = ((unsigned char*)&RADIO.ADDRESS.LOCAL.PAN_ID)[1];
    RADIO_RFD = ((unsigned char*)&RADIO.ADDRESS.LOCAL.PAN_ID)[0];
    if (RadioTX->FCF.BITS.Src_AM == 2)
    {
      RADIO_RFD = ((unsigned char*)&RADIO.ADDRESS.LOCAL.SHORT_ADDR)[1];
      RADIO_RFD = ((unsigned char*)&RADIO.ADDRESS.LOCAL.SHORT_ADDR)[0];
      send_len += 4;
    }
    else
    {
      for (i = 0; i < 8; i++)
        RADIO_RFD = RADIO.ADDRESS.LOCAL.EXTEND_ADDR[i];
      send_len += 10;
    }
  }
  RADIO.RAM.TX_FIFO[0] = send_len;
  while (Size--)
    RADIO_RFD = *Data++;
  RADIO_CSPWrite(CSP_CMD_IMME_STROBE(CSP_S_TX_ON));
}