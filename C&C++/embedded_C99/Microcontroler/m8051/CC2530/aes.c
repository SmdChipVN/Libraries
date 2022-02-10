#include <aes.h>

typedef enum
{
  AES_COMMAND_ENCRYPT_BLOCK     = (0<<1),
  AES_COMMAND_DECRYPT_BLOCK     = (1<<1),
  AES_COMMAND_LOAD_KEY          = (2<<1),
  AES_COMMAND_LOAD_VECTOR       = (3<<1),
} AES_COMMAND;
static BASE_STATUS _AES_Process(const AESRule_TypeDef* AESRule, const unsigned char* SrcData, unsigned char* DstBuffer, unsigned short Length, AES_COMMAND CMD)
{
  static const __code unsigned char packet_div[][2] = {
    /*AES_MODE_CBC    */  {1, 16},
    /*AES_MODE_CFB    */  {4, 4},
    /*AES_MODE_OFB    */  {4, 4},
    /*AES_MODE_CTR    */  {4, 4},
    /*AES_MODE_ECB    */  {1, 16},};
//    /*AES_MODE_CBC_MAC*/  {1, 16},};
  if (AES_ENCCS.BITS.READY)
  {
    AES_ENCCS.REG = AES_COMMAND_LOAD_KEY | BIT0;
    for (unsigned char i = 0; i < 16; i++)
      AES_IN = AESRule->Key[i];
    
    AES_ENCCS.REG = AES_COMMAND_LOAD_VECTOR | BIT0 | AESRule->Mode;
    for (unsigned char i = 0; i < 16; i++)
      AES_IN = AESRule->Vector[i];
    
    unsigned char size_of_packet = packet_div[AESRule->Mode >> 4][1];
    while (Length)
    {
      Length -= 16;
      AES_ENCCS.REG = CMD | BIT0 | AESRule->Mode;
      unsigned char npacket_div = packet_div[AESRule->Mode >> 4][0];      
      
      while (npacket_div--)
      {
        for (unsigned char i = 0; i < size_of_packet; i++)
          AES_IN = *SrcData++;

//        if (AESRule->Delay)
//          AESRule->Delay();

        for (unsigned char i = 0; i < size_of_packet; i++)
          *DstBuffer++ = AES_OUT;
      }
    }
    return BASE_STATUS_DONE;
  }
  return BASE_STATUS_BUSY;
}


BASE_STATUS AES_Encrypt(const AESRule_TypeDef* AESRule, const unsigned char* SrcData, unsigned char* DstBuffer, unsigned short Length)
{
  return _AES_Process(AESRule, SrcData, DstBuffer, Length, AES_COMMAND_ENCRYPT_BLOCK);
}

BASE_STATUS AES_Decrypt(const AESRule_TypeDef* AESRule, const unsigned char* SrcData, unsigned char* DstBuffer, unsigned short Length)
{
  return _AES_Process(AESRule, SrcData, DstBuffer, Length, AES_COMMAND_DECRYPT_BLOCK);
}