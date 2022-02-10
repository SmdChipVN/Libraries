#ifndef _USBP_ENUM_H_
#define _USBP_ENUM_H_

//                                      |       //Address       Default         Description
//==============================================================================================================================================================
//===========================================================       COMMON      ================================================================================
//==============================================================================================================================================================
//==========================================================       PID TYPE        =========================================================================
//typedef enum
//{
//  USB_PID_SYNC                          = 0x80,
//  USB_PID_OUT                           = 0xE1,
//  USB_PID_IN                            = 0x69,
//  USB_PID_SOF                           = 0xA5,
//  USB_PID_SETUP                         = 0x2D,
//  USB_PID_DATA0                         = 0xC3,
//  USB_PID_DATA1                         = 0x4B,
//  USB_PID_DATA2                         = 0x87,
//  USB_PID_MDATA                         = 0x0F,
//  USB_PID_ACK                           = 0xD2,
//  USB_PID_NACK                          = 0x5A, 
//  USB_PID_STALL                         = 0x1E,
//  USB_PID_NYET                          = 0x96,
//  USB_PID_PREMBLE                       = 0x3C,
//  USB_PID_ERR                           = 0x3C,
//  USB_PID_SPLIT                         = 0x78,
//  USB_PID_PING                          = 0xB4,
//} USB_PID;
//============================================================   ENDPOINT STATUS   =========================================================================
typedef enum
{
  USB_ENDPOINT_STATUS_DISABLED          = 0,
  USB_ENDPOINT_STATUS_STALL             = 1,
  USB_ENDPOINT_STATUS_NAK               = 2,
  USB_ENDPOINT_STATUS_VALID             = 3,
} USB_ENDPOINT_STATUS;
//============================================================    ENDPOINT TYPE    =========================================================================
typedef enum
{
  USB_ENDPOINT_TYPE_CONTROL             = 0,
  USB_ENDPOINT_TYPE_ISO                 = 1,
  USB_ENDPOINT_TYPE_BULK                = 2,
  USB_ENDPOINT_TYPE_INTERRUPT           = 3,
} USB_ENDPOINT_TYPE;
//================================================    ENDPOINT > SYNCHRONISATION TYPE   ===================================================================
typedef enum
{
  USB_SYNCHRONISATION_TYPE_NONE         = 0,
  USB_SYNCHRONISATION_TYPE_ASYNCHRONOUS = 1,
  USB_SYNCHRONISATION_TYPE_ADAPTIVE     = 2,
  USB_SYNCHRONISATION_TYPE_SYNCHRONOUS  = 3,
} USB_SYNCHRONISATION_TYPE;
//================================================        ENDPOINT > USAGE TYPE         ==================================================================
typedef enum
{
  USB_USAGE_TYPE_DATA_ENDPOINT                          = 0,
  USB_USAGE_TYPE_FEEDBACK_ENDPOINT                      = 1,
  USB_USAGE_TYPE_EXPLICIT_FEEDBACK_DATA_ENDPOINT        = 2,
} USB_USAGE_TYPE;
//==============================================================================================================================================================
//=========================================================       CLASS CODE      ==============================================================================
//==============================================================================================================================================================
//                                              //SubClass      Protocol        Meaning
typedef enum
{
  USB_CLASS_DEVICE                      = 0x00, //0x00          0x00            Use class code info from Interface Descriptors
  USB_CLASS_AUDIO                       = 0x01, //0x--          0x--            Audio device
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_CDC                         = 0x02, //0x01          0x--            Direct Line Control Model
                                                //0x02          0x--            Abstract Control Model
                                                //0x03          0x--            Telephone Control Model
                                                //0x04          0x--            Multi-Channel Control Model
                                                //0x05          0x--            CAPI Control Model
                                                //0x06          0x--            Ethernet Networking Control Model
                                                //0x07          0x--            ATM Networking Control Model
                                                //0x08          0x--            Wireless Handset Control Model
                                                //0x09          0x--            Device Management
                                                //0x0A          0x--            Mobile Direct Line Model
                                                //0x0B          0x--            OBEX
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_HID                         = 0x03, //0x--          0x--            Human Interface Device
  USB_CLASS_PHYSICAL                    = 0x05, //0x--          0x--            Physical device class
  USB_CLASS_IMAGE                       = 0x06, //0x01          0x01            Still Imaging device
  USB_CLASS_PRINTER                     = 0x07, //0x--          0x--            Printer device
  USB_CLASS_MASS_STORAGE                = 0x08, //0x--          0x--            Mass Storage device
                                                //0x00                          SCSI command set not reported
                                                //0x01                          RBC
                                                //0x02                          MMC-5 (ATAPI)
                                                //0x03                          Obsolete
                                                //0x04                          UFI
                                                //0x05                          Obsolete
                                                //0x06                          SCSI transparent command set
                                                //0x07                          LSD FS
                                                //0x08                          IEEE 1667
                                                //0x09:FE                       Reserved
                                                //0xFF                          Specific to device vendor
                                                //              0x00            CBI (with command completion interrupt)
                                                //              0x01            CBI (with no command completion interrupt)
                                                //              0x02            Obsolete
                                                //              0x03:4F         Reserved
                                                //              0x50            BBB
                                                //              0x51:61         Reserved
                                                //              0x62            UAS
                                                //              0x63:FE         Reserved
                                                //              0xFF             Specific to device vendor
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_HUB                         = 0x09, //0x00          0x00            Full speed Hub
                                                //0x00          0x01            Hi-speed hub with single TT
                                                //0x00          0x02            Hi-speed hub with multiple TTs
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_CDC_DATA                    = 0x0A, //0x--          0x--            CDC data device
  USB_CLASS_SMART_CARD                  = 0x0B, //0x--          0x--            Smart Card device
  USB_CLASS_CONTENT_SECURITY            = 0x0D, //0x00          0x00            Content Security device
  USB_CLASS_VIDEO                       = 0x0E, //0x--          0x--            Video device
  USB_CLASS_PERSONAL_HEALTHCARE         = 0x0F, //0x--          0x--            Personal Healthcare device
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_AV_DEVICE                   = 0x10, //0x01          0x00            Audio/Video Device – AVControl Interface
                                                //0x02          0x00            Audio/Video Device – AVData Video Streaming Interface
                                                //0x03          0x00            Audio/Video Device – AVData Audio Streaming Interface
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_BILL_BOARD                  = 0x11, //0x00          0x00            Billboard Device
  USB_CLASS_TYPE_C                      = 0x12, //0x00          0x00            USB Type-C Bridge Device
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_DIAGNOSTIC                  = 0xDC, //0x01          0x01            USB2 Compliance Device
                                                //0x02          0x00            Debug Target vendor defined
                                                //0x02          0x01            GNU Remote Debug Command Set
                                                //0x03          0x01            Vendor defined Trace protocol on DbC
                                                //0x04          0x01            Vendor defined Dfx protocol on DbC
                                                //0x05          0x00            Vendor defined Trace protocol over General Purpose (GP) endpoint on DvC
                                                //0x05          0x01            GNU Protocol protocol over General Purpose (GP) endpoint on DvC
                                                //0x06          0x01            Vendor defined Dfx protocol on DvC
                                                //0x07          0x01            Vendor defined Trace protocol on DvC  
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_WIRELESS                    = 0xE0, //0x01          0x01            Bluetooth Programming Interface
                                                //0x01          0x02            UWB Radio Control Interface
                                                //0x01          0x03            Remote NDIS
                                                //0x01          0x04            Bluetooth AMP Controller
                                                //0x02          0x01            Host Wire Adapter Control/Data interface
                                                //0x02          0x02            Device Wire Adapter Control/Data interface
                                                //0x02          0x03            Device Wire Adapter Isochronous interface
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_MISCELLANEOUS               = 0xEF, //0x--          0x--            google search "nkju` vaj~ ka daj', po' aj ljet ke dc" for more information
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_APPLICATION                 = 0xFE, //0x01          0x01            Device Firmware Upgrade
                                                //0x02          0x00            IRDA Bridge device
                                                //0x03          0x00            USB Test and Measurement Device
                                                //0x03          0x01            USB Test and Measurement Device conforming to the USBTMC USB488 Subclass
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  USB_CLASS_VENDER                      = 0xFF, //0x--          0x--            Vendor specific
} USB_CLASS;
//==============================================================================================================================================================
//=======================================================       HOST TO DEVICE      ============================================================================
//==============================================================================================================================================================
//======================================================      RECIPIENT TYPE          ======================================================================
typedef enum
{
  USB_RECIPIENT_DEVICE                  = 0,
  USB_RECIPIENT_INTERFACE               = 1,
  USB_RECIPIENT_ENDPOINT                = 2,
  USB_RECIPIENT_USER,
} USB_RECIPIENT;
//======================================================        REQUEST TYPE          ======================================================================
typedef enum
{
  USB_REQUEST_TYPE_STANDARD             = 0,
  USB_REQUEST_TYPE_CLASS                = 1,
  USB_REQUEST_TYPE_VENDER               = 2,
} USB_REQUEST_TYPE;
//===========================================================    DEVICE REQUEST   ==========================================================================
//=========================================================    STANDARD     ============================================================================
typedef enum
{
  USB_DEVICE_STANDARD_REQUEST_GET_STATUS                = 0x00,
  USB_DEVICE_STANDARD_REQUEST_CLEAR_FEATURE             = 0x01,
  USB_DEVICE_STANDARD_REQUEST_SET_FEATURE               = 0x03,
  USB_DEVICE_STANDARD_REQUEST_SET_ADDRESS               = 0x05,
  USB_DEVICE_STANDARD_REQUEST_GET_DESCRIPTOR            = 0x06,
  USB_DEVICE_STANDARD_REQUEST_SET_DESCRIPTOR            = 0x07,
  USB_DEVICE_STANDARD_REQUEST_GET_CONFIGURATION         = 0x08,
  USB_DEVICE_STANDARD_REQUEST_SET_CONFIGURATION         = 0x09,
} USB_DEVICE_STANDARD_REQUEST;
//=======================================================    DESCRIPTOR     ========================================================================
typedef enum
{
  USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE                 = 0x01,
  USB_DEVICE_STANDARD_DESCRIPTOR_CONFIGURATION          = 0x02,
  USB_DEVICE_STANDARD_DESCRIPTOR_STRING                 = 0x03,
  USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE              = 0x04,
  USB_DEVICE_STANDARD_DESCRIPTOR_ENDPOINT               = 0x05,
  USB_DEVICE_STANDARD_DESCRIPTOR_DEVICE_QUALIFIER       = 0x06,
  USB_DEVICE_STANDARD_DESCRIPTOR_OTHER_SPEED            = 0x07,
  USB_DEVICE_STANDARD_DESCRIPTOR_INTERFACE_POWER        = 0x08,
  USB_DEVICE_STANDARD_DESCRIPTOR_OTG                    = 0x09,
} USB_DEVICE_STANDARD_DESCRIPTOR;
//=========================================================    CLASS       =============================================================================
typedef enum
{
  USB_DEVICE_CLASS_REQUEST_UN_DEFINE                    = 0x00,
} USB_DEVICE_CLASS_REQUEST;
//=========================================================    VENDER       ============================================================================
typedef enum
{
  USB_DEVICE_VENDER_REQUEST_UN_DEFINE                   = 0x00,
} USB_DEVICE_VENDER_REQUEST;
//=========================================================    INTERFACE REQUEST   =========================================================================
//=========================================================    STANDARD     ============================================================================
typedef enum
{
  USB_INTERFACE_STANDARD_REQUEST_GET_STATUS             = 0x00,
  USB_INTERFACE_STANDARD_REQUEST_CLEAR_FEATURE          = 0x01,
  USB_INTERFACE_STANDARD_REQUEST_SET_FEATURE            = 0x03,
  USB_INTERFACE_STANDARD_REQUEST_GET_INTERFACE          = 0x0A,
  USB_INTERFACE_STANDARD_REQUEST_SET_INTERFACE          = 0x11,
} USB_INTERFACE_STANDARD_REQUEST;
//=========================================================    CLASS       =============================================================================
typedef enum
{
  USB_INTERFACE_CLASS_REQUEST_UN_DEFINE                 = 0x00,
} USB_INTERFACE_CLASS_REQUEST;
//=========================================================    VENDER       ============================================================================
typedef enum
{
  USB_INTERFACE_VENDER_REQUEST_UN_DEFINE                = 0x00,
} USB_INTERFACE_VENDER_REQUEST;
//=========================================================    ENDPOINT REQUEST    =========================================================================
//=========================================================    STANDARD     ============================================================================
typedef enum
{
  USB_ENDPOINT_STANDARD_REQUEST_GET_STATUS              = 0x00,
  USB_ENDPOINT_STANDARD_REQUEST_CLEAR_FEATURE           = 0x01,
  USB_ENDPOINT_STANDARD_REQUEST_SET_FEATURE             = 0x03,
  USB_ENDPOINT_STANDARD_REQUEST_SYN_FRAME               = 0x12,
} USB_ENDPOINT_STANDARD_REQUEST;
//=========================================================    CLASS       =============================================================================
typedef enum
{
  USB_ENDPOINT_CLASS_REQUEST_UN_DEFINE                  = 0x00,
} USB_ENDPOINT_CLASS_REQUEST;
//=========================================================    VENDER       ============================================================================
typedef enum
{
  USB_ENDPOINT_VENDER_REQUEST_UN_DEFINE                 = 0x00,
} USB_ENDPOINT_VENDER_REQUEST;

#endif