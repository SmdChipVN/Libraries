#include <config.h>
#include <common.h>

typedef enum {
  // Page 0: Command and status
  CommandReg            = 0x01 << 1,    //starts and stops command execution
  ComIEnReg             = 0x02 << 1,    //enable and disable interrupt request control bits
  DivIEnReg             = 0x03 << 1,    //enable and disable interrupt request control bits
  ComIrqReg             = 0x04 << 1,    //interrupt request bits
  DivIrqReg             = 0x05 << 1,    //interrupt request bits
  ErrorReg              = 0x06 << 1,    //error bits showing the error status of the last command executed 
  Status1Reg            = 0x07 << 1,    //communication status bits
  Status2Reg            = 0x08 << 1,    //receiver and transmitter status bits
  FIFODataReg           = 0x09 << 1,    //input and output of 64 unsigned char FIFO buffer
  FIFOLevelReg          = 0x0A << 1,    //number of unsigned chars stored in the FIFO buffer
  WaterLevelReg         = 0x0B << 1,    //level for FIFO underflow and overflow warning
  ControlReg            = 0x0C << 1,    //miscellaneous control registers
  BitFramingReg         = 0x0D << 1,    //adjustments for bit-oriented frames
  CollReg               = 0x0E << 1,    //bit position of the first bit-collision detected on the RF interface
  // Page 1: Command
  ModeReg               = 0x11 << 1,    //defines general modes for transmitting and receiving 
  TxModeReg             = 0x12 << 1,    //defines transmission data rate and framing
  RxModeReg             = 0x13 << 1,    //defines reception data rate and framing
  TxControlReg          = 0x14 << 1,    //controls the logical behavior of the antenna driver pins TX1 and TX2
  TxASKReg              = 0x15 << 1,    //controls the setting of the transmission modulation
  TxSelReg              = 0x16 << 1,    //selects the internal sources for the antenna driver
  RxSelReg              = 0x17 << 1,    //selects internal receiver settings
  RxThresholdReg        = 0x18 << 1,    //selects thresholds for the bit decoder
  DemodReg              = 0x19 << 1,    //defines demodulator settings
  MfTxReg               = 0x1C << 1,    //controls some MIFARE communication transmit parameters
  MfRxReg               = 0x1D << 1,    //controls some MIFARE communication receive parameters
  SerialSpeedReg        = 0x1F << 1,    //selects the speed of the serial UART interface
  // Page 2: Configuration
  CRCResultRegH         = 0x21 << 1,    //shows the MSB and LSB values of the CRC calculation
  CRCResultRegL         = 0x22 << 1,
  ModWidthReg           = 0x24 << 1,    //controls the ModWidth setting?
  RFCfgReg              = 0x26 << 1,    //configures the receiver gain
  GsNReg                = 0x27 << 1,    //selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
  CWGsPReg              = 0x28 << 1,    //defines the conductance of the p-driver output during periods of no modulation
  ModGsPReg             = 0x29 << 1,    //defines the conductance of the p-driver output during periods of modulation
  TModeReg              = 0x2A << 1,    //defines settings for the internal timer
  TPrescalerReg         = 0x2B << 1,    //the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
  TReloadRegH           = 0x2C << 1,    //defines the 16-bit timer reload value
  TReloadRegL           = 0x2D << 1,
  TCounterValueRegH     = 0x2E << 1,    //shows the 16-bit timer value
  TCounterValueRegL     = 0x2F << 1,
  // Page 3: Test Registers
  TestSel1Reg           = 0x31 << 1,    //general test signal configuration
  TestSel2Reg           = 0x32 << 1,    //general test signal configuration
  TestPinEnReg          = 0x33 << 1,    //enables pin output driver on pins D1 to D7
  TestPinValueReg       = 0x34 << 1,    //defines the values for D1 to D7 when it is used as an I/O bus
  TestBusReg            = 0x35 << 1,    //shows the status of the internal test bus
  AutoTestReg           = 0x36 << 1,    //controls the digital self-test
  VersionReg            = 0x37 << 1,    //shows the software version
  AnalogTestReg         = 0x38 << 1,    //controls the pins AUX1 and AUX2
  TestDAC1Reg           = 0x39 << 1,    //defines the test value for TestDAC1
  TestDAC2Reg           = 0x3A << 1,    //defines the test value for TestDAC2
  TestADCReg            = 0x3B << 1,    //shows the value of ADC I and Q channels
} Register;

typedef union {
  unsigned char REG;
  struct
  {
    unsigned char _reserved2 : 2;
    unsigned char CRC_COMPLETE : 1;
    unsigned char _reserved1 : 1;
    unsigned char MFIN_ACTIVE : 1;
    unsigned char _reserved : 2;    
    unsigned char SET2 : 1;
  } BITS;
} DivIrqReg_TypeDef;
typedef union {
  unsigned char REG;
  struct
  {
    unsigned char TIMER : 1;
    unsigned char ERROR : 1;
    unsigned char LOW_ALERT : 1;
    unsigned char HIGH_ALERT : 1;
    unsigned char IDLE : 1;
    unsigned char RX_COMPLETE : 1;
    unsigned char TX_COMPLETE : 1;
    unsigned char SET2 : 1;
  } BITS;
} ComIrqReg_TypeDef;

typedef enum {
  CMD_IDLE              = 0x00,         //no action, cancels current command execution
  CMD_MEM               = 0x01,         //stores 25 unsigned chars into the internal buffer
  CMD_GEN_RAND_ID       = 0x02,         //generates a 10-unsigned char random ID number
  CMD_CALC_CRC          = 0x03,         //activates the CRC coprocessor or performs a self-test
  CMD_TRANSMIT          = 0x04,         //transmits data from the FIFO buffer
  CMD_NONE              = 0x07,         //no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
  CMD_RECIEVE           = 0x08,         //activates the receiver circuits
  CMD_TRANSCEIVE        = 0x0C,         //transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
  CMD_MF_AUTHENT        = 0x0E,         //performs the MIFARE standard authentication as a reader
  CMD_SOFT_RESET        = 0x0F,         //resets the MFRC522
} COMMAND;

// Commands sent to the MIFARE.
typedef enum {
  // The commands used by the PCD to manage communication with several MIFAREs (ISO 14443-3, Type A, section 6.4)
  MIFARE_CMD_REQA       = 0x26,         // REQuest command, Type A. Invites MIFAREs in state IDLE to go to READY and prepare for anticollision or selection. 7 bit frame.
  MIFARE_CMD_WUPA       = 0x52,         // Wake-UP command, Type A. Invites MIFAREs in state IDLE and HALT to go to READY(*) and prepare for anticollision or selection. 7 bit frame.
  //MIFARE_CMD_CT         = 0x88,         // Cascade Tag. Not really a command, but used during anti collision.
  MIFARE_CMD_SEL_CL1    = 0x93,         // Anti collision/Select, Cascade Level 1
  MIFARE_CMD_SEL_CL2    = 0x95,         // Anti collision/Select, Cascade Level 2
  MIFARE_CMD_SEL_CL3    = 0x97,         // Anti collision/Select, Cascade Level 3
  MIFARE_CMD_HALT       = 0x50,         // HaLT command, Type A. Instructs an ACTIVE MIFARE to go to state HALT.
  //MIFARE_CMD_RATS       = 0xE0,         // Request command for Answer To Reset.
  // The commands used for MIFARE Classic (from http://www.mouser.com/ds/2/302/MF1S503x-89574.pdf, Section 9)
  // Use PCD_MFAuthent to authenticate access to a sector, then use these commands to read/write/modify the blocks on the sector.
  // The read/write commands can also be used for MIFARE Ultralight.
  MIFARE_CMD_AUTH_KEY_A = 0x60,         // Perform authentication with Key A
  MIFARE_CMD_AUTH_KEY_B = 0x61,         // Perform authentication with Key B

  MIFARE_CMD_READ       = 0x30,         // Reads one 16 unsigned char block from the authenticated sector of the MIFARE. Also used for MIFARE Ultralight.
  MIFARE_CMD_WRITE      = 0xA0,         // Writes one 16 unsigned char block to the authenticated sector of the MIFARE. Called "COMPATIBILITY WRITE" for MIFARE Ultralight.
  MIFARE_CMD_DECREMENT  = 0xC0,         // Decrements the contents of a block and stores the result in the internal data register.
  MIFARE_CMD_INCREMENT  = 0xC1,         // Increments the contents of a block and stores the result in the internal data register.
  MIFARE_CMD_RESTORE    = 0xC2,         // Reads the contents of a block into the internal data register.
  MIFARE_CMD_TRANSFER   = 0xB0,         // Writes the contents of the internal data register to a block.
  // The commands used for MIFARE Ultralight (from http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf, Section 8.6)
  // The MIFARE_CMD_MF_READ and MIFARE_CMD_MF_WRITE can also be used for MIFARE Ultralight.
  MIFARE_CMD_UL_WRITE   = 0xA2,         // Writes one 4 unsigned char page to the MIFARE.
} MIFARE_CMD;


static reg8 ReadRegister(reg8 Address)
{
  reg8 ret;
  MFRC522_CONFIG_NSS_0(0);
  MFRC522_SPI_WRITEBYTE(BIT7 | Address);
  ret = MFRC522_SPI_WRITEBYTE(0x00);
  MFRC522_CONFIG_NSS_0(1);
  return ret;
}
static void ReadRegisters(reg8 Address, unsigned char* Buffer, reg8 Length)
{
  MFRC522_CONFIG_NSS_0(0);
  MFRC522_SPI_WRITEBYTE(BIT7 | Address);
  while (--Length)
    *Buffer++ = MFRC522_SPI_WRITEBYTE(Address);
  *Buffer = MFRC522_SPI_WRITEBYTE(0x00);
  MFRC522_CONFIG_NSS_0(1);
}
static void WriteRegister(reg8 Address, reg8 Value)
{
  MFRC522_CONFIG_NSS_0(0);
  MFRC522_SPI_WRITEBYTE(Address);
  MFRC522_SPI_WRITEBYTE(Value);
  MFRC522_CONFIG_NSS_0(1);
}
static void WriteRegisters(reg8 Address, unsigned char __gptr* Data, reg8 Length)
{
  MFRC522_CONFIG_NSS_0(0);
  MFRC522_SPI_WRITEBYTE(Address);
  while (Length--)
    MFRC522_SPI_WRITEBYTE(*Data++);
  MFRC522_CONFIG_NSS_0(1);
}

reg8 MFRC522_ReadCard(unsigned char* CardUID)
{
  WriteRegister(CommandReg, CMD_IDLE);          //Stop any active command
  WriteRegister(DivIrqReg, 0x04);               // Clear the CRCIRq interrupt request bit  
  WriteRegister(FIFOLevelReg, 0x80);            //Flush buffer
  unsigned char read_code[4] = {MIFARE_CMD_READ, 0x00, };
  WriteRegisters(FIFODataReg, read_code, 2);
  WriteRegister(CommandReg, CMD_CALC_CRC);      //
  while (1)
  {
    DivIrqReg_TypeDef div;
    div.REG = ReadRegister(DivIrqReg);
    if (div.BITS.CRC_COMPLETE)
      break;
  }
  WriteRegister(CommandReg, CMD_IDLE);          //Stop any active command
  read_code[2] = ReadRegister(CRCResultRegL);
  read_code[3] = ReadRegister(CRCResultRegH);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  WriteRegister(ComIrqReg, 0x7F);               //Clear all seven interrupt request bits
  WriteRegister(FIFOLevelReg, 0x80);            //Flush buffer
  
  reg8 state = 0;
  state = ReadRegister(FIFOLevelReg);
  
  state = ReadRegister(ComIrqReg);
  
  WriteRegisters(FIFODataReg, read_code, 4);
  WriteRegister(CommandReg, CMD_TRANSCEIVE);    //
  
  state = ReadRegister(FIFOLevelReg);
  
  WriteRegister(BitFramingReg, 0xF0);
  
  state = 0;
  
  while (!state)
  {
    ComIrqReg_TypeDef com;
    com.REG = ReadRegister(ComIrqReg);
    if (com.BITS.RX_COMPLETE)
    {
      WriteRegister(CommandReg, CMD_IDLE);
      state = ReadRegister(FIFOLevelReg);
      if (state != 16)
        return 0;
      ReadRegisters(FIFODataReg, CardUID, 4);
      return 1;
    }
    else if (com.BITS.TIMER)
      state = 2;
    else if (com.BITS.ERROR)
      state = 3;
  }
  WriteRegister(CommandReg, CMD_IDLE);
  return state;  
}