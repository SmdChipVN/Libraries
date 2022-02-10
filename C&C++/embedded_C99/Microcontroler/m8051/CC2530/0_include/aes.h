#ifndef _AES_H_
#define _AES_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
SFRB(AES_ENCCS, 0xB3, ,                         //              0x08            Encryption Control and Status
  STATUS                                , 1,    //0             0               Start processing command set by CMD
  COMMAND                               , 2,    //1-2           0               Command to be performed when a 1 is written to STATUS
  const READY                           , 1,    //3             1               Encryption or decryption ready status
  MODE                                  , 3,    //4:6           0               Encryption/decryption mode
                                                //                                      0: CBC
                                                //                                      1: CFB
                                                //                                      2: OFB
                                                //                                      3: CTR
                                                //                                      4: ECB
  _Reserved                             , 1);
SFR(AES_IN, 0xB1);                              //              0x--            Encryption Input Data
SFR(AES_OUT, 0xB2);                             //              0x--            Encryption Output Data
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================
typedef struct
{
  unsigned char* Key;
  unsigned char* Vector;
  unsigned char Mode;
  void (*Delay)();
  void (*Push)(unsigned char* Data, unsigned char Length);
  void (*Pop)(unsigned char* Data, unsigned char Length);
} AESRule_TypeDef;
/*Example:
AESRule_TypeDef AESRule = {
  .Key = ...,
  .Vector = ...,
  .Mode = AES_MODE_CBC,
  .Delay = ...,
  .Push = NULL,
  .Pop = NULL,
};
AES_Encrypt(&AESRule, SrcData, DstBuffer, 16);
AES_Decrypt(&AESRule, SrcData, DstBuffer, 16);
*/
BASE_STATUS AES_Encrypt(const AESRule_TypeDef* AESRule, const unsigned char* SrcData, unsigned char* DstBuffer, unsigned short Length); //Length must % 16 = 0
BASE_STATUS AES_Decrypt(const AESRule_TypeDef* AESRule, const unsigned char* SrcData, unsigned char* DstBuffer, unsigned short Length);

#endif