#ifndef _RADIO_H_
#define _RADIO_H_

#include <IEEE_802_15_4.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BRUNION_16x8(FRAME_FILTER, ,                  //0x6180-0x6181 0x780D
    r0, r1,
    
    ENABLE                              , 1,    //0             1               Enables frame filtering
    PAN_COORDINATOR                     , 1,    //1             0               using PAN coordinator address in no destination address mode
    MAX_FRAME_VERSION                   , 2,    //2-3           3               if (frame filtering), if (frame.type > MAX_FRAME_VERSION) -> rejected
    FCF_RESERVED_MASK                   , 3,    //4:6           0               if (frame filtering), if (FCF_RESERVED_MASK & FCF[9:7]) -> rejected
    _reserved                           , 1,
    _reserved1                          , 1,
    MODIFY_FRAME_TYPE_FILTER            , 2,    //1-2           0               Modify the frame-type field before frame-type filtering:
                                                //                                      0: not change
                                                //                                      1: Invert MSB
                                                //                                      2: Set MSB to 0
                                                //                                      3: Set MSB to 1
    ACCEPT_BEACON                       , 1,    //3             1               accepted beacon frames(frame-type = 0)
    ACCEPT_DATA                         , 1,    //4             1               accepted data frames(frame-type = 1)
    ACCEPT_ACK                          , 1,    //5             1               acceptedacknowledgment frames(frame-type = 2)
    ACCEPT_MAC_CMD                      , 1,    //6             1               accepted MAC command frames(frame-type = 3)
    ACCEPT_4TO7_FRAME                   , 1);   //7             0               accepted frames have frame type = 4, 5, 6, 7
  BUNION(SOURCE_MATCH, unsigned char,           //0x6182        0x07            Source Address Matching and Pending Bits
    SOURCE_MATCH_EN                     , 1,    //0             1               Source address matching enable
    AUTO_PEND                           , 1,    //1             1               Automatic acknowledgment pending flag enable
    PEND_DATAREQ_ONLY                   , 1,    //2             1               When this bit is set, the AUTOPEND function also requires that the received frame is a DATA REQUEST MAC command frame 
    _reserved                           , 5);
  unsigned char SOURCE_SHORT_EN[3];             //0x6183:0x6185                 Short Address Matching enable
  unsigned char SOURCE_EXTEND_EN[3];            //0x6186:0x6188                 Extended Address Matching enable 
} RADIO_RX_CTRL_TypeDef;
typedef struct
{
  BRUNION_16x8(IRQ, ,                           //0x61A3-0x61A4                 RF Interrupt
    r0, r1,

    ACT_UNUSED                          , 1,    //0             0                       
    SFD                                 , 1,    //1             0               SFD has been received or transmitted
    FIFOP                               , 1,    //2             0               The number of bytes in the RXFIFO is above the threshold
    SOURCE_MATCH_DONE                   , 1,    //3             0               Source matching complete
    SOURCE_MATCH_FOUND                  , 1,    //4             0               Source match found
    FRAME_ACCEPTED                      , 1,    //5             0               Frame has passed frame filtering
    RX_PACKET_DONE                      , 1,    //6             0               A complete frame has been received
    RX_MASK_ZERO                        , 1,    //7             0               The RX_ENABLE register has gone from a nonzero state to an all-zero state  
    TX_ACK_DONE                         , 1,    //0             0               An acknowledgment frame has been completely transmitted
    TX_DONE                             , 1,    //1             0               A complete frame has been transmitted.
    RF_IDLE                             , 1,    //2             0               Radio state machine has entered the idle state
    CSP_MAN_INT                         , 1,    //3             0               Manual interrupt generated from CSP
    CSP_STOP                            , 1,    //4             0               CSP has stopped program execution
    CSP_WAIT                            , 1,    //5             0               Execution continued after a wait instruction in CSP
    const _reserved                     , 2);
  BUNION(ERROR, unsigned char,                  //0x61A5                        RF Error Interrupt
    NLOCK                               , 1,    //0             0               Frequency synthesizer failed to achieve lock after time-out or lock is lost during reception
    RX_ABORT                            , 1,    //1             0               Reception of a frame was aborted
    RX_OVER_FLW                         , 1,    //2             0               RX_FIFO overflowed
    RX_UNDER_FLW                        , 1,    //3             0               RX_FIFO underflowed
    TX_OVERF                            , 1,    //4             0               TX_FIFO overflowed
    TX_UNDERF                           , 1,    //5             0               TX_FIFO underflowed
    STROBE_ERR                          , 1,    //6             0               A command strobe was issued at a time it could not be processed
    const _reserved                     , 1);
} RADIO_INTERRUPT_ENABLE_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  struct
  {
    unsigned char RX_FIFO[128];                 //0x6000:0x607F
    unsigned char TX_FIFO[128];                 //0x6080:0x60FF
  } RAM;
  struct
  {
    struct
    {
      union
      {
        xRSTRUCT(EXTEND, unsigned char, EX_, 0, 11, [8]);
        xRSTRUCT(SHORT, ShortAddressField_TypeDef, SH_, 0, 23, );
      } TABLE;                                  //0x6100:0x615F
      struct
      {
        unsigned char MASK[3];                  //0x6160-0x6162
        unsigned char INDEX;                    //0x6163
      } MATCHING_RESULT;
      struct
      {
        unsigned char EXTEND_PEND_EN[3];        //0x6164-0x6166                 enables and disables automatic pending for each of the 12 extended addresses, bit[2n]
        unsigned char SHORT_PEND_EN[3];         //0x6167-0x6169                 enables and disables automatic pending for each of the 24 short addresses
      } MATCHING_CTRL;
    } SOURCE;
    struct
    {
      unsigned char EXTEND_ADDR[8];             //0x616A-0x6171                 The IEEE extended address used during destination address filtering
      unsigned short PAN_ID;                    //0x6172-0x6173                 The PAN ID used during destination address filtering
      unsigned short SHORT_ADDR;                //0x6174-0x6174                 The short address used during destination address filtering
    } LOCAL;
    unsigned char _reserved[0x6180 - 0x6176];
  } ADDRESS;
  RADIO_RX_CTRL_TypeDef RX_CTRL;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  struct
  {
    BRUNION_16x8(FRAME_CTRL, ,
      r0, r1,
      
      TX_MODE                           , 2,    //0-1           0               Set test modes for TX
      RX_MODE                           , 2,    //2-3           0               Set RX modes
      ENERGY_SCAN                       , 1,    //4             0
      AUTO_ACK                          , 1,    //5             0               all frames -> address filtering -> acknowledge request -> valid CRC -> automatically acknowledged
      AUTO_CRC                          , 1,    //6             1
      APPEND_DATA_MODE                  , 1,    //7
      SET_RX_EN_MASK_ON_TX              , 1,    //0             1               Defines whether STXON sets bit 6 in the RXENABLE register or leaves it unchanged
      IGNORE_TX_UNDER_FLW               , 1,    //1             0               ignored TX underflow flag
      PENDING_OR                        , 1,    //2             0
      _reserved                         , 5);
    struct
    {                                           //applies for STATUS
      BUNION(, unsigned char,                   //              0x00            Clear -> CSP_Command(SRF_OFF)
        _reserved                       , 5,
        SRX_MASK_BIT                    , 1,    //5             0               Set -> CSP_Command(SRX_MASK_BIT_SET), Clear -> CSP_Command(SRX_MASK_BIT_CLR)
        STX_ON                          , 1,    //6             0               Set -> CSP_Command(STX_ON) if SET_RX_EN_MASK_ON_TX = 1
        SRX_ON                          , 1)    //7             0               Set -> CSP_Command(SRX_ON)
          const STATUS,                         //0x618B        0x00
          SET,                                  //0x618C
          CLEAR;                                //0x618D
    } RX_ENABLING;
    RSTRUCT(FREQUENCE, unsigned char,
      XOSC32M_TUNE,                             //0x618E        0xF             Tune crystal oscillator (0->15)
      CHANNEL);                                 //0x618F        0xB             Frequency control word  (0->127)
    struct
    {
      unsigned char POWER;                      //0x6190        0xF5            Controls the Output Power
      BUNION(CTRL, unsigned char,               //0x6191        0x69            Controls the TX Settings
        TX_MIX_CURRENT                  , 2,    //0-1           1               Transmit mixers core current: current increases with increasing setting
        DAC_DC                          , 2,    //2-3           2               Adjusts the dc level to the TX mixer
        DAC_CURR                        , 3,    //4:6           6               Change the current in the DAC
        const _reserved                 , 1);
    } TX_SETTING;
    BRUNION_16x8(STATUS, ,                      //0x6192-0x6193
      r0, r1,
      
      FSM_FFCTRL_STATE                  , 6,    //0:5           --              Gives the current state of the FIFO and frame-control (FFCTRL) finite-state machine
      CAL_RUNNING                       , 1,    //6             0               Frequency synthesizer calibration status
      _reserved                         , 1,
      RX_ACTIVE                         , 1,    //0             0               Status signal, active when FFCTRL is in one of the receive states
      TX_ACTIVE                         , 1,    //1             0               Status signal, active when FFCTRL is in one of the transmit states
      LOCK_STATUS                       , 1,    //2             0               1 when PLL is in lock, otherwise 0.
      SAMPLED_CCA                       , 1,    //3             0               Contains a sampled value of the CCA. The value is updated whenever a SSAMPLECCA or STXONCCA strobe is issued
      CCA                               , 1,    //4             0               Clear-channel assessment
      SFD                               , 1,    //5             0
      FIFOP                             , 1,    //6             0
      FIFO                              , 1);   //7             0               FIFO is high whenever there is data in the RXFIFO. Low during RXFIFO overflow
    union
    {
      RSTRUCT(FIFO, unsigned char,
        PACKET_THRESHOLD,                       //0x6194        0x40            Threshold used when generating FIFOP signal (0->127)
        _reserved[0x619A - 0x6195],
        const RX_FIRST,                         //0x619A        0x00            First Byte in RX_FIFO
        const RX_COUNT,                         //0x619B        0x00            Number of Bytes in RX_FIFO
        const TX_COUNT,                         //0x619C        0x00            Number of Bytes in TX_FIFO
        const RX_FIRST_PTR,                     //0x619D        0x00            RAM address offset of the first byte in the RX_FIFO
        const RX_LAST_PTR,                      //0x619E        0x00            RAM address offset of the last byte +1 byte in the RX_FIFO
        const RX_P1_PTR,                        //0x619F        0x00            RAM address offset of the first byte of the first frame in the RX_FIFO
        _reserved1,
        const TX_FIRST_PTR,                     //0x61A1        0x00            RAM address offset of the next byte to be transmitted from the TX_FIFO
        const TX_LAST_PTR);                     //0x61A2        0x00            RAM address offset of the last byte +1 byte of the TX_FIFO
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      RSTRUCT(RSSI, unsigned char,
        _reserved[0x6198 - 0x6194],
        const VALUE,                            //0x6198        0x80            RSSI estimate on a logarithmic scale, signed number in 2s complement
        const VALID,                            //0x6199        0x00            RSSI value is valid 
        _reserved1[0x61A3 - 0x619A]);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        unsigned char _reserved;
        BUNION(CTRL, unsigned char,             //                              FSM Options
          RX2RX_TIME_OFF                , 1,    //0             1               Defines whether or not a 12-symbol time-out should be used after frame
          SLOTTED_ACK                   , 1,    //1             0               Controls timing of transmission of acknowledge frames
          _reserved                     , 6);
        unsigned char _reserved1[0x61A3 - 0x6196];
      } FSM;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      struct
      {
        unsigned char _reserved[0x6196 - 0x6194];
        unsigned char THRESHOLD;                //0x6196        0xE0          
        BUNION(CTRL, unsigned char,             //0x6197                        Other CCA Options
          CCA_HYST                      , 3,    //0:2           2               Sets the level of CCA hysteresis. Unsigned values given in dB
          CCA_MODE                      , 2,    //3-4           3
          const _reserved               , 3);
        unsigned char _reserved1[0x61A3 - 0x6198];
      } CCA;
    };
  } RADIO_CTRL;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  RADIO_INTERRUPT_ENABLE_TypeDef INTERRUPT_ENABLE;
  unsigned char _reserved;
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  BUNION(RF_RANDOM, const unsigned char,        //0x61A7                        Random Data
    I                                   , 1,    //0             0               Random bit from the I channel of the receiver
    Q                                   , 1,    //0             0               Random bit from the Q channel of the receiver
    _reserved                           , 6);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  union
  {
    struct
    {
      BRUNION_16x8(MODEM_CTRL, ,                //0x61A8-0x16A9
        r0, r1,
        
        TX_FILTER                       , 1,    //0             1               Defines the kind of TX filter that is used
        PREAMBLE_LENGTH                 , 4,    //1:4           2               The number of preamble bytes (two zero-symbols) to be sent in TX mode prior to the SFD
        DEMOD_AVG_MODE                  , 1,    //5             0               Defines the behavior or the frequency offset averaging filter
        DEM_NUM_ZEROS                   , 2,    //6-7           2               Sets how many zero symbols must be detected before the sync word when searching for sync
        CORR_THR                        , 5,    //0:4           0x14            Demodulator correlator threshold value, required before SFD search
        CORR_THR_SFD                    , 1,    //5             0               Defines requirements for SFD detection
        const _reserved                 , 2);
      const unsigned char FREQEST;              //0x61AA                        Estimated RF Frequency Offset
      struct
      {
        BUNION(RX, unsigned char,               //0x61AB                        Tune Receive Section
          MIX_CURRENT                   , 2,    //0-1           3               Control of the receiver mixers output current
          GBIAS_LNA_REF                 , 2,    //2-3           3               Adjusts front-end LNA PTAT current output (from M = 3 to M = 6)
          GBIAS_LNA2_REF                , 2,    //4-5           3               Adjusts front-end LNA2 or mixer PTAT current output (from M = 3 to M = 6)
          const _reserved               , 2);
        BUNION(FRQ_SYNT, unsigned char,         //0x61AC                        Tune Frequency Synthesizer
          LODIV_CURRENT                 , 2,    //0-1           2               Adjusts divider currents, except mixer and PA buffers
          LODIV_BUF_CURRENT_RX          , 2,    //2-3           2               Adjusts current in mixer and PA buffers when TX_ACTIVE = 0
          LODIV_BUF_CURRENT_TX          , 2,    //4-5           1               Adjusts current in mixer and PA buffers when TX_ACTIVE = 1
          PRE_CURRENT                   , 2);   //6-7           1               Prescaler current setting
        unsigned char _reserved1;
        BRUNION_24x8(FRQ_CALIB, ,               //0x61AE:0x61B0
          r0, r1, r2,
          
          VCO_CURR                      , 2,    //0-1           3               Defines current in VCO core. Sets the multiplier between calibrated current and VCO current
          _reserved                     , 6,
          VCO_CAPARR                    , 6,    //0:5           0x20            VCO capacitor array setting. Programmed during calibration. Override value when VCO_CAPARR_OE = 1
          VCO_CAPARR_OE                 , 1,    //6             0               Override the calibration result with the value from VCO_CAPARR[5:0]
          const _reserved1              , 1,
          VCO_CAPARR_CAL_CTRL           , 2,    //0-1           2               Calibration accuracy setting for the capacitor array part of the calibration
          VCO_VC_DAC                    , 4,    //2:5           10              Bit vector for programming varactor control voltage from VC DAC
          VCO_DAC_EN_OV                 , 1,    //6             0               Enables the VCO DAC when 1
          const _reserved2              , 1);
      } TUNE;
      struct
      {
        BUNION(DYNAMIC_RANGE, unsigned char,    //0x61B1
          AGC_DR_XTND_THR               , 6,    //0:5           0x1F       
          AGC_DR_XTND_EN                , 1,    //6             1
          const _reserved               , 1);
        unsigned char REFERENCE;                //0x61B2        0x11            Target value for the AGC control loop, given in 1-dB steps (0->63)      
        BUNION(GAIN_OVERRIDE, unsigned char,    //0x61B3                      
          LNA_CURRENT_OE                , 1,    //0             0               Write 1 to override the AGC LNA current setting with the values above (LNA1_CURRENT, LNA2_CURRENT, and LNA3_CURRENT)
          LNA3_CURRENT                  , 2,    //1-2           0               Overrride value for LNA 3. Only used when LNA_CURRENT_OE = 1
          LNA2_CURRENT                  , 3,    //3:5           0               Overrride value for LNA 2. Only used when LNA_CURRENT_OE = 1
          LNA1_CURRENT                  , 2);   //6-7           0               Overrride value for LNA 1. Only used when LNA_CURRENT_OE = 1
        BUNION(CTRL, unsigned char,             //0x61B4                      
          AAF_RP_OE                     , 1,    //0             0               Write 1 to override the AGC AAF control signals with the values stored in AAF_RP
          AAF_RP                        , 2,    //1-2           3               Overrides the AGC control signals to AAF when AAF_RP_OE = 1
          AGC_WIN_SIZE                  , 2,    //3-4           1               Window size for the accumulate and dump function in the AGC
          AGC_SETTLE_WAIT               , 2,    //5-6           1               Time for AGC to wait for analog gain to settle after a gain change
          const _reserved               , 1);
      } AGC;
      BRUNION_24x8(ADC, ,                       //0x61B5:0x61B7
        r0, r1, r2,
        
        ADC_DAC2_EN                     , 1,    //0             0               Enables DAC2 for enhanced ADC stability
        ADC_GM_ADJ                      , 3,    //1:3           0               Gm control for test and debug
        ADC_QUANT_ADJ                   , 2,    //4-5           1               Quantizer threshold control for test and debug
        ADC_VREF_ADJ                    , 2,    //6-7           0               Quantizer threshold control for test and debug
        ADC_C3_ADJ                      , 2,    //0-1           2               Used to adjust capacitor values in ADC
        ADC_C2_ADJ                      , 2,    //2-3           3               Used to adjust capacitor values in ADC
        ADC_TEST_CTRL                   , 4,    //4:7           0               ADC test mode selector
        ADC_DAC_ROT                     , 1,    //0             1               Control of DAC DWA scheme
        ADC_FF_ADJ                      , 2,    //1-2           1               Adjust feedforward
        AAF_RS                          , 2,    //3-4           0               Controls series resistance of AAF
        ADC_TEST_MODE                   , 2,    //5-6           0               Test mode to enable output of ADC data from demodulator
        const _reserved                 , 1);
      BRUNION_16x8(MODEM, ,                     //0x61B8-0x61B9
        r0, r1,
        
        DC_BLOCK_MODE                   , 2,    //0-1           1               Selects the mode of operation
        DC_WIN_SIZE                     , 2,    //2-3           1               Controls the number of samples to be accumulated between each dump of the accumulate-and-dump filter used in dc removal
        TX_TONE                         , 4,    //4:7           7               Enables the possibility to transmit a baseband tone by picking samples from the sine tables with a controllable phase step between the samples
        _reserved                       , 1,
        MODULATION_MODE                 , 1,    //1             0               Set one of two RF modulation modes for RX/TX
        RFC_SNIFF_EN                    , 1,    //2             0             
        RAMP_AMP                        , 1,    //3             1             
        MOD_IF                          , 1,    //4             0             
        const _reserved1                , 3);
      RSTRUCT(DAC, unsigned char,
        OVERRIDE_Q_O                    ,       //0x61BA        0x00            Q-branch DAC override value when DAC_SRC = 001 (0->127)
        OVERRIDE_I_O                    ,       //0x61BB        0x00            I-branch DAC override value when DAC_SRC = 001 (0-127)
        SOURCE                          ,       //0x61BC        0x00            The data source for the TX DAC is selected by DAC_SRC according to (0->7)
        ANALOG_TEST                     );      //0x61BD        0x00            Controls the analog test mode (0->63)      
      BRUNION_16x8(POWER_DOWN_OVERRIDE, ,       //0x61BE-0x61BF
        r0, r1,
        
        AAF_PD                          , 1,    //0             0               Antialiasing filter power-down signal when PD_OVERRIDE = 1
        TX_MIX_PD                       , 1,    //1             0               Transmit mixer power-down signal when PD_OVERRIDE = 1
        LNA_PD                          , 2,    //2-3           0               Low-noise amplifier power-down signal. Defines LNA and mixer PD modes
        DAC_PD                          , 1,    //4             0               Digital-to-analog converter power-down signal when PD_OVERRIDE = 1
        ADC_PD                          , 1,    //5             0               Analog-to-digital converter power-down signal when PD_OVERRIDE = 1
        CHP_PD                          , 1,    //6             0               Charge-pump power-down signal when PD_OVERRIDE = 1
        PRE_PD                          , 1,    //7             0               Prescaler power-down signal when PD_OVERRIDE = 1
        LODIV_PD                        , 1,    //0             0               LO power-down signal when PD_OVERRIDE = 1
        VCO_PD                          , 1,    //1             0               Voltage-controlled oscillator power-down signal when PD_OVERRIDE = 1
        PA_PD                           , 1,    //2             0               Power amplifier power-down signal when PD_OVERRIDE = 1
        PD_OVERRIDE                     , 1,    //3             0               Override enabling and disabling of various modules. For debug and testing only
        const _reserved                 , 4);
      unsigned char _reserved[0x61FA - 0x61C0];
      unsigned char TX_FILT_CFG;                //0x61FA        15              Sets TX anti-aliasing filter to appropriate bandwidth (0->15)
      unsigned char _reserved1;
    } AD_TEST_TUNING;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct
    {
      unsigned char _reserved[0x61C0 - 0x61A8];
      xRSTRUCT(PROG, unsigned char, r, 0, 23, ); //0x61C0:0x61D7                CSP Program
      unsigned char _reserved1[8];
      unsigned char CTRL;                       //0x61E0        0               CSP MCU control input (0->1)
      BUNION(STATUS, const unsigned char,       //0x61E1                        CSP Status Register
            PC                          , 5,    //0:4           0 0000          CSP program counter
            RUNNING                     , 1,    //6             0               1: CSP is running
            _reserved                   , 2);
      unsigned char X;                          //0x61E2        0x00            CSP X Register
      unsigned char Y;                          //0x61E3        0x00            CSP Y Register
      unsigned char Z;                          //0x61E4        0x00            CSP Z Register
      unsigned char T;                          //0x61E5        0xFF            CSP T Register
      unsigned char _reserved2[0x61FB - 0x61E5];
    } CSP;
    //----------------------------------------------------------------------------------------------------------------------------------------------------------
    struct
    {
      unsigned char _reserved[0x61EB - 0x61A8];
      BRUNION_24x8(MUX_CTRL, ,                  //0x61EB:0x61ED
        r0, r1, r2,
      
        RFC_OBS_MUX0                    , 6,    //0:5           0               Controls which observable signal from RF Core is to be muxed out to rfc_obs_sigs[0]
        RFC_OBS_POL0                    , 1,    //6             0               The signal chosen by RFC_OBS_MUX0 is XORed with this bit
        const _reserved                 , 1,
        RFC_OBS_MUX1                    , 6,    //0:5           0               Controls which observable signal from RF Core is to be muxed out to rfc_obs_sigs[1]
        RFC_OBS_POL1                    , 1,    //6             0               The signal chosen by RFC_OBS_MUX1 is XORed with this bit
        const _reserved1                , 1,
        RFC_OBS_MUX2                    , 6,    //0:5           0               Controls which observable signal from RF Core is to be muxed out to rfc_obs_sigs[2]
        RFC_OBS_POL2                    , 1,    //6             0               The signal chosen by RFC_OBS_MUX2 is XORed with this bit
        const _reserved2                , 1);
      unsigned char _reserved1[0x61FB - 0x61ED];
    } OBSERVABILITY_CTRL;
  };
} RADIO_TypeDef;
extern __root __no_init __xdata volatile RADIO_TypeDef RADIO;
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
SFR(RADIO_RFD, 0xD9);                           //              0x00            RF data
SFR(RADIO_RFST, 0xE1);                          //              0x00            RF command strobe
SFRB(RADIO_IRQ_FLAG0, 0xE9, ,                   //              0x00            Interrupt Flags
  ACT_UNUSED                            , 1,    //0             0               Reserved
  SFD                                   , 1,    //1             0               SFD has been received or transmitted
  FIFOP                                 , 1,    //2             0               The number of bytes in the RXFIFO is above the threshold
  SRC_MATCH_DONE                        , 1,    //3             0               Source matching complete
  SRC_MATCH_FOUND                       , 1,    //4             0               Source match found
  FRAME_ACCEPTED                        , 1,    //5             0               Frame has passed frame filtering
  RX_PKT_DONE                           , 1,    //6             0               A complete frame has been received
  RX_MASK_ZERO                          , 1);   //7             0               The RXENABLE register has gone from a nonzero state to an all-zero state
SFRB(RADIO_IRQ_FLAG1, 0x91, ,                   //              0x00            Interrupt Flags     
  TX_ACK_DONE                           , 1,    //0             0               An acknowledgment frame has been completely transmitted
  TX_DONE                               , 1,    //1             0               A complete frame has been transmitted
  RF_IDLE                               , 1,    //2             0               Radio state machine has entered the idle state
  CSP_MAN_INT                           , 1,    //3             0               Manual interrupt generated from CSP
  CSP_STOP                              , 1,    //4             0               CSP has stopped program execution
  CSP_WAIT                              , 1,    //5             0               Execution continued after a wait instruction in CSP
  _reserved                             , 2);
SFRB(RADIO_ERROR_FLAG, 0xBF, ,                  //              0x00            RF Error Interrupt Flags
  NLOCK                                 , 1,    //0             0               Frequency synthesizer failed to achieve lock after time-out, or lock is lost
  RX_ABO                                , 1,    //1             0               Reception of a frame was aborted
  RX_OVERF                              , 1,    //2             0               RXFIFO overflowed
  RX_UNDERF                             , 1,    //3             0               RXFIFO underflowed
  TX_OVERF                              , 1,    //4             0               TXFIFO overflowed
  TX_UNDERF                             , 1,    //5             0               TXFIFO underflowed
  STROBE_ERR                            , 1,    //6             0               A command strobe was issued at a time it could not be processed
  _reserved                             , 1);
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
//C condition
#define CSP_C_CCA_TRUE                  0x0
#define CSP_C_SFD_FOUND                 0x1
#define CSP_C_MCU_CTRL                  0x2
#define CSP_C_X_IS_ZERO                 0x4
#define CSP_C_Y_IS_ZERO                 0x5
#define CSP_C_Z_IS_ZERO                 0x6
#define CSP_C_RSSI_VALID                0x7
//S command strobe
#define CSP_S_NOP                       0x0
#define CSP_S_START                     0x1
#define CSP_S_STOP                      0x2
#define CSP_S_RX_ON                     0x3
#define CSP_S_RX_MASK_BIT_SET           0x4
#define CSP_S_RX_MASK_BIT_CLR           0x5
#define CSP_S_ACK                       0x6
#define CSP_S_ACK_PEND                  0x7
#define CSP_S_NACK                      0x8
#define CSP_S_TX_ON                     0x9
#define CSP_S_TX_ON_CCA                 0xA
#define CSP_S_SAMPLE_CCA                0xB
#define CSP_S_FLUSH_RX                  0xD
#define CSP_S_FLUSH_TX                  0xE
#define CSP_S_RF_OFF                    0xF
//==============================================================================================================================================================
#define CSP_CMD_SKIP(C, N, S)           (S<<4)|(N<<3)|C         //Skip S(0->7) instructions on condition C(N-not)
#define CSP_CMD_WAIT(W)                 0x80|W                  //Wait for W(0->31) MAC Timer overflows
#define CSP_CMD_REPEAT(C, N)            0xA0|(N<<3)|C           //If condition C is true(N-false), then jump last LABEL instruction
#define CSP_CMD_WAIT_EVENT1()           0xB8                    //Wait until MAC Timer event 1
#define CSP_CMD_WAIT_EVENT2()           0xB9                    //Wait until MAC Timer event 2
#define CSP_CMD_INTERRUPT()             0xBA                    //The interrupt IRQ_CSP_INT is asserted when this instruction is executed
#define CSP_CMD_LABEL()                 0xBB                    //Sets next instruction as start of loop
#define CSP_CMD_WAITX()                 0xBC                    //Wait for X MAC Timer overflows
#define CSP_CMD_RANDXY()                0xBD                    //Load random value into X
#define CSP_CMD_SETCMP1()               0xBE                    //Set the compare value of the MAC Timer to the current timer value
#define CSP_CMD_INCX()                  0xC0                    //Increment X
#define CSP_CMD_INCY()                  0xC1                    //Increment Y
#define CSP_CMD_INCZ()                  0xC2                    //Increment Z
#define CSP_CMD_DECX()                  0xC3                    //Decrement X
#define CSP_CMD_DECY()                  0xC4                    //Decrement Y
#define CSP_CMD_DECZ()                  0xC5                    //Decrement Z
#define CSP_CMD_INC_MAX_Y(M)            0xC8|M                  //Increment Y not greater than M(0->7)
#define CSP_CMD_STROBE(S)               0xD0|S                  //Execute command strobe S
#define CSP_CMD_IMME_STROBE(S)          0xE0|S                  //Execute command strobe S immediately
#define CSP_CMD_IMME_STROBE_CLEAR()     0xFF                    //Clear all command strobe immediately
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define RADIO_CSPWrite(Command)         RADIO_RFST = Command
//==============================================================================================================================================================
typedef struct
{
  struct
  {
    unsigned char Extend[8];
    unsigned short PAN_ID;
    unsigned short Short;
  } Address;
  RADIO_RX_CTRL_TypeDef RX_CTRL;
  unsigned char Channel;
  RADIO_INTERRUPT_ENABLE_TypeDef INTERRUPT_ENABLE;
} RadioInit_TypeDef;
void RADIO_Init(const RadioInit_TypeDef __code* RadioInit);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  FCF_TypeDef FCF;
  unsigned char SequenceNumber;
} RadioTX_TypeDef;
void RADIO_Send(const RadioTX_TypeDef* RadioTX, const AddressField_TypeDef* DstAddress, const unsigned char __gptr* Data, unsigned char Size);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

//==============================================================================================================================================================
//must declare
void RADIO_ERROR_Handle();                              //process in RADIO.ERROR.ISR
//{
//  if (RADIO_ERROR_FLAG.BITS.NLOCK               )       //Frequency synthesizer failed to achieve lock after time-out, or lock is lost
//  {}
//  if (RADIO_ERROR_FLAG.BITS.RX_ABO              )       //Reception of a frame was aborted
//  {}
//  if (RADIO_ERROR_FLAG.BITS.RX_OVERF            )       //RXFIFO overflowed
//  {}
//  if (RADIO_ERROR_FLAG.BITS.RX_UNDERF           )       //RXFIFO underflowed
//  {}
//  if (RADIO_ERROR_FLAG.BITS.TX_OVERF            )       //TXFIFO overflowed
//  {}
//  if (RADIO_ERROR_FLAG.BITS.TX_UNDERF           )       //TXFIFO underflowed
//  {}
//  if (RADIO_ERROR_FLAG.BITS.STROBE_ERR          )       //A command strobe was issued at a time it could not be processed
//  {}
//}
void RADIO_IRQ_Handle();                                //process in RADIO.IRQ.ISR
//{
//  if (RADIO_IRQ_FLAG0.BITS.ACT_UNUSED           )       //Reserved
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.SFD                  )       //SFD has been received or transmitted
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.FIFOP                )       //The number of bytes in the RXFIFO is above the threshold
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.SRC_MATCH_DONE       )       //Source matching complete
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.SRC_MATCH_FOUND      )       //Source match found
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.FRAME_ACCEPTED       )       //Frame has passed frame filtering
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.RX_PKT_DONE          )       //A complete frame has been received
//  {}
//  if (RADIO_IRQ_FLAG0.BITS.RX_MASK_ZERO         )       //The RXENABLE register has gone from a nonzero state to an all-zero state
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.TX_ACK_DONE          )       //An acknowledgment frame has been completely transmitted
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.TX_DONE              )       //A complete frame has been transmitted
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.RF_IDLE              )       //Radio state machine has entered the idle state
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.CSP_MAN_INT          )       //Manual interrupt generated from CSP
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.CSP_STOP             )       //CSP has stopped program execution
//  {}
//  if (RADIO_IRQ_FLAG1.BITS.CSP_WAIT             )       //Execution continued after a wait instruction in CSP
//  {}
//}

#endif