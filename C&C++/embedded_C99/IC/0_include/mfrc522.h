/**
 * Library to use Arduino MFRC522 module.
 * 
 * @authors Dr.Leong, Miguel Balboa, S�ren Thing Andersen, Tom Clement, many more! See GitLog.
 * 
 * For more information read the README.
 * 
 * Please read this file for an overview and then MFRC522.cpp for comments on the specific functions.
 */
#ifndef MFRC522_h
#define MFRC522_h

#ifndef MFRC522_SPICLOCK
#define MFRC522_SPICLOCK (4000000u)	// MFRC522 accept upto 10MHz, set to 4MHz.
#endif

// MFRC522 registers. Described in chapter 9 of the datasheet.
// When using SPI all addresses are shifted one bit left in the "SPI address unsigned char" (section 8.1.2.3)
typedef enum {
  // Page 0: Command and status
  //						  0x00			// reserved for future use
  CommandReg				= 0x01 << 1,	// starts and stops command execution
  ComIEnReg				= 0x02 << 1,	// enable and disable interrupt request control bits
  DivIEnReg				= 0x03 << 1,	// enable and disable interrupt request control bits
  ComIrqReg				= 0x04 << 1,	// interrupt request bits
  DivIrqReg				= 0x05 << 1,	// interrupt request bits
  ErrorReg				= 0x06 << 1,	// error bits showing the error status of the last command executed 
  Status1Reg				= 0x07 << 1,	// communication status bits
  Status2Reg				= 0x08 << 1,	// receiver and transmitter status bits
  FIFODataReg				= 0x09 << 1,	// input and output of 64 unsigned char FIFO buffer
  FIFOLevelReg			= 0x0A << 1,	// number of unsigned chars stored in the FIFO buffer
  WaterLevelReg			= 0x0B << 1,	// level for FIFO underflow and overflow warning
  ControlReg				= 0x0C << 1,	// miscellaneous control registers
  BitFramingReg			= 0x0D << 1,	// adjustments for bit-oriented frames
  CollReg					= 0x0E << 1,	// bit position of the first bit-collision detected on the RF interface
  //						  0x0F			// reserved for future use
  
  // Page 1: Command
  // 						  0x10			// reserved for future use
  ModeReg					= 0x11 << 1,	// defines general modes for transmitting and receiving 
  TxModeReg				= 0x12 << 1,	// defines transmission data rate and framing
  RxModeReg				= 0x13 << 1,	// defines reception data rate and framing
  TxControlReg			= 0x14 << 1,	// controls the logical behavior of the antenna driver pins TX1 and TX2
  TxASKReg				= 0x15 << 1,	// controls the setting of the transmission modulation
  TxSelReg				= 0x16 << 1,	// selects the internal sources for the antenna driver
  RxSelReg				= 0x17 << 1,	// selects internal receiver settings
  RxThresholdReg			= 0x18 << 1,	// selects thresholds for the bit decoder
  DemodReg				= 0x19 << 1,	// defines demodulator settings
  // 						  0x1A			// reserved for future use
  // 						  0x1B			// reserved for future use
  MfTxReg					= 0x1C << 1,	// controls some MIFARE communication transmit parameters
  MfRxReg					= 0x1D << 1,	// controls some MIFARE communication receive parameters
  // 						  0x1E			// reserved for future use
  SerialSpeedReg			= 0x1F << 1,	// selects the speed of the serial UART interface
  
  // Page 2: Configuration
  // 						  0x20			// reserved for future use
  CRCResultRegH			= 0x21 << 1,	// shows the MSB and LSB values of the CRC calculation
  CRCResultRegL			= 0x22 << 1,
  // 						  0x23			// reserved for future use
  ModWidthReg				= 0x24 << 1,	// controls the ModWidth setting?
  // 						  0x25			// reserved for future use
  RFCfgReg				= 0x26 << 1,	// configures the receiver gain
  GsNReg					= 0x27 << 1,	// selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
  CWGsPReg				= 0x28 << 1,	// defines the conductance of the p-driver output during periods of no modulation
  ModGsPReg				= 0x29 << 1,	// defines the conductance of the p-driver output during periods of modulation
  TModeReg				= 0x2A << 1,	// defines settings for the internal timer
  TPrescalerReg			= 0x2B << 1,	// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
  TReloadRegH				= 0x2C << 1,	// defines the 16-bit timer reload value
  TReloadRegL				= 0x2D << 1,
  TCounterValueRegH		= 0x2E << 1,	// shows the 16-bit timer value
  TCounterValueRegL		= 0x2F << 1,
  
  // Page 3: Test Registers
  // 						  0x30			// reserved for future use
  TestSel1Reg				= 0x31 << 1,	// general test signal configuration
  TestSel2Reg				= 0x32 << 1,	// general test signal configuration
  TestPinEnReg			= 0x33 << 1,	// enables pin output driver on pins D1 to D7
  TestPinValueReg			= 0x34 << 1,	// defines the values for D1 to D7 when it is used as an I/O bus
  TestBusReg				= 0x35 << 1,	// shows the status of the internal test bus
  AutoTestReg				= 0x36 << 1,	// controls the digital self-test
  VersionReg				= 0x37 << 1,	// shows the software version
  AnalogTestReg			= 0x38 << 1,	// controls the pins AUX1 and AUX2
  TestDAC1Reg				= 0x39 << 1,	// defines the test value for TestDAC1
  TestDAC2Reg				= 0x3A << 1,	// defines the test value for TestDAC2
  TestADCReg				= 0x3B << 1		// shows the value of ADC I and Q channels
  // 						  0x3C			// reserved for production tests
  // 						  0x3D			// reserved for production tests
  // 						  0x3E			// reserved for production tests
  // 						  0x3F			// reserved for production tests
} PCD_Register;
// MFRC522 commands. Described in chapter 10 of the datasheet.
typedef enum {
  PCD_Idle				= 0x00,		// no action, cancels current command execution
  PCD_Mem					= 0x01,		// stores 25 unsigned chars into the internal buffer
  PCD_GenerateRandomID	= 0x02,		// generates a 10-unsigned char random ID number
  PCD_CalcCRC				= 0x03,		// activates the CRC coprocessor or performs a self-test
  PCD_Transmit			= 0x04,		// transmits data from the FIFO buffer
  PCD_NoCmdChange			= 0x07,		// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
  PCD_Receive				= 0x08,		// activates the receiver circuits
  PCD_Transceive 			= 0x0C,		// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
  PCD_MFAuthent 			= 0x0E,		// performs the MIFARE standard authentication as a reader
  PCD_SoftReset			= 0x0F		// resets the MFRC522
} PCD_Command;

// MFRC522 RxGain[2:0] masks, defines the receiver's signal voltage gain factor (on the PCD).
// Described in 9.3.3.6 / table 98 of the datasheet at http://www.nxp.com/documents/data_sheet/MFRC522.pdf
typedef enum {
  RxGain_18dB				= 0x00 << 4,	// 000b - 18 dB, minimum
  RxGain_23dB				= 0x01 << 4,	// 001b - 23 dB
  RxGain_18dB_2			= 0x02 << 4,	// 010b - 18 dB, it seems 010b is a duplicate for 000b
  RxGain_23dB_2			= 0x03 << 4,	// 011b - 23 dB, it seems 011b is a duplicate for 001b
  RxGain_33dB				= 0x04 << 4,	// 100b - 33 dB, average, and typical default
  RxGain_38dB				= 0x05 << 4,	// 101b - 38 dB
  RxGain_43dB				= 0x06 << 4,	// 110b - 43 dB
  RxGain_48dB				= 0x07 << 4,	// 111b - 48 dB, maximum
  RxGain_min				= 0x00 << 4,	// 000b - 18 dB, minimum, convenience for RxGain_18dB
  RxGain_avg				= 0x04 << 4,	// 100b - 33 dB, average, convenience for RxGain_33dB
  RxGain_max				= 0x07 << 4		// 111b - 48 dB, maximum, convenience for RxGain_48dB
} PCD_RxGain;

// Commands sent to the PICC.
typedef enum {
  // The commands used by the PCD to manage communication with several PICCs (ISO 14443-3, Type A, section 6.4)
  PICC_CMD_REQA			= 0x26,		// REQuest command, Type A. Invites PICCs in state IDLE to go to READY and prepare for anticollision or selection. 7 bit frame.
  PICC_CMD_WUPA			= 0x52,		// Wake-UP command, Type A. Invites PICCs in state IDLE and HALT to go to READY(*) and prepare for anticollision or selection. 7 bit frame.
  PICC_CMD_CT				= 0x88,		// Cascade Tag. Not really a command, but used during anti collision.
  PICC_CMD_SEL_CL1		= 0x93,		// Anti collision/Select, Cascade Level 1
  PICC_CMD_SEL_CL2		= 0x95,		// Anti collision/Select, Cascade Level 2
  PICC_CMD_SEL_CL3		= 0x97,		// Anti collision/Select, Cascade Level 3
  PICC_CMD_HLTA			= 0x50,		// HaLT command, Type A. Instructs an ACTIVE PICC to go to state HALT.
  PICC_CMD_RATS           = 0xE0,     // Request command for Answer To Reset.
  // The commands used for MIFARE Classic (from http://www.mouser.com/ds/2/302/MF1S503x-89574.pdf, Section 9)
  // Use PCD_MFAuthent to authenticate access to a sector, then use these commands to read/write/modify the blocks on the sector.
  // The read/write commands can also be used for MIFARE Ultralight.
  PICC_CMD_MF_AUTH_KEY_A	= 0x60,		// Perform authentication with Key A
  PICC_CMD_MF_AUTH_KEY_B	= 0x61,		// Perform authentication with Key B
  PICC_CMD_MF_READ		= 0x30,		// Reads one 16 unsigned char block from the authenticated sector of the PICC. Also used for MIFARE Ultralight.
  PICC_CMD_MF_WRITE		= 0xA0,		// Writes one 16 unsigned char block to the authenticated sector of the PICC. Called "COMPATIBILITY WRITE" for MIFARE Ultralight.
  PICC_CMD_MF_DECREMENT	= 0xC0,		// Decrements the contents of a block and stores the result in the internal data register.
  PICC_CMD_MF_INCREMENT	= 0xC1,		// Increments the contents of a block and stores the result in the internal data register.
  PICC_CMD_MF_RESTORE		= 0xC2,		// Reads the contents of a block into the internal data register.
  PICC_CMD_MF_TRANSFER	= 0xB0,		// Writes the contents of the internal data register to a block.
  // The commands used for MIFARE Ultralight (from http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf, Section 8.6)
  // The PICC_CMD_MF_READ and PICC_CMD_MF_WRITE can also be used for MIFARE Ultralight.
  PICC_CMD_UL_WRITE		= 0xA2		// Writes one 4 unsigned char page to the PICC.
} PICC_Command;
// MIFARE constants that does not fit anywhere else
typedef enum {
  MF_ACK					= 0xA,		// The MIFARE Classic uses a 4 bit ACK/NAK. Any other value than 0xA is NAK.
  MF_KEY_SIZE				= 6			// A Mifare Crypto1 key is 6 unsigned chars.
} MIFARE_Misc;

// PICC types we can detect. Remember to update PICC_GetTypeName() if you add more.
// last value set to 0xff, then compiler uses less ram, it seems some optimisations are triggered
typedef enum {
  PICC_TYPE_UNKNOWN		,
  PICC_TYPE_ISO_14443_4	,	// PICC compliant with ISO/IEC 14443-4 
  PICC_TYPE_ISO_18092		, 	// PICC compliant with ISO/IEC 18092 (NFC)
  PICC_TYPE_MIFARE_MINI	,	// MIFARE Classic protocol, 320 unsigned chars
  PICC_TYPE_MIFARE_1K		,	// MIFARE Classic protocol, 1KB
  PICC_TYPE_MIFARE_4K		,	// MIFARE Classic protocol, 4KB
  PICC_TYPE_MIFARE_UL		,	// MIFARE Ultralight or Ultralight C
  PICC_TYPE_MIFARE_PLUS	,	// MIFARE Plus
  PICC_TYPE_MIFARE_DESFIRE,	// MIFARE DESFire
  PICC_TYPE_TNP3XXX		,	// Only mentioned in NXP AN 10833 MIFARE Type Identification Procedure
  PICC_TYPE_NOT_COMPLETE	= 0xff	// SAK indicates UID is not complete.
} PICC_Type;

// Return codes from the functions in this class. Remember to update GetStatusCodeName() if you add more.
// last value set to 0xff, then compiler uses less ram, it seems some optimisations are triggered
typedef enum {
  STATUS_OK				,	// Success
  STATUS_ERROR			,	// Error in communication
  STATUS_COLLISION		,	// Collission detected
  STATUS_TIMEOUT			,	// Timeout in communication.
  STATUS_NO_ROOM			,	// A buffer is not big enough.
  STATUS_INTERNAL_ERROR	,	// Internal error in the code. Should not happen ;-)
  STATUS_INVALID			,	// Invalid argument.
  STATUS_CRC_WRONG		,	// The CRC_A does not match
  STATUS_MIFARE_NACK		= 0xff	// A MIFARE PICC responded with NAK.
} StatusCode;
// A struct used for passing the UID of a PICC.
typedef struct {
  unsigned char         size;			// Number of unsigned chars in the UID. 4, 7 or 10.
  unsigned char         uidByte[10];
  unsigned char         sak;			// The SAK (Select acknowledge) unsigned char returned from the PICC after successful selection.
} Uid;

// A struct used for passing a MIFARE Crypto1 key
typedef struct {
  unsigned char         keyByte[MF_KEY_SIZE];
} MIFARE_Key;

typedef struct
{
  // Size of the MFRC522 FIFO
  unsigned char FIFO_SIZE;      //The FIFO is 64 unsigned chars.
  unsigned char UNUSED_PIN;     // Default value for unused pin
  // Member variables
  Uid uid;								// Used by PICC_ReadCardSerial().
} MFRC522;
/////////////////////////////////////////////////////////////////////////////////////
// Functions for setting up the Arduino
/////////////////////////////////////////////////////////////////////////////////////
//void MFRC522();
//void MFRC522(unsigned char resetPowerDownPin);
//void MFRC522(unsigned char chipSelectPin, unsigned char resetPowerDownPin);

/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
void PCD_WriteRegister(PCD_Register reg, unsigned char value);
void PCD_WriteRegisters(PCD_Register reg, unsigned char count, unsigned char *values);

unsigned char PCD_ReadRegister(PCD_Register reg);
void PCD_ReadRegisters(PCD_Register reg, unsigned char count, unsigned char *values, unsigned char rxAlign);

void PCD_SetRegisterBitMask(PCD_Register reg, unsigned char mask);
void PCD_ClearRegisterBitMask(PCD_Register reg, unsigned char mask);
StatusCode PCD_CalculateCRC(unsigned char *data, unsigned char length, unsigned char *result);

/////////////////////////////////////////////////////////////////////////////////////
// Functions for manipulating the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
void PCD_Init();
//void PCD_Init(unsigned char resetPowerDownPin);
//void PCD_Init(unsigned char chipSelectPin, unsigned char resetPowerDownPin);
void PCD_Reset();
void PCD_AntennaOn();
void PCD_AntennaOff();
unsigned char PCD_GetAntennaGain();
void PCD_SetAntennaGain(unsigned char mask);
unsigned char PCD_PerformSelfTest();

/////////////////////////////////////////////////////////////////////////////////////
// Power control functions
/////////////////////////////////////////////////////////////////////////////////////
void PCD_SoftPowerDown();
void PCD_SoftPowerUp();

/////////////////////////////////////////////////////////////////////////////////////
// Functions for communicating with PICCs
/////////////////////////////////////////////////////////////////////////////////////
StatusCode PCD_TransceiveData(unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned char *backLen, unsigned char *validBits, unsigned char rxAlign, unsigned char checkCRC);
StatusCode PCD_CommunicateWithPICC(unsigned char command, unsigned char waitIRq, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned char *backLen, unsigned char *validBits, unsigned char rxAlign, unsigned char checkCRC);
StatusCode PICC_RequestA(unsigned char *bufferATQA, unsigned char *bufferSize);
StatusCode PICC_WakeupA(unsigned char *bufferATQA, unsigned char *bufferSize);
StatusCode PICC_REQA_or_WUPA(unsigned char command, unsigned char *bufferATQA, unsigned char *bufferSize);
StatusCode PICC_Select(Uid *uid, unsigned char validBits);
StatusCode PICC_HaltA();

/////////////////////////////////////////////////////////////////////////////////////
// Functions for communicating with MIFARE PICCs
/////////////////////////////////////////////////////////////////////////////////////
StatusCode PCD_Authenticate(unsigned char command, unsigned char blockAddr, MIFARE_Key *key, Uid *uid);
void PCD_StopCrypto1();
StatusCode MIFARE_Read(unsigned char blockAddr, unsigned char *buffer, unsigned char *bufferSize);
StatusCode MIFARE_Write(unsigned char blockAddr, unsigned char *buffer, unsigned char bufferSize);
StatusCode MIFARE_Ultralight_Write(unsigned char page, unsigned char *buffer, unsigned char bufferSize);
StatusCode MIFARE_Decrement(unsigned char blockAddr, unsigned int delta);
StatusCode MIFARE_Increment(unsigned char blockAddr, unsigned int delta);
StatusCode MIFARE_Restore(unsigned char blockAddr);
StatusCode MIFARE_Transfer(unsigned char blockAddr);
StatusCode MIFARE_GetValue(unsigned char blockAddr, unsigned int *value);
StatusCode MIFARE_SetValue(unsigned char blockAddr, unsigned int value);
StatusCode PCD_NTAG216_AUTH(unsigned char *passWord, unsigned char pACK[]);

///////////////////////////////////////////////////////////////////////////////////////
//// Support functions
///////////////////////////////////////////////////////////////////////////////////////
StatusCode PCD_MIFARE_Transceive(unsigned char *sendData, unsigned char sendLen, unsigned char acceptTimeout);
//// old function used too much memory, now name moved to flash; if you need char, copy from flash to memory
////const char *GetStatusCodeName(unsigned char code);
//static const __FlashStringHelper *GetStatusCodeName(StatusCode code);
//static PICC_Type PICC_GetType(unsigned char sak);
//// old function used too much memory, now name moved to flash; if you need char, copy from flash to memory
////const char *PICC_GetTypeName(unsigned char type);
//static const __FlashStringHelper *PICC_GetTypeName(PICC_Type type);

// Support functions for debuging
void PCD_DumpVersionToSerial();
void PICC_DumpToSerial(Uid *uid);
void PICC_DumpDetailsToSerial(Uid *uid);
void PICC_DumpMifareClassicToSerial(Uid *uid, PICC_Type piccType, MIFARE_Key *key);
void PICC_DumpMifareClassicSectorToSerial(Uid *uid, MIFARE_Key *key, unsigned char sector);
void PICC_DumpMifareUltralightToSerial();

// Advanced functions for MIFARE
void MIFARE_SetAccessBits(unsigned char *accessBitBuffer, unsigned char g0, unsigned char g1, unsigned char g2, unsigned char g3);
unsigned char MIFARE_OpenUidBackdoor(unsigned char logErrors);
unsigned char MIFARE_SetUid(unsigned char *newUid, unsigned char uidSize, unsigned char logErrors);
unsigned char MIFARE_UnbrickUidSector(unsigned char logErrors);

unsigned char PICC_IsNewCardPresent();
unsigned char PICC_ReadCardSerial();


//class MFRC522 {
//public:
//	
//	static constexpr unsigned char FIFO_SIZE = 64;		// The FIFO is 64 unsigned chars.
//	
//	static constexpr unsigned char UNUSED_PIN = UINT8_MAX;
//
//
//	
//	
//
//	
//
//	
//
//	
//
//	
//	/////////////////////////////////////////////////////////////////////////////////////
//	// Convenience functions - does not add extra functionality
//	/////////////////////////////////////////////////////////////////////////////////////
//	virtual unsigned char PICC_IsNewCardPresent();
//	virtual unsigned char PICC_ReadCardSerial();
//	
//protected:
//
//};

#endif