#ifndef _IEEE_802_15_4_H_
#define _IEEE_802_15_4_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef BRUNION_16x8(FCF_TypeDef, ,             //                              Frame Control Field format
  r0, r1,
  
  FrameType                             , 3,    //0:2                                   0: Beacon
                                                //                                      1: Data
                                                //                                      2: Ack
                                                //                                      3: Command
  SecurityEnabled                       , 1,    //3
  FramePending                          , 1,    //4
  AcknowledgeRequest                    , 1,    //5
  PAN_ID_Comp                           , 1,    //6                             Personal Area Network (PAN) ID Compression
  _reserved                             , 1,
  _reserved1                            , 2,
  Dest_AM                               , 2,    //2-3                           Destination Addressing Mode
                                                //                                      0: PAN identifier and address fields are not present
                                                //                                      2: Address field contains a short address (16 bit)
                                                //                                      3: Address field contains an extended address (64 bit)
  FrameVersion                          , 2,    //4-5                                   0: Frame is compatible with IEEE Std. 802.15.4-2003
                                                //                                      1: IEEE 802.15.4 frame
  Src_AM                                , 2);   //6-7                           Source Addressing Mode (same Destination Addressing Mode)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned short PAN_ID;
  unsigned short Address;
} ShortAddressField_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  unsigned short PAN_ID;
  unsigned char Address[8];
} ExtendAddressField_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef union
{
  unsigned short PAN_ID;
  union
  {
    unsigned short Short;
    unsigned char Extend[8];
  } Address;
} AddressField_TypeDef;

#endif