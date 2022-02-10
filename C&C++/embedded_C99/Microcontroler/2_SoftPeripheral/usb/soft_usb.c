//#include <config.h>
//#include <soft_usb.h>
//
//#define SYNC                                    0x80
/***********************    PID      ***********************/
typedef enum
{
  PID_OUT               = 0xE1,
  PID_IN                = 0x69,
  PID_SOF               = 0xA5,
  PID_SETUP             = 0x2D,
  PID_DATA0             = 0xC3,
  PID_DATA1             = 0x4B,
  PID_DATA2             = 0x87,
  PID_MDATA             = 0x0F,
  PID_ACK               = 0xD2,
  PID_NACK              = 0x5A, 
  PID_STALL             = 0x1E,
  PID_NYET              = 0x96,
  PID_PREMBLE           = 0x3C,
  PID_ERR               = 0x3C,
  PID_SPLIT             = 0x78,
  PID_PING              = 0xB4,
} PID;
/***********************    PID      ***********************/
/***********************  bRequest   ***********************/
typedef enum
{
  GET_STATUS            = 0x00,         // Standard Device Request - GET STATUS
  CLEAR_FEATURE         = 0x01,         // Standard Device Request - CLEAR FEATURE
  SET_FEATURE           = 0x03,         // Standard Device Request - SET FEATURE
  SET_ADDRESS           = 0x05,         // Standard Device Request - SET ADDRESS
  GET_DESCRIPTOR        = 0x06,         // Standard Device Request - GET DESCRIPTOR
  SET_DESCRIPTOR        = 0x07,         // Standard Device Request - SET DESCRIPTOR
  GET_CONFIGURATION     = 0x08,         // Standard Device Request - GET CONFIGURATION
  SET_CONFIGURATION     = 0x09,         // Standard Device Request - SET CONFIGURATION
  GET_INTERFACE         = 0x0A,         // Standard Device Request - GET INTERFACE
  SET_INTERFACE         = 0x0B,         // Standard Device Request - SET INTERFACE
  SYNCH_FRAME           = 0x0C,         // Standard Device Request - SYNCH FRAME
} BREQUEST;
/***********************  bRequest   ***********************/
/******************** Descriptor Type  *********************/
typedef enum
{
  DEVICE                = 0x0001,       // bDescriptorType for a Device Descriptor.
  CONFIGURATION         = 0x0002,       // bDescriptorType for a Configuration Descriptor.
  STRING                = 0x0003,       // bDescriptorType for a String Descriptor.
  INTERFACE             = 0x0004,       // bDescriptorType for an Interface Descriptor.
  ENDPOINT              = 0x0005,       // bDescriptorType for an Endpoint Descriptor.
  DEVICE_QUALIFIER      = 0x0006,       // bDescriptorType for a Device Qualifier.
  OTHER_SPEED           = 0x0007,       // bDescriptorType for a Other Speed Configuration.
  INTERFACE_POWER       = 0x0008,       // bDescriptorType for Interface Power.
  OTG                   = 0x0009,       // bDescriptorType for an OTG Descriptor.
  HID                   = 0x0021,
} DESCRIPTOR;
/******************** Descriptor Type  *********************/
typedef struct
{
  PID PID;
  struct
  {
    unsigned short Address      : 7;
    unsigned short Endpoint     : 4;
    unsigned short CRC          : 5;
  };
} Token_TypeDef;

typedef struct
{
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char Receiver                    : 4;                            //0: Device; 1: Interface; 2: Endpoint; 3: Other
      unsigned char Type                        : 3;                            //0: Standard; 1: Class; 2: Vendor
      unsigned char Direction                   : 1;                            //0: Host to Device; 1: Device to Host
    } BITS;
  } bmRequestType;
  struct
  {
    BREQUEST Type;
    union
    {
      struct
      {
        unsigned char _Reserved[7];
      } GET_STATUS;
      struct
      {
        unsigned char _Reserved;
        unsigned short FeatureSelector;
        unsigned char _Reserved1[4];
      } CLEAR_FEATURE;
      struct
      {
        unsigned char _Reserved;
        unsigned short FeatureSelector;
        unsigned char _Reserved1[4];
      } SET_FEATURE;
      struct
      {
        unsigned char _Reserved;
        unsigned short DeviceAddress;
        unsigned char _Reserved1[4];
      } SET_ADDRESS;
      struct
      {
        unsigned char _Reserved;
        DESCRIPTOR Type;
        unsigned short LanguageID;
        unsigned short DescriptorLength;
      } GET_DESCRIPTOR;
      struct
      {
        unsigned char _Reserved;
        DESCRIPTOR Type;
        unsigned short LanguageID;
        unsigned short DescriptorLength;
      } SET_DESCRIPTOR;    
      struct
      {
        unsigned char _Reserved[7];
      } GET_CONFIGURATION;
      struct
      {
        unsigned char _Reserved;
        unsigned short ConfigurationValue;
        unsigned char _Reserved1[4];
      } SET_CONFIGURATION;
      struct
      {
        unsigned char _Reserved[3];
        unsigned short Interface;
        unsigned char _Reserved1[2];
      } GET_INTERFACE;
      struct
      {
        unsigned char _Reserved;
        unsigned short AlternativeSetting;
        unsigned short Interface;
        unsigned char _Reserved1[2];
      } SET_INTERFACE;
      struct
      {
        unsigned char _Reserved[7];
      } SYNCH_FRAME;
    };
  } bRequest;
} SetupPacket_TypeDef;

typedef enum
{
  IDLE                  = 0,
  
  SETUP_PROCESS         = 1,
  SETUP_COMPLETE        = 2,
  
  DATA_PREPARE          = 3,
  DATA_READY            = 4,
} MAIN_STATUS;
typedef enum
{
  READY                 = 0,
  WAIT_SETUP_DATA       = 1,
  WAIT_DATA             = 2,
  WAIT_ACK              = 3,
} PACKET_STATUS;
typedef struct
{
  unsigned char* Data;
  unsigned char Index;
  unsigned char Length;
  unsigned char PacketLength;
} Buffer_TypeDef;
typedef struct
{
  struct
  {
    unsigned char Process       : 1;
    MAIN_STATUS Main            : 5;
    PACKET_STATUS Packet        : 2;
  } Status;
  Buffer_TypeDef In;
  Buffer_TypeDef Out;
  unsigned char Backup[2];
} SUSB_TypeDef;
typedef struct
{
  void (*Ack)(SUSB_TypeDef* SUSB, unsigned char ACK);
  void (*Send)(SUSB_TypeDef* SUSB);
} SUSBFunction_TypeDef;

static void usb_calc_crc16(SUSB_TypeDef* SUSB)
{
  SUSB->Out.PacketLength = 8;
  if (SUSB->Out.Length < 8)
    SUSB->Out.PacketLength = SUSB->Out.Length;
  unsigned char length = SUSB->Out.PacketLength;
  unsigned short crc = 0xFFFF;
  unsigned char index = 2;
  SUSB->Backup[0] = SUSB->Out.Data[SUSB->Out.Index + length]; SUSB->Backup[1] = SUSB->Out.Data[SUSB->Out.Index + length + 1];
  while (length--)
  {
    crc ^= SUSB->Out.Data[index++];
    for (unsigned char i = 8; i--;)
    {
      if (crc & 0x01)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
  crc = ~crc;
  SUSB->Out.Data[index++] = (unsigned char)crc;
  SUSB->Out.Data[index] = (unsigned char)(crc >> 8);
}

void SUSB_Process(SUSBFunction_TypeDef* SUSBFunction, SUSB_TypeDef* SUSB)
{
  switch (SUSB->Status.Packet)
  {
  case READY:
    switch (((Token_TypeDef*)SUSB->In.Data)->PID)
    {
    case PID_SETUP:
      SUSB->Status.Packet = WAIT_SETUP_DATA;
      break;
    case PID_IN:
      if (SUSB->Status.Main == DATA_READY)
      {
        SUSB->Status.Packet = WAIT_ACK;
        SUSBFunction->Send(SUSB);
        SUSB->Out.Data[SUSB->Out.Index + SUSB->Out.PacketLength] = SUSB->Backup[0]; SUSB->Out.Data[SUSB->Out.Index + SUSB->Out.PacketLength + 1] = SUSB->Backup[1];
      }
      else SUSBFunction->Ack(SUSB, 0);          //inner interrupt
      break;
    case PID_OUT:
      SUSB->Status.Packet = WAIT_DATA;
      break;
    }
    break;
  case WAIT_SETUP_DATA:
    SUSBFunction->Ack(SUSB, 1);
    SUSB->Status.Packet = READY;
    
    if (((SetupPacket_TypeDef*)&SUSB->In.Data[1])->bmRequestType.BITS.Direction)
    {
      SUSB->Status.Main = DATA_PREPARE;
      switch (((SetupPacket_TypeDef*)&SUSB->In.Data[1])->bRequest.Type)
      {
        case GET_STATUS:
          //prepare status
          break;
        case GET_DESCRIPTOR:
          //prepare descriptor
          break;
        case GET_CONFIGURATION:
          //prepare config
          break;
        case GET_INTERFACE:
          //prepare interface
          break;
      }
      SUSB->Status.Main = DATA_READY;
    }
    else
    {
      SUSB->Status.Main = SETUP_PROCESS;
      switch (((SetupPacket_TypeDef*)&SUSB->In.Data[1])->bRequest.Type)
      {
        case CLEAR_FEATURE:
          //clear feature
          break;
        case SET_FEATURE:
          //set feature
          break;
        case SET_ADDRESS:
          //set address
          break;
        case SET_DESCRIPTOR:
          //set descriptor
          break;
        case SET_CONFIGURATION:
          //set config
          break;
        case SET_INTERFACE:
          //set interface
          break;
        case SYNCH_FRAME:
          //synch frame
          break;
      }
      SUSB->Out.Length = 0;
      SUSB->Out.Data[0] = 0; SUSB->Out.Data[1] = 0;
      SUSB->Status.Main = DATA_READY;
    }    
    break;
  case WAIT_DATA:
    
    
//    SUSBFunction->Ack(SUSB, 1);
//    SUSB->Status.Packet = READY;
    
    
    
    break;
  case WAIT_ACK:
    SUSB->Status.Packet = READY;    
    switch (SUSB->Status.Main)
    {
    case DATA_READY:
      if (SUSB->In.Data[0] == PID_ACK)
      {
        SUSB->Out.Length -= SUSB->Out.PacketLength;
        SUSB->Out.Index += SUSB->Out.PacketLength;
      }      
      if (!SUSB->Out.Length)
        SUSB->Status.Main = IDLE;
      break;
    }
    break;
  }  
}