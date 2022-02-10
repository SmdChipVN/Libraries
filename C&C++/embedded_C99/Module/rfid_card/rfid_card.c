#include <rfid_card.h>
#include <common.h>

typedef enum {
  MIFARE_CMD_REQA       = 0x26,         // REQuest command, Type A. Invites MIFAREs in state IDLE to go to READY and prepare for anticollision or selection. 7 bit frame.
  MIFARE_CMD_WUPA       = 0x52,         // Wake-UP command, Type A. Invites MIFAREs in state IDLE and HALT to go to READY(*) and prepare for anticollision or selection. 7 bit frame.
  MIFARE_CMD_CT         = 0x88,         // Cascade Tag. Not really a command, but used during anti collision.
  MIFARE_CMD_SEL_CL1    = 0x93,         // Anti collision/Select, Cascade Level 1
  MIFARE_CMD_SEL_CL2    = 0x95,         // Anti collision/Select, Cascade Level 2
  MIFARE_CMD_SEL_CL3    = 0x97,         // Anti collision/Select, Cascade Level 3
  MIFARE_CMD_HALT       = 0x50,         // HaLT command, Type A. Instructs an ACTIVE MIFARE to go to state HALT.
  MIFARE_CMD_RATS       = 0xE0,         // Request command for Answer To Reset.
  MIFARE_CMD_AUTH_KEY_A = 0x60,         // Perform authentication with Key A
  MIFARE_CMD_AUTH_KEY_B = 0x61,         // Perform authentication with Key B
  MIFARE_CMD_READ       = 0x30,         // Reads one 16 unsigned char block from the authenticated sector of the MIFARE. Also used for MIFARE Ultralight.
  MIFARE_CMD_WRITE      = 0xA0,         // Writes one 16 unsigned char block to the authenticated sector of the MIFARE. Called "COMPATIBILITY WRITE" for MIFARE Ultralight.
  MIFARE_CMD_DECREMENT  = 0xC0,         // Decrements the contents of a block and stores the result in the internal data register.
  MIFARE_CMD_INCREMENT  = 0xC1,         // Increments the contents of a block and stores the result in the internal data register.
  MIFARE_CMD_RESTORE    = 0xC2,         // Reads the contents of a block into the internal data register.
  MIFARE_CMD_TRANSFER   = 0xB0,         // Writes the contents of the internal data register to a block.
  MIFARE_CMD_UL_WRITE   = 0xA2,         // Writes one 4 unsigned char page to the MIFARE.
} MIFARE_CMD;

static reg16 CRC16(reg16 Preset, unsigned char* Data, reg8 Size)
{

  return Preset;
}
void RFID_PrepareRead(reg8 BlockAddress, unsigned char* DstBuffer)
{
  DstBuffer[0] = MIFARE_CMD_READ;
  DstBuffer[1] = BlockAddress;
  
}
void RFID_PrepareWrite(reg8 BlockAddress, unsigned char* DstBuffer, reg8 IsFirstPart)
{
  
}