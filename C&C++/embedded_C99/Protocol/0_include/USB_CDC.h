#ifndef _USBP_CDC_H_
#define _USBP_CDC_H_

#include <USBP.h>
//==============================================================================================================================================================
//====================================================          Host to Device          ========================================================================
//==============================================================================================================================================================
typedef enum
{
  USB_CDC_INTERFACE_CLASS_REQUEST_SET_LINE_CODING               = 0x20,
  USB_CDC_INTERFACE_CLASS_REQUEST_GET_LINE_CODING               = 0x21,
  USB_CDC_INTERFACE_CLASS_REQUEST_SET_CONTROL_LINE_STATE        = 0x22,
} USB_CDC_INTERFACE_CLASS_REQUEST;
__packed typedef struct
{
  union
  {
    unsigned char REG;
    BSTRUCT(BITS, ,
          USB_RECIPIENT Recipient       , 5,
          USB_REQUEST_TYPE Type         , 2,
          unsigned char IsDevToHost     , 1);
  } bmRequestType;
  union
  {
//    __packed union Standard
//    {
//      USB_CDC_INTERFACE_STANDARD_REQUEST UN_DEFINE;
//    };
    struct
    {
      USB_CDC_INTERFACE_CLASS_REQUEST bRequest;
      __packed union
      {
        RSTRUCT(SET_LINE_CODING, unsigned short, _Reserved, Interface, Length);
        RSTRUCT(GET_LINE_CODING, unsigned short, _Reserved, Interface, MaxLength);
        struct
        {
          BUNION(CSB, unsigned short,
                DTE                         , 1,
                CarrierIsActivate           , 1,
                _Reserved                   , 14);
          unsigned short Interface;
          unsigned short _Reserved;
        } SET_CONTROL_LINE_STATE;
      };
    } Class;    
  };
//    __packed union Vender
//    {
//      USB_CDC_INTERFACE_VENDER_REQUEST UN_DEFINE;
//    };
} USB_CDC_REQUEST_TypeDef;
//==============================================================================================================================================================
//===========================================================          Device to Host          =================================================================
//==============================================================================================================================================================
typedef enum
{
  USB_CDC_DESCRIPTOR_CS_INTERFACE       = 0x24,
  USB_CDC_DESCRIPTOR_CS_ENDPOINT        = 0x25,
} USB_CDC_DESCRIPTOR;
typedef enum
{
  USB_CDC_FUNCTIONAL_DESCRIPTOR_HEADER                  = 0x00, //Header functional descriptor subtype
  USB_CDC_FUNCTIONAL_DESCRIPTOR_CALL                    = 0x01, //Call Management Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_ABSTRACT_CONTROL        = 0x02, //Abstract Control Management Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_DIRECT_LINE             = 0x03, //Direct Line Management Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_TELEPHONE_RINGER        = 0x04, //Telephone Ringer Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_TC_LSRC                 = 0x05, //Telephone Call and Line State Reporting Capabilities Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_UNION                   = 0x06, //Union Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_COUNTRY_SELECTION       = 0x07, //Country Selection Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_TOM                     = 0x08, //Telephone Operational Modes Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_USB_TERMINAL            = 0x09, //USB Terminal Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_NETWORK_CHANNEL         = 0x0A, //Network Channel Terminal Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_PROTOCOL_UNIT           = 0x0B, //Protocol Unit Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_EXTENSION_UNIT          = 0x0C, //Extension Unit Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_MULTI_CHANNEL           = 0x0D, //Multi-Channel Management Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_CAPI_CONTROL            = 0x0E, //CAPI Control Management Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_ETHERNET                = 0x0F, //Ethernet Networking Functional Descriptor
  USB_CDC_FUNCTIONAL_DESCRIPTOR_ATM                     = 0x10, //ATM Networking Functional Descriptor
} USB_CDC_FUNCTIONAL_DESCRIPTOR;
typedef enum
{
  USB_CDC_STOP_BITS_1          = 0,
  USB_CDC_STOP_BITS_1P5        = 1,
  USB_CDC_STOP_BITS_2          = 2,
} USB_CDC_STOP_BITS;
typedef enum
{
  USB_CDC_PARITY_TYPE_NONE     = 0,
  USB_CDC_PARITY_TYPE_ODD      = 1,
  USB_CDC_PARITY_TYPE_EVEN     = 2,
  USB_CDC_PARITY_TYPE_MARK     = 3,
  USB_CDC_PARITY_TYPE_SPACE    = 4,
} USB_CDC_PARITY_TYPE;
typedef struct
{
    union
    {
      struct
      {        
        unsigned char bFunctionLength;
        USB_CDC_DESCRIPTOR bDescriptorType;
        USB_CDC_FUNCTIONAL_DESCRIPTOR bDescriptorSubtype;
        union
        {
          struct
          {
            unsigned short bcdCDC;                      //BCD Release version of the CDC specification
          } HEADER;
          struct
          {
            BUNION(bmCapabilities, unsigned char,
                  IsHandlesCallItsSelf          , 1,    //Device handles call management itself
                  CanSendCall                   , 1,    //Device can send/receive call management information over a Data Class interface
                  _Reserved                     , 6);
            unsigned char bDataInterface;               //Interface number of Data Class interface optionally used for call management
          } CALL;
          struct
          {
            BUNION(bmCapabilities, unsigned char,
                  SupportFeatureCommand         , 1,    //Device supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature
                  SupportLineCommand            , 1,    //Device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State
                  SupportBreak                  , 1,    //Device supports the request Send_Break
                  SupportNotiNetwork            , 1,    // Device supports the notification Network_Connection
                  _Reserved                     , 4);   //The capabilities that this configuration supports
          } ABSTRACT_CONTROL;
          struct
          {
            BUNION(bmCapabilities, unsigned char,
                  SupportPulse                  , 1,    //Device supports the request combination of Pulse_Setup, Send_Pulse, and Set_Pulse_Time
                  SupportAUX                    , 1,    //Device supports the request combination of Set_Aux_Line_State, Ring_Aux_Jack, and notification Aux_Jack_Hook_State
                  RequiresExtraPulse            , 1,    //Device requires extra Pulse_Setup request during pulse dialing sequence to disengage holding circuit
                  _Reserved                     , 5);
          } DIRECT_LINE;
          struct
          {
            unsigned char bRingerVolSteps;              //Number of discrete steps in volume supported by the ringer
            unsigned char bNumRingerPatterns;           //Number of ringer patterns supported, values of 1 to 255 with a value of 0 being reserved for future use
          } TELEPHONE_RINGER;
//          struct
//          {
//            BUNION(bmCapabilities, unsigned char,
//                  
//          } TC_LSRC;
          struct
          {
            unsigned char bMasterInterface;             //The interface number of the Communication or Data Class interface, designated as the master or controlling interface for the union
            unsigned char bSlaveInterface[8];           // Interface number of first slave or associated interface in the union
          } UNION_;
          struct
          {
            unsigned char iCountryCodeRelDate;          //Index of a string giving the release date for the implemented ISO 3166 Country Codes
            unsigned short wCountryCode[8];             //Country code in hexadecimal format as defined in ISO 3166
          } COUNTRY_SELECTION;
          struct
          {
            BUNION(bmCapabilities, unsigned char,
                  SupportsSimpleMode            , 1,
                  SupportsStandaloneMode        , 1,
                  SupportsComputerCentricMode   , 1,
                  _Reserved                     , 5);
          } TOM;
          struct
          {
            unsigned char bEntityId;                    //Constant uniquely identifying the Terminal
            unsigned char bInInterfaceNo;               //The input interface number of the associated USB interface
            unsigned char bOutInterfaceNo;              //The output interface number of the associated USB interface
            unsigned char IsWrapperUsed;
            unsigned char bChildId[8];                  //ID of lower Terminal or Unit to which this Terminal is connected
          } USB_TERMINAL;
          struct
          {
            unsigned char bEntityId;                    //Constant uniquely identifying the Terminal
            unsigned char iName;                        //Index of string descriptor, describing the name of the Network Channel Terminal
            unsigned char bChannelIndex;                //The channel index of the associated network channel according to indexing rules below
            unsigned char bPhysicalInterface;           //Type of physical interface
          } NETWORK_CHANNEL;
          struct
          {
            unsigned char bEntityId;                    //Constant uniquely identifying the Unit
            unsigned char bProtocol;                    // Protocol code
            unsigned char bChildId[8];                  // ID of lower Terminal or Unit to which this Terminal is connected
          } PROTOCOL_UNIT;
          struct
          {
            unsigned char bEntityId;                    //Vendor specific code identifying the Extension Unit
            unsigned char bExtensionCode;               //Index of string descriptor, describing the name of the Extension Unit
            unsigned char iName;                        //ID of lower Terminal or Unit to which this Terminal is connected
            unsigned char bChildId[8];
          } EXTENSION_UNIT;
//          struct
//          {
//            BUNION(bmCapabilities, unsigned char,
//                  
//          } MULTI_CHANNEL;
//          struct
//          {
//            BUNION(bmCapabilities, unsigned char,
//                  
//          } CAPI_CONTROL;
          struct
          {
            unsigned char iMACAddress;
            BUNION(bmEthernetStatistics, unsigned long,
                  XMIT_OK                       , 1,
                  RVC_OK                        , 1,
                  XMIT_ERROR                    , 1,
                  RCV_ERROR                     , 1,
                  RCV_NO_BUFFER                 , 1,
                  DIRECTED_BYTES_XMIT           , 1,
                  DIRECTED_FRAMES_XMIT          , 1,
                  MULTICAST_BYTES_XMIT          , 1,
                  MULTICAST_FRAMES_XMIT         , 1,
                  BROADCAST_BYTES_XMIT          , 1,
                  BROADCAST_FRAMES_XMIT         , 1,
                  DIRECTED_BYTES_RCV            , 1,
                  DIRECTED_FRAMES_RCV           , 1,
                  MULTICAST_BYTES_RCV           , 1,
                  MULTICAST_FRAMES_RCV          , 1,
                  BROADCAST_BYTES_RCV           , 1,
                  BROADCAST_FRAMES_RCV          , 1,
                  RCV_CRC_ERROR                 , 1,
                  TRANSMIT_QUEUE_LENGTH         , 1,
                  RCV_ERROR_ALIGNMENT           , 1,
                  XMIT_ONE_COLLISION            , 1,
                  XMIT_MORE_COLLISIONS          , 1,
                  XMIT_DEFERRED                 , 1,
                  XMIT_MAX_COLLISIONS           , 1,
                  RCV_OVERRUN                   , 1,
                  XMIT_UNDERRUN                 , 1,
                  XMIT_HEARTBEAT_FAILURE        , 1,
                  XMIT_TIMES_CRS_LOST           , 1,
                  XMIT_LATE_COLLISIONS          , 1,
                  _Reserved                     , 3);
            unsigned short wMaxSegmentSize;             //The maximum segment size that the Ethernet device is capable of supporting
            BUNION(wNumberMCFilters, unsigned short,                  
                  IndicatesNumber               , 15
                  /*,---------------------------*/);
            unsigned char bNumberPowerFilters;          //Contains the number of pattern filters that are available for causing wake-up of the host
          } ETHERNET;
          struct
          {
            unsigned char iEndSystemIdentifier;         //Index of string descriptor
            BUNION(bmDataCapabilities, unsigned char,
                  _Reserved                     , 1
                  /*,---------------------------*/);
            BUNION(bmATMDeviceStatistics, unsigned char,
                  /*---------------------------,*/
                  _Reserved                     , 2);
            unsigned short wType2MaxSegmentSize;        //The maximum segment size that the Type 2 device is capable of supporting
            unsigned short wType3MaxSegmentSize;        //The maximum segment size that the Type 3 device is capable of supporting
            unsigned short wMaxVC;                      //The maximum number of simultaneous virtual circuits the device is capable of supporting (Type 3 only)
          } ATM;
        };
      } GET_DESCRIPTOR;
    } Standard;
    union
    {
      struct
      {
        unsigned long dwDTERate;
        USB_CDC_STOP_BITS bStopBits;
        USB_CDC_PARITY_TYPE bParityType;
        unsigned char bDataBits;                        //5, 6, 7, 8, 16
      } GET_LINE_CODING;
    } Class;
//    union
//    {
//      
//    } Vender;
} USB_CDC_RESPOND_TypeDef;
//==============================================================================================================================================================
//==============================================================              Support             ==============================================================
//==============================================================================================================================================================
typedef enum
{
  USB_CDC_REQUEST_NULL                  = 0,
  USB_CDC_REQUEST_DATA_IN               = 1,
  USB_CDC_REQUEST_DATA_OUT              = 2,
  USB_CDC_REQUEST_SET_LINE_CODING       = 3,
} USB_CDC_STATUS;
typedef struct
{
  struct
  {
    unsigned long dwDTERate;
    USB_CDC_STOP_BITS bStopBits;
    USB_CDC_PARITY_TYPE bParityType;
    unsigned char bDataBits;                      //5, 6, 7, 8, 16
  } Info;
  USB_CDC_STATUS Request;
  unsigned char PortState;
  BUNION(Event, unsigned char,
    ChangeState                         , 1,
    ChangeInfo                          , 1,
    _reserved                           , 6);
} USB_CDC_Manager_TypeDef;
extern __no_init USB_CDC_Manager_TypeDef USB_CDC_Manager;
//==============================================================================================================================================================
//=========================================================        User must declare         ===================================================================
//==============================================================================================================================================================
/*
  +) return:
    -if in receiving have sending data by: return false;
    -other: return true;
*/
reg8 USB_CDC_Received(reg8 EndpointIndex, const unsigned char* Data, reg16 Length);
//==============================================================================================================================================================
//===========================================================        Using function         ====================================================================
//==============================================================================================================================================================
void USB_CDC_Init(void);

#endif