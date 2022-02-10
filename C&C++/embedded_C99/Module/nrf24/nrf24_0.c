//#include <nrf24.h>
//#include <config.h>
//
//typedef enum
//{
//  NRF24_CONFIG                  = 0x00,
//  NRF24_EN_AA                   = 0x01,
//  NRF24_EN_RXADDR               = 0x02,
//  NRF24_SETUP_AW                = 0x03,
//  NRF24_SETUP_RETR              = 0x04,
//  NRF24_RF_CH                   = 0x05,
//  NRF24_RF_SETUP                = 0x06,
//  NRF24_STATUS                  = 0x07,
//  NRF24_OBSERVE_TX              = 0x08,
//  NRF24_RPD                     = 0x09,
//  NRF24_RX_ADDR_P0              = 0x0A,
//  NRF24_RX_ADDR_P1              = 0x0B,
//  NRF24_RX_ADDR_P2              = 0x0C,
//  NRF24_RX_ADDR_P3              = 0x0D,
//  NRF24_RX_ADDR_P4              = 0x0E,
//  NRF24_RX_ADDR_P5              = 0x0F,
//  NRF24_TX_ADDR                 = 0x10,
//  NRF24_RX_PW_P0                = 0x11,
//  NRF24_RX_PW_P1                = 0x12,
//  NRF24_RX_PW_P2                = 0x13,
//  NRF24_RX_PW_P3                = 0x14,
//  NRF24_RX_PW_P4                = 0x15,
//  NRF24_RX_PW_P5                = 0x16,
//  NRF24_FIFO_STATUS             = 0x17,
//  NRF24_DYNPD	                = 0x1C,
//  NRF24_FEATURE	                = 0x1D,
//} NRF24;
//typedef enum
//{
//  NRF24CMD_R_REGISTER           = 0x00,
//  NRF24CMD_W_REGISTER           = 0x20,
//  NRF24CMD_R_RX_PL_WID          = 0x60,
//  NRF24CMD_R_RX_PAYLOAD         = 0x61,
//  NRF24CMD_W_TX_PAYLOAD         = 0xA0,
//  NRF24CMD_W_ACK_PAYLOAD        = 0xA8,
//  NRF24CMD_FLUSH_TX             = 0xE1,
//  NRF24CMD_FLUSH_RX             = 0xE2,
//  NRF24CMD_REUSE_TX_PL          = 0xE3,
//  NRF24CMD_W_TX_PAYLOAD_NO_ACK  = 0xB0,
//  NRF24CMD_NOP                  = 0xFF,
//} NRF24CMD;
////==============================================================================================================================================================
////==============================================================================================================================================================
////==============================================================================================================================================================
////                                      |       //Address       Default         Description
//typedef BUNION(CONFIG_TypeDef, reg8,            //                              Configuration Register
//  PRIM_RX                               , 1,    //0
//  PWR_UP                                , 1,    //1
//  CRCO                                  , 1,    //2
//  EN_CRC                                , 1,    //3
//  MASK_MAX_RT                           , 1,    //4
//  MASK_TX_DS                            , 1,    //5
//  MASK_RX_DR                            , 1,    //6
//  _reserved                             , 1);
//typedef BUNION(RF_SETUP_TypeDef, reg8,          //                              RF Setup Register
//  _Obsolete  	                        , 1,    //0
//  RF_PWR                                , 2,    //1-2
//  RF_DR_HIGH  	                        , 1,    //3                             1->2Mbps
//  PLL_LOCK    	                        , 1,    //4
//  RF_DR_LOW                             , 1,    //5                             1->250kbps
//  _reserved  	                        , 1,
//  CONT_WAVE  	                        , 1);   //7
//typedef BUNION(FEATURE_TypeDef, reg8,
//  END_DYN_ACK                           ,1,     //0
//  END_ACK_PAY                           ,1,     //1
//  END_DPL                               ,1,     //2
//  _reserved                             ,5);
////==============================================================================================================================================================
////==============================================================================================================================================================
////==============================================================================================================================================================
//static void _Command(reg8 Command)
//{
//  NRF24_CONFIG_CE_0(0);
//  NRF24_CONFIG_CSN_0(0);
//  NRF24_SPI_WRITEBYTE_0(Command);
//  NRF24_CONFIG_CSN_0(1);
//}
////==============================================================================================================================================================
//static void _ConfigReg(reg8 Address, reg8 Value)
//{
//  NRF24_CONFIG_CE_0(0);
//  NRF24_CONFIG_CSN_0(0);
//  NRF24_SPI_WRITEBYTE_0(Address | NRF24CMD_W_REGISTER);
//  NRF24_SPI_WRITEBYTE_0(Value);
//  NRF24_CONFIG_CSN_0(1);
//}
////==============================================================================================================================================================
//static reg8 _ReadReg(reg8 Address)
//{
//  reg8 temp;
//  NRF24_CONFIG_CSN_0(0);
//  NRF24_SPI_WRITEBYTE_0(Address | NRF24CMD_R_REGISTER);
//  temp = NRF24_SPI_WRITEBYTE_0(NRF24CMD_NOP);
//  NRF24_CONFIG_CSN_0(1);
//  return temp;
//}
////==============================================================================================================================================================
//static void _WriteRegs(reg8 Address, const unsigned char __gptr* Data, reg8 Length)
//{
//  NRF24_CONFIG_CE_0(0);
//  NRF24_CONFIG_CSN_0(0);
//  if (Address < 0x20)
//    NRF24_SPI_WRITEBYTE_0(Address | NRF24CMD_W_REGISTER);
//  else
//    NRF24_SPI_WRITEBYTE_0(Address);
//  while (Length-- > 0)
//    NRF24_SPI_WRITEBYTE_0(*Data++);
//  NRF24_CONFIG_CSN_0(1);
//}
////==============================================================================================================================================================
//static void _ReadRegs(reg8 Address, unsigned char* Contain, reg8 Length)
//{
//  NRF24_CONFIG_CSN_0(0);
//  if (Address < 0x20)
//    NRF24_SPI_WRITEBYTE_0(Address | NRF24CMD_R_REGISTER);
//  else
//    NRF24_SPI_WRITEBYTE_0(Address);
//  while (Length-- > 0)
//    *Contain++ = NRF24_SPI_WRITEBYTE_0(NRF24CMD_NOP);
//  NRF24_CONFIG_CSN_0(1);
//}
////==============================================================================================================================================================
////==============================================================================================================================================================
////==============================================================================================================================================================
//reg8 NRF24_Init_0(const NRF24Init_TypeDef __gptr* NRF24Init)
//{
//  if (!NRF24Init)
//  {
//    static const NRF24Init_TypeDef __code nrf24_init_default = {
//      .BITS = {.RFChannel = 16, .AddressWidth = 3, .EnableDynamicPayloadForPipe = 0, .EnableTxNoAck = 0,
//      .EnableAckPayload = 0, .EnableDynamicPayload = 0, .DataRate = 1, .EnableCRC = 1, .CRCMode = 0, },
//    };
//    NRF24Init = &nrf24_init_default;
//  }
//  {
//    CONFIG_TypeDef config;
//    config.REG = _ReadReg(NRF24_CONFIG);
//    config.REG &= ~(BIT1 | BIT2 | BIT3);
//    config.REG |= NRF24Init->r3 & (BIT2 | BIT3);                //CRCO, EN_CRC, PWR_UP = 0
//    _ConfigReg(NRF24_CONFIG, config.REG);
//    if (_ReadReg(NRF24_CONFIG) != config.REG)
//      return 0;
//  }
//  _ConfigReg(NRF24_SETUP_AW, NRF24Init->BITS.AddressWidth);
//  _ConfigReg(NRF24_RF_CH, NRF24Init->BITS.RFChannel > 126 ? 16 : NRF24Init->BITS.RFChannel);  
//  {
//    RF_SETUP_TypeDef rf_setup;  
//    rf_setup.REG = _ReadReg(NRF24_RF_SETUP);
//    rf_setup.REG &= ~(BIT3 | BIT5);
//    rf_setup.REG |= NRF24Init->r2 & (BIT3 | BIT5);
//    _ConfigReg(NRF24_RF_SETUP, rf_setup.REG);    //Data rate
//  }
//  _ConfigReg(NRF24_FEATURE, NRF24Init->r2 & (BIT0 | BIT1 | BIT2));
//  _ConfigReg(NRF24_DYNPD, NRF24Init->BITS.EnableDynamicPayloadForPipe);
//  _Command(NRF24CMD_FLUSH_TX);
//  _Command(NRF24CMD_FLUSH_RX);
//  return 1;
//}
////==============================================================================================================================================================
//void NRF24_ModeTx_0(const NRF24Tx_TypeDef __gptr* NRF24Tx)
//{
//  if (!NRF24Tx)
//  {
//    static const NRF24Tx_TypeDef nrf24_tx_default = {
//      .Mode = {.BITS = {.EnableAutoAck = 1, .RFPower = 3, .TxMaxRetryNotInterrupt = 1, .TxDoneNotInterrupt = 1,
//                        .PayloadWidth = 32, .RetransmitCount = 5, .RetransmitDelay = (1000 / 251),}, },
//      .Address = {1, 2, 3, 4, 5},
//    };
//    NRF24Tx = &nrf24_tx_default;
//  }
//  _ConfigReg(NRF24_SETUP_RETR, NRF24Tx->Mode.r2);        //ARC, ARD
//  {
//    RF_SETUP_TypeDef rf_setup;
//    rf_setup.REG = _ReadReg(NRF24_RF_SETUP);
//    rf_setup.REG &= ~(BIT1 | BIT2);
//    rf_setup.REG |= NRF24Tx->Mode.r1 & (BIT1 | BIT2);
//    _ConfigReg(NRF24_RF_SETUP, rf_setup.REG);    //RF_PWR
//  }
//  _WriteRegs(NRF24_TX_ADDR, NRF24Tx->Address, 5);
//  if (NRF24Tx->Mode.BITS.EnableAutoAck)
//  {
//    _ConfigReg(NRF24_EN_RXADDR, 0x01);
//    _WriteRegs(NRF24_RX_ADDR_P0, NRF24Tx->Address, 5);
//    _ConfigReg(NRF24_EN_AA, 0x01);
//    {
//      FEATURE_TypeDef feature;
//      feature.REG = _ReadReg(NRF24_FEATURE);
//      if (!feature.BITS.END_DPL)
//        _ConfigReg(NRF24_RX_PW_P0, NRF24Tx->Mode.BITS.PayloadWidth);
//    }
//  }
//  {
//    CONFIG_TypeDef config;
//    config.REG = _ReadReg(NRF24_CONFIG);
//    config.REG &= ~(BIT0 | BIT4 | BIT5);
//    config.REG |= BIT1 | (NRF24Tx->Mode.r0 & (BIT4 | BIT5));
//    _ConfigReg(NRF24_CONFIG, config.REG);        //MASK_TX_DS, MASK_MAX_RT, PRIM_RX = 0, PWR_UP = 1
//  }
//}
////==============================================================================================================================================================
//void NRF24_ModeRx_0(const NRF24Rx_TypeDef __gptr* NRF24Rx)
//{
//  if (!NRF24Rx)
//  {
//    static const NRF24Rx_TypeDef nrf24_rx_default = {
//      .Mode = {.BITS = {.EnableRXPipe = BIT0, .RxDoneNotInterrupt = 1, .EnableAutoAckForPipe = BIT0, },},
//      .PayloadWidth = {32, 0, 0, 0, 0},
//      .Address = {{1, 2, 3, 4, 5},},
//    };
//    NRF24Rx = (NRF24Rx_TypeDef*)&nrf24_rx_default;
//  }
//  _ConfigReg(NRF24_EN_RXADDR, NRF24Rx->Mode.BITS.EnableRXPipe);
//  _ConfigReg(NRF24_EN_AA, NRF24Rx->Mode.BITS.EnableAutoAckForPipe);
//  _WriteRegs(NRF24_TX_ADDR, NRF24Rx->Address[0], 5);
//  for (reg8 i = 0; i < 6; i++)
//  {
//    _WriteRegs(NRF24_RX_ADDR_P0 + i, NRF24Rx->Address[i], 5);
//    _ConfigReg(NRF24_RX_PW_P0 + i, NRF24Rx->PayloadWidth[i]);
//  }
//  {
//    CONFIG_TypeDef config;
//    config.REG = _ReadReg(NRF24_CONFIG);
//    config.REG &= ~BIT6;
//    config.REG |= BIT0 | BIT1 | (NRF24Rx->Mode.r0 & BIT6);
//    _ConfigReg(NRF24_CONFIG, config.REG);        //MASK_RX_DR, PRIM_RX = 1, PWR_UP = 1
//  }
//  NRF24_CONFIG_CE_0(1);
//}
////==============================================================================================================================================================
//reg8 NRF24_Send_0(const unsigned char __gptr* Data, reg8 Length, NRF24TxResult_TypeDef* TxResult)
//{
//  TxResult->Status.r0 = 0;
//  _WriteRegs(NRF24CMD_W_TX_PAYLOAD, Data, Length);
//  NRF24_CONFIG_CE_0(1);
//  while (1)
//  {
//    NRF24_DELAY_0();
//    TxResult->Status.r0 = _ReadReg(NRF24_STATUS);
//    if (TxResult->Status.r0 & 0x30)
//      break;
//  }
//  NRF24_CONFIG_CE_0(0);
//  _Command(NRF24CMD_FLUSH_TX);
//  TxResult->Status.r1 = _ReadReg(NRF24_OBSERVE_TX);
//  if (TxResult->Status.BITS.RxReady)
//  {
//    TxResult->AckPayload.Length = _ReadReg(NRF24CMD_R_RX_PL_WID);
//    _ReadRegs(NRF24CMD_R_RX_PAYLOAD, TxResult->AckPayload.Data, TxResult->AckPayload.Length);
//    _Command(NRF24CMD_FLUSH_RX);
//  }
//  _ConfigReg(NRF24_STATUS, 0x70);
//  return TxResult->Status.BITS.TxDone;
//}
////==============================================================================================================================================================
//reg8 NRF24_Received_0(NRF24RxResult_TypeDef* RxResult, reg8 Process(NRF24RxResult_TypeDef*))
//{
//  RxResult->Status.REG = _ReadReg(NRF24_STATUS);
//  if (RxResult->Status.BITS.RxReady)
//  {
//    RxResult->Payload.Length = _ReadReg(NRF24CMD_R_RX_PL_WID);
//    _ReadRegs(NRF24CMD_R_RX_PAYLOAD, RxResult->Payload.Data, RxResult->Payload.Length);
//    _Command(NRF24CMD_FLUSH_RX);
//    reg8 n_break = 1;
//    if (Process)
//      n_break = Process(RxResult);
//    if (n_break)
//    {
//      _ConfigReg(NRF24_STATUS, 0x70);
//      NRF24_CONFIG_CE_0(1);
//    }
//    return 1;
//  }
//  return 0;
//}
////==============================================================================================================================================================
//void NRF24_AckPayload_0(reg8 Pipe, const unsigned char __gptr* Data, reg8 Length)
//{
//  _WriteRegs(NRF24CMD_W_ACK_PAYLOAD | Pipe, Data, Length);
//}
////==============================================================================================================================================================
//void NRF24_PowerUp_0()
//{
//  CONFIG_TypeDef config;
//  config.REG = _ReadReg(NRF24_CONFIG);
//  config.BITS.PWR_UP = 1;
//  _ConfigReg(NRF24_CONFIG, config.REG);
//}
////==============================================================================================================================================================
//void NRF24_PowerDown_0()
//{
//  CONFIG_TypeDef config;
//  config.REG = _ReadReg(NRF24_CONFIG);
//  config.BITS.PWR_UP = 0;
//  _ConfigReg(NRF24_CONFIG, config.REG);
//}