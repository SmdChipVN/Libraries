#ifndef _USB_MASS_SCSI_H_
#define _USB_MASS_SCSI_H_

#include <common.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef enum
{
  SCSI_COMMAND_FORMAT_UNIT              = 0x04,
  SCSI_COMMAND_INQUIRY                  = 0x12,
  SCSI_COMMAND_MODE_SELECT6             = 0x15,
  SCSI_COMMAND_MODE_SELECT10            = 0x55,
  SCSI_COMMAND_MODE_SENSE6              = 0x1A,
  SCSI_COMMAND_MODE_SENSE10             = 0x5A,
  SCSI_COMMAND_ALLOW_MEDIUM_REMOVAL     = 0x1E,
  SCSI_COMMAND_READ6                    = 0x08,
  SCSI_COMMAND_READ10                   = 0x28,
  SCSI_COMMAND_READ12                   = 0xA8,
  SCSI_COMMAND_READ16                   = 0x88,
  
  SCSI_COMMAND_READ_CAPACITY10          = 0x25,
  SCSI_COMMAND_READ_CAPACITY16          = 0x9E,
  
  SCSI_COMMAND_REQUEST_SENSE            = 0x03,
  SCSI_COMMAND_START_STOP_UNIT          = 0x1B,
  SCSI_COMMAND_TEST_UNIT_READY          = 0x00,
  SCSI_COMMAND_WRITE6                   = 0x0A,
  SCSI_COMMAND_WRITE10                  = 0x2A,
  SCSI_COMMAND_WRITE12                  = 0xAA,
  SCSI_COMMAND_WRITE16                  = 0x8A,

  SCSI_COMMAND_VERIFY10                 = 0x2F,
  SCSI_COMMAND_VERIFY12                 = 0xAF,
  SCSI_COMMAND_VERIFY16                 = 0x8F,
  
  SCSI_COMMAND_SEND_DIAGNOSTIC          = 0x1D,
  SCSI_COMMAND_READ_FORMAT_CAPACITIES   = 0x23,
} SCSI_COMMAND;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                      |       //Address       Default         Description
__packed typedef struct
{
  SCSI_COMMAND Command;
  unsigned char Info;                           //                              LUN usually at 3 bit high, refer doccument for special bits
  __packed union
  {
    RSTRUCT(INQUIRY, unsigned char,
      _reserved                         [2],
      _AllocationLength                    ,    //              0x24
      _reserved1                        [11]);
    RSTRUCT(, unsigned char,
      LogicalBlockAddress               [4],    //                              MSB
      _reserved                            ,
      Length                            [2],    //                              MSB
      _reserved1                        [7])
      READ_10, WRITE_10, VERIFY;
    RSTRUCT(REQUEST_SENSE, unsigned char,
      _reserved                         [2],
      AllocationLength                     ,
      _reserved1                        [11]);
    RSTRUCT(, unsigned char,
      _reserved1                        [14])
      TEST_UNIT_READY, READ_CAPACITY;
    RSTRUCT(MODE_SENSE_10, unsigned char,
      PageCode                             ,    //                              6 bit low is used
      _reserved                         [4],
      ParameterListLength               [2],    //                              MSB
      _reserved1                        [7]);
    RSTRUCT(FORMAT_UNIT, unsigned char,
      VendorSpecific                       ,
      Interleave                        [2],    //                              MSB
      _reserved1                        [11]);
    RSTRUCT(READ_TOC, unsigned char,
      FormatA                              ,
      _reserved                         [4],
      AllocationLength                  [2],    //                              MSB
      _reserved1                        [7]);
    RSTRUCT(READ_FORMAT_CAPACITIES, unsigned char,
      _reserved                         [5],
      AllocationLength                  [2],    //                              MSB
      _reserved1                        [7]);
  };
} USB_MASS_SCSI_Command_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef union
{
  RSTRUCT(INQUIRY, unsigned char,
    PeripheralDeviceType                   ,    //                              5 bit low is used
                                                //                              0x00: SBC Direct-access device (e.g., UHD Floppy disk)
                                                //                              0x01:0x04: Out of scope
                                                //                              0x05: CD-ROM device
                                                //                              0x06: Out of scope
                                                //                              0x07:  Optical memory device (e.g., Non-CD optical disks)
                                                //                              0x08:0x0D: Out of scope
                                                //                              0x0E:  RBC Direct-access device (e.g., UHD Floppy disk)
    RMB                                    ,    //                              0x0F:0xFF: Out of scope
    _reserved                           [2],
    AdditionalLength                       ,
    _reserved1                          [2],
    VendorIdentification                [8],
    ProductIdentification               [16],
    ProductRevisionLevel                [4]);
  struct
  {
    BUNION(Status, unsigned char,
      ErrorCode                         , 7,    //                              0x70 or 0x71
      Valid                             , 1);
    unsigned char _SegmentNumber;
    BUNION(Info, unsigned char,
      SenseKey                          , 4,
      _reserved                         , 1,
      ILI                               , 1,
      _reserved1                        , 2);
    REGS(unsigned char,
      Information                       [4],
      AdditionalSenseLength                ,    //                              (n - 7)
      CommandSpecificInfo               [4],
      AdditionalSenseCode                  ,
      AdditionalSenseCodeQualifier         );
      //_reserved[n]);
  } REQUEST_SENSE;
  RSTRUCT(READ_CAPACITY, unsigned char,
    LastLogicalBlockAddress             [4],    //                              MSB
    BlockLength                         [4]);   //                              MSB (in bytes)
    RSTRUCT(READ_FORMAT_CAPACITIES, unsigned char,
      _reserved                         [3],
      CapacityListLength                   ,
      NumberOfBlocks                    [4],    //                              MSB
      DescriptorCode                       ,    //                              0x01: Unformatted Media - Maximum formattable capacity for this cartridge
                                                //                              0x02: Formatted Media - Current media capacity
                                                //                              0x03: No Cartridge in Drive - Maximum formattable capacity for any cartridge
      BlockLength                       [3]);   //                              MSB    
//  RSTRUCT(ReadTOC, unsigned char,
//    TOCDataLength                       [2],    //              0x0A            MSB
//    FirstCompleteSessionNumber             ,
//    LastCompleteSessionNumber              ,
//    _reserved                           [2],
//     FirstTrackNumber                      ,
//    _reserved                              ,
//    LogicalBlockAddress                 [4]);   //                              MSB
} USB_MASS_SCSI_Respond_TypeDef;

#endif