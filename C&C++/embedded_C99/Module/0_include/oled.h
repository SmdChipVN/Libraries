#ifndef _OLED_H_
#define _OLED_H_

#include <common.h>
#include <data_access.h>
//==============================================================================================================================================================
typedef struct
{
  unsigned char XOffset;
  void (*SPI_WriteByte)(reg8 Data);
  void (*ConfigCE)(reg8 IsSet);
  void (*ConfigDC)(reg8 IsSet);
  void (*ConfigRST)(reg8 IsSet);
} OledFunction_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                      |       //Address       Default         Description
typedef struct
{
  union
  {
    unsigned char REG;
    struct
    {
      unsigned char SegmentInvert       : 1;    //0             0
      unsigned char _reserved           : 2;
      unsigned char ComInvert           : 1;    //3             0
      unsigned char _reserved1          : 4;
    } BITS;
  } ScanMode;
  void (*ExtendConfig)();
} OledInit_TypeDef;
//==============================================================================================================================================================
void Oled_Init_0(const OledInit_TypeDef __code* OledInit);
void Oled_Clear_0();
void Oled_Fill_0(const unsigned char __gptr* Data);
void Oled_FillPart_0(const unsigned char __gptr* Data, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1);
void Oled_On_0();
void Oled_Off_0();

void Oled_FillDMA_0(DMAFunction_TypeDef* DMAFunction);
void Oled_FillPartDMA_0(DMAFunction_TypeDef* DMAFunction, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void Oled_Begin_1(const OledFunction_TypeDef __code* OLEDFunction);
void Oled_Clear_1(const OledFunction_TypeDef __code* OLEDFunction);
void Oled_SetPosition_1(const OledFunction_TypeDef __code* OLEDFunction, reg8 X, reg8 Y);
void Oled_Eraser_1(const OledFunction_TypeDef __code* OLEDFunction, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1);
reg8 Oled_Draw_1(const OledFunction_TypeDef __code* OLEDFunction, const unsigned char** Font, reg8 Character, reg8 X, reg8 Y);
void Oled_Off_1(const OledFunction_TypeDef __code* OLEDFunction);
void Oled_On_1(const OledFunction_TypeDef __code* OLEDFunction);
//==============================================================================================================================================================
//===================================================           COMMAND list      ==============================================================================
//==============================================================================================================================================================
/*
NOTE: REFER DATASHEER FOR AVAILABLE COMMAND LIST
----------------------------------------------------------------------------------------------------------------------------------------------------------------
                        Hex                     | D7    | D6    | D5    | D4    | D3    | D2    | D1    | D0
Set Contrast            0x81                    |       |       |       |       |       |       |       |
                        contrast                |
------------------------------------------------------------------------------------------------------------------
Entire on               0xA4 | on               |       |       |       |       |       |       |       | on
------------------------------------------------------------------------------------------------------------------
Inverse                 0xA6 | inverse          |       |       |       |       |       |       |       | inverse
------------------------------------------------------------------------------------------------------------------
Display on              0xAE | on               |       |       |       |       |       |       |       | on
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Horizontal              0x26 | left             |       |       |       |       |       |       |       | left
scroll                  0x00                    |       |       |       |       |       |       |       |
                        start page              |       |       |       |       |       |     start page
                        interval                |       |       |       |       |       |      interval
                        end page                |       |       |       |       |       |      end page
                        0x00                    |       |       |       |       |       |       |       |
                        0xFF                    |       |       |       |       |       |       |       |
------------------------------------------------------------------------------------------------------------------
Vertical &              0x28 | type             |       |       |       |       |       |       |       | 1: V-RH       No continuous vertical scrolling is available
Horizontal                                      |       |       |       |       |       |       |       | 2: V-LH
scroll                  0x00                    |       |       |       |       |       |       |       |
                        start page              |       |       |       |       |       |     start page
                        interval                |       |       |       |       |       |      interval
                        end page                |       |       |       |       |       |      end page
                        vertical offset         |       |       |         vertical offset
------------------------------------------------------------------------------------------------------------------
Deactivate scroll       0x2E                    |       |       |       |       |       |       |       |
                                                |       |       |       |       |       |       |       |
------------------------------------------------------------------------------------------------------------------
Activate scroll         0x2F                    |       |       |       |       |       |       |       |
------------------------------------------------------------------------------------------------------------------
Vertical Scroll         0xA3                    |       |       |       |       |       |       |       |
Area                    xx                      |       |       |       |       |       |       |       |
                        xx                      |       |       |       |       |       |       |       |
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Lower Column            column[3:0]             |       |       |       |       |       column[3:0]
Start Address for                               |       |       |       |       |
Page Addressing                                 |       |       |       |       |
Mode                                            |       |       |       |       |
------------------------------------------------------------------------------------------------------------------
Higher Column           0x10 | column[7:4]      |       |       |       |       |       column[7:4]
Start Address for                               |       |       |       |       |
Page Addressing                                 |       |       |       |       |
Mode                                            |       |       |       |       |
------------------------------------------------------------------------------------------------------------------
Memory                  0x20                    |       |       |       |       |       |       |       |
Addressing Mode         mode                    |       |       |       |       |       |       |  0: Horizontal
                                                |       |       |       |       |       |       |  1: Vertical
                                                |       |       |       |       |       |       |  2: Page Addressing Mode (RESET)
------------------------------------------------------------------------------------------------------------------
Set Column Address      0x21                    |       |       |       |       |       |       |       |               This command is only for horizontal or vertical addressing mode
                        column start            |       |         column start
                        column end              |       |         column end
------------------------------------------------------------------------------------------------------------------
Set page Address        0x22                    |       |       |       |       |       |       |       |               This command is only for horizontal or vertical addressing mode
                        page start              |       |       |       |       |       |    page start
                        page end                |       |       |       |       |       |    page end
------------------------------------------------------------------------------------------------------------------
Set Page Start Address  0xB0 | page start       |       |       |       |       |       |    page start                 This command is only for page addressing mode
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Set Display Start Line  0x40 | start line       |       |       |          start line
------------------------------------------------------------------------------------------------------------------
Set Segment Re-map      0xA0 | col address      |       |       |       |       |       |       |       | 0: col address = 0 map SEG0
                                                |       |       |       |       |       |       |       | 1: col address = 127 map SEG0
------------------------------------------------------------------------------------------------------------------
Set Multiplex Ratio     0xA8                    |       |       |       |       |       |       |       |
                        multiplex               |       |       |       multiplex : from 0 to 14 are invalid entry
------------------------------------------------------------------------------------------------------------------
Set COM Output          0xC0 | com scan mode    |       |       |       |       | com   |       |       |               0: scan from 0 -> 7
Scan Direction                                  |       |       |       |       |       |       |       |               1: scan from 7 -> 0
------------------------------------------------------------------------------------------------------------------
Set Display Offset      0xD3                    |       |       |       |       |       |       |       |
                        vertical shift          |       |       |             vertical shift
------------------------------------------------------------------------------------------------------------------
Set COM Pins            0xDA                    |       |       |       |       |       |       |       |               5                               4
Hardware                0x02 | c-r | a-c        |       |       |  c-r  |  a-c  |       |       |       |               Enable COM Left/Right remap     Alternative COM pin configuration
Configuration                                   |       |       |       |       |       |       |       |
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Set Display Clock       0xD5                    |       |       |       |       |       |       |       |
Divide                  FOSC | ratio            |           FOSC                |            ratio
Ratio/Oscillator                                |                               |
Frequency                                       |                               |
------------------------------------------------------------------------------------------------------------------
Set Pre-charge Period   0xD9                    |       |       |       |       |       |       |       |
                        phase1 | phase2         |           phase2              |            phase1                     0 is not valid
------------------------------------------------------------------------------------------------------------------
Set VCOMH Deselect      0xDB                    |       |       |       |       |       |       |       |
Level                   level                   |       |        level          |       |       |       |
------------------------------------------------------------------------------------------------------------------
NOP                     0xE3
----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#endif