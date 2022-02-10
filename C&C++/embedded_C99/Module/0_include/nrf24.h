/*
MODE 0:
  +) Note:
      -) logic bus init
        NRF24_CONFIG_CE_0(0); NRF24_CONFIG_CSN_0(1); SPI_CLK = 0;
      -) must delay 100ms for nrf24 power stabilize
  +) Config:
      #define NRF24_CONFIG_CE_0(IsSet)
      #define NRF24_CONFIG_CSN_0(IsSet)
      #define NRF24_SPI_WRITEBYTE_0(Data)
        -) MSB, POL = 0, PHASE = 0, return data
      #define NRF24_DELAY_0()
  +) Declare:
  +) Using:
      reg8 NRF24_Init_0(const NRF24Init_TypeDef __gptr* NRF24Init);
        -) return 1 if done
        -) Example:
            NRF24Init_TypeDef nrf24_init = {
              .BITS = {.RFChannel = 16, .AddressWidth = 3, .EnableDynamicPayloadForPipe = 0, .EnableTxNoAck = 0,
              .EnableAckPayload = 0, .EnableDynamicPayload = 0, .DataRate = 1, .EnableCRC = 1, .CRCMode = 0, },
            };
            NRF24_Init_0(&nrf24_init);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      void NRF24_ModeTx_0(const NRF24Tx_TypeDef __gptr* NRF24Tx);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      void NRF24_ModeRx_0(const NRF24Rx_TypeDef __gptr* NRF24Rx);
      reg8 NRF24_Send_0(const unsigned char __gptr* Data, reg8 Length, NRF24TxResult_TypeDef* TxResult);
        -) if not enables dynamic payload length, <Length> must equal receiver's RX payload width
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      reg8 NRF24_Received_0(NRF24RxResult_TypeDef* RxResult, reg8 Process(NRF24RxResult_TypeDef*));
        -) return 1 if has rx packet
        -) Process return 0 if break RX mode
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      void NRF24_AckPayload_0(reg8 Pipe, const unsigned char __gptr* Data, reg8 Length);
        -) only for receiver: respond data to tranmister
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      void NRF24_PowerUp_0();
      void NRF24_PowerDown_0();
MODE 1:
  +) Config:
  +) Declare:
  +) Using:
      reg8 NRF24_Init_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Init_TypeDef __gptr* NRF24Init);
      void NRF24_ModeTx_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Tx_TypeDef __gptr* NRF24Tx);
      void NRF24_ModeRx_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Rx_TypeDef __gptr* NRF24Rx);
      reg8 NRF24_Send_1(const NRF24Function_TypeDef __code* NRF24Function, const unsigned char __gptr* Data, reg8 Length, NRF24TxResult_TypeDef* TxResult);
      reg8 NRF24_Received_1(const NRF24Function_TypeDef __code* NRF24Function, NRF24RxResult_TypeDef* RxResult, reg8 Process(NRF24RxResult_TypeDef*));
      void NRF24_AckPayload_1(const NRF24Function_TypeDef __code* NRF24Function, reg8 Pipe, const unsigned char __gptr* Data, reg8 Length);
      void NRF24_PowerUp_1(const NRF24Function_TypeDef __code* NRF24Function);
      void NRF24_PowerDown_1(const NRF24Function_TypeDef __code* NRF24Function);
*/
#ifndef _NRF24_H_
#define _NRF24_H_

#include <common.h>
#include <define.h>
//==============================================================================================================================================================
typedef struct
{
  void (__code* ConfigCSN)(reg8 IsSet);
  void (__code* ConfigCE)(reg8 IsSet);
  reg8 (__code* SPI_WriteByte)(reg8 Data);
  void (__code* Delay)();                       //                              unnecessary
} NRF24Function_TypeDef;
/*
  Example:
    static void NRF24_ConfigCSN_0(reg8 IsSet)
    {
      NRF24_CSN_PIN_0 = IsSet;
    }
    static void NRF24_ConfigCE_0(reg8 IsSet)
    {
      NRF24_CE_PIN_0 = IsSet;
    }
    static reg8 NRF24_WriteByte_0(reg8 Data)
    {
      return SPI_WriteByte(Data);
    }
    static void NRF24_Delay_0()
    {
      delay_ms(10);
    }
    static const NRF24Function_TypeDef __code NRF24Function_0 = {
      .ConfigCSN = NRF24_ConfigCSN_0,
      .ConfigCE = NRF24_ConfigCE_0,
      .SPI_WriteByte = NRF24_WriteByte_0,
      .Delay = NRF24_Delay_0,
    };
*/
//==============================================================================================================================================================
//===========================================================       LEVEL 1      ===============================================================================
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef BRUNION_32x8(NRF24Init_TypeDef, ,
  r0, r1, r2, r3,
  //r0
  RFChannel                             , 8,    //              16              Frequency channel: 0->125
  //r1
  AddressWidth                          , 2,    //0-1           3               Address Widths
                                                //                                      1       3 bytes
                                                //                                      2       4 bytes
                                                //                                      3       5 bytes
  EnableDynamicPayloadForPipe           , 6,    //2:7           BITN            Enable dynamic payload length for each Pipe
  //r2
  EnableTxNoAck                         , 1,    //0             0               Enables the W_TX_PAYLOAD_NOACK command  
  EnableAckPayload                      , 1,    //1             0               Enables Payload with ACK , EN_DPL must be enabled
  EnableDynamicPayload                  , 1,    //2             0               Enables Dynamic Payload Length
  DataRate                              , 2,    //3:5           1               Data rates
                                                //                                      0       1 Mbps
                                                //                                      1       2 Mbps
                                                //                                      4       250 Kbps
  _reserved                             , 2,
  //r3
  _reserved1                            , 2,
  CRCMode                               , 1,    //2             0               CRC encoding scheme
                                                //                                      0       1 byte
                                                //                                      1       2 byte
  EnableCRC                             , 1,    //3             1               Enable CRC
  _reserved2                            , 4);
/*
  Example:
  NRF24Init_TypeDef nrf24_init = {
    .BITS = {.RFChannel = 16, .AddressWidth = 3, .EnableDynamicPayloadForPipe = 0, .EnableTxNoAck = 0,
    .EnableAckPayload = 0, .EnableDynamicPayload = 0, .DataRate = 1, .EnableCRC = 1, .CRCMode = 0, },
  };
  NRF24_Init_0(&nrf24_init);
*/
reg8 NRF24_Init_0(const NRF24Init_TypeDef __gptr* NRF24Init);
reg8 NRF24_Init_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Init_TypeDef __gptr* NRF24Init);
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef STRUCT(NRF24Tx_TypeDef,
  BRUNION_24x8(Mode, ,
    r0, r1, r2,
    //r0
    EnableAutoAck                       , 1,    //0             1               Enable Auto Acknowledgment
    
    RFPower                             , 2,    //1-2           3               RF output power in TX mode
                                                //                                      0       -18 dBm
                                                //                                      1       -12 dBm
                                                //                                      2       -6 dBm
                                                //                                      3       0 dBm 
    _reserved                           , 1,
    TxMaxRetryNotInterrupt              , 1,    //4             1               Disable interrupt caused by MAX_RT
    TxDoneNotInterrupt                  , 1,    //5             1               Disable interrupt caused by TX_DS
    _reserved1                          , 2,
    //r1
    PayloadWidth                        , 6,    //0:5           32              if (EN_AA == 1 && !EN_DPL) => RX0 payload width
    _reserved2                          , 2,
    //r2
    RetransmitCount                     , 4,    //0:3           5               Auto Retransmit Count                                         
    RetransmitDelay                     , 4);   //4:7           (1000 / 251)    Auto Retransmit Delay (1000 us)
  unsigned char Address[5];);                   //              [1,2,3,4,5]     Transmit address
/*
  Example:
  NRF24Tx_TypeDef nrf24_tx = {
    .Mode = {.BITS = {.EnableAutoAck = 1, .RFPower = 3, .TxMaxRetryNotInterrupt = 1, .TxDoneNotInterrupt = 1,
                      .PayloadWidth = 32, .RetransmitCount = 5, .RetransmitDelay = (1000 / 251),}, },
    .Address = {1, 2, 3, 4, 5},
  };
  NRF24_ModeTx_0(&nrf24_tx);
*/
void NRF24_ModeTx_0(const NRF24Tx_TypeDef __gptr* NRF24Tx);
void NRF24_ModeTx_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Tx_TypeDef __gptr* NRF24Tx);
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef STRUCT(NRF24Rx_TypeDef,
  BRUNION_16x8(Mode, ,
    r0, r1,
    //r0
    EnableRXPipe                        , 6,    //0:5           BIT0            Enabled RX Addresses for each Pipe
    RxDoneNotInterrupt                  , 1,    //6             1               Disable interrupt caused by RX_DR    
    _reserved0                          , 1,
    //r1
    EnableAutoAckForPipe                , 6,    //0:5           BIT0            Enable Auto Acknowledgment for each Pipe
    _reserved1                          , 2);
  unsigned char Address[6][5];                  //              [0,1,2,3,4,5]   Receive address (Default for Pipe 0)
  unsigned char PayloadWidth[6];);              //              32              RX payload width (Default for Pipe 0)
/*
  Example:
  NRF24Rx_TypeDef nrf24_rx = {
    .Mode = {.BITS = {.EnableRXPipe = BIT0, .RxDoneNotInterrupt = 1, .EnableAutoAckForPipe = BIT0, },},
    .PayloadWidth = {32, 0, 0, 0, 0},
    .Address = {{1, 2, 3, 4, 5},},
  };
  NRF24_ModeRx_0(&nrf24_rx);
*/
void NRF24_ModeRx_0(const NRF24Rx_TypeDef __gptr* NRF24Rx);
void NRF24_ModeRx_1(const NRF24Function_TypeDef __code* NRF24Function, const NRF24Rx_TypeDef __gptr* NRF24Rx);
//==============================================================================================================================================================
typedef STRUCT(NRF24TxResult_TypeDef,
  BRUNION_16x8(Status, ,
    r0, r1,
    //r0
    _reserved0                          , 4,
    MaxRetry                            , 1,    //                              Maximum number of TX retransmits
    TxDone                              , 1,    //                              Data sent
    RxReady                             , 1,    //                              Ack payload data ready
    _reserved1                          , 1,
    //r1
    RetransmitCount                     , 4,    //                              Count retransmitted packets
    LostPacketsCount                    , 4);   //                              Count lost packets
  RSTRUCT(AckPayload, unsigned char,
    Length, Data[32]););
reg8 NRF24_Send_0(const unsigned char __gptr* Data, reg8 Length, NRF24TxResult_TypeDef* TxResult);
reg8 NRF24_Send_1(const NRF24Function_TypeDef __code* NRF24Function, const unsigned char __gptr* Data, reg8 Length, NRF24TxResult_TypeDef* TxResult);
//==============================================================================================================================================================
typedef STRUCT(NRF24RxResult_TypeDef,
  BUNION(Status, unsigned char,
    _reserved0                          , 1,
    PipeNumber                          , 3,    //                              Data pipe number for the payload available for reading from RX_FIFO
    _reserved1                          , 2,
    RxReady                             , 1,    //                              Data Ready
    _reserved2                          , 1);
  RSTRUCT(Payload, unsigned char,
    Length, Data[32]););
reg8 NRF24_Received_0(NRF24RxResult_TypeDef* RxResult, reg8 Process(NRF24RxResult_TypeDef*));
reg8 NRF24_Received_1(const NRF24Function_TypeDef __code* NRF24Function, NRF24RxResult_TypeDef* RxResult, reg8 Process(NRF24RxResult_TypeDef*));
//==============================================================================================================================================================
void NRF24_AckPayload_0(reg8 Pipe, const unsigned char __gptr* Data, reg8 Length);
void NRF24_AckPayload_1(const NRF24Function_TypeDef __code* NRF24Function, reg8 Pipe, const unsigned char __gptr* Data, reg8 Length);
//==============================================================================================================================================================
void NRF24_PowerUp_0();
void NRF24_PowerUp_1(const NRF24Function_TypeDef __code* NRF24Function);
//==============================================================================================================================================================
void NRF24_PowerDown_0();
void NRF24_PowerDown_1(const NRF24Function_TypeDef __code* NRF24Function);

#endif