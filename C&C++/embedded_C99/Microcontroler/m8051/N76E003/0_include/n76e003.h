#ifndef _N76E003_REGSMAP_H_
#define _N76E003_REGSMAP_H_

#include <base8051.h>

//                                      //Address       Default         Description
SFR(RCTRIM0             , 0x84);        //              0x00            Internal RC trim value high byte
SFRB(RCTRIM1            , 0x85,,         //              0x00            Internal RC trim value low byte     
     HIRCTRIM           , 1,            //0             0               
     _Reserved          , 7);
SFR(RWK                 , 0x86);        //              0x00            Self Wake-up Timer reload byte
SFRB(PCON               , 0x87,,         //              0x00            Power control 
     IDL                , 1,            //0             0               Idle mode
     PD                 , 1,            //1             0               Power-down mode
     GF                 , 2,            //2:3           0               General purpose flag
     POF                , 1,            //4             0               Power-on reset flag
     _Reserved          , 1,
     SMOD0              , 1,            //6             0               Serial port 0 framing error flag access enable
     SMOD               , 1);           //7             0               Serial port 0 double baud rate enable
//----------------------------------------------------------------------------------------------------------------------
SFRB(CKCON              , 0x8E,,         //              0x00            Clock control 
     _Reserved          , 1,
     CLOEN              , 1,            //1             0               System clock output enable
     _Reserved1         , 1,
     T0M                , 1,            //3             0               Timer 0 clock mode select
     T1M                , 1,            //4             0               Timer 1 clock mode select
     _Reserved2         , 1,
     PWMCKS             , 1,            //6             0               PWM clock source select
     _Reserved3         , 1);
SFRB(WKCON              , 0x8F,,         //              0x00            Self Wake-up Timer control 
     WKPS               , 3,            //0:2           0               WKT pre-scalar
     WKTR               , 1,            //3             0               WKT run control
     WKTF               , 1,            //4             0               WKT overflow flag
     _Reserved          , 3);
//----------------------------------------------------------------------------------------------------------------------
SFRB(SFRB               , 0x91,,         //              0x00            SFR page selection (TA Protection)
    SFRPSEL             , 1,            //0             0               SFR page select
    _Reserved           , 7);
SFRB(CAPCON0            , 0x92,,         //              0x00            Input capture control 0 
     CAPF0              , 1,            //0             0               Input capture 0 flag
     CAPF1              , 1,            //1             0               Input capture 1 flag
     CAPF2              , 1,            //2             0               Input capture 2 flag
     _Reserved          , 1,
     CAPEN0             , 1,            //4             0               Input capture 0 enable
     CAPEN1             , 1,            //5             0               Input capture 1 enable
     CAPEN2             , 1,            //6             0               Input capture 2 enable
     _Reserved1         , 1);
SFRB(CAPCON1            , 0x93,,         //              0x00            Input capture control 1
     CAP0LS             , 2,            //0:1           0               Input capture 0 level select
     CAP1LS             , 2,            //2:3           0               Input capture 1 level select
     CAP2LS             , 2,            //4:5           0               Input Capture Control 1
     _Reserved          , 2);
SFRB(CAPCON2            , 0x94,,         //              0x00            Input capture control 2
     _Reserved          , 4,
     ENF0               , 1,            //              0               Enable noise filer on input capture 0
     ENF1               , 1,            //              0               Enable noise filer on input capture 1
     ENF2               , 1,            //              0               Enable noise filer on input capture 2
     _Reserved1         , 1);
SFR(CKDIV               , 0x95);        //              0x00            Clock divider
SFRB(CKSWT              , 0x96,,         //              0x30            Clock switch (TA Protection)
     _Reserved          , 1,
     OSC                , 2,            //              0               Oscillator selection bits
     const ECLKST       , 1,            //              0               External clock input status
     _Reserved1         , 1,
     const HIRCST       , 1,            //              1               High-speed internal oscillator 16 MHz status
     _Reserved2         , 2);
SFRB(CKEN               , 0x97,,         //              0x30            Clock enable (TA Protection)
     const CKSWTF       , 1,            //              0               Clock switch fault flag
     _Reserved          , 4,
     HIRCEN             , 1,            //              1               High-speed internal oscillator 16 MHz enable
     EXTEN              , 2);           //              0               External clock source enable
//----------------------------------------------------------------------------------------------------------------------      
SFR(SBUF_1              , 0x9A);        //              0x00            Serial port 1 data buffer
SFRB(EIE                , 0x9B,,         //              0x00            Extensive interrupt enable 
     EI2C               , 1,            //              0               Enable I2C interrupt
     EPI                , 1,            //              0               Enable pin interrupt
     ECAP               , 1,            //              0               Enable input capture interrupt
     EPWM               , 1,            //              0               Enable PWM interrupt
     EWDT               , 1,            //              0               Enable WDT interrupt
     EFB                , 1,            //              0               Enable Fault Brake interrupt
     ESPI               , 1,            //              0               Enable SPI interrupt
     ET2                , 1);           //              0               Enable Timer 2 interrupt
SFRB(EIE1               , 0x9C,,         //              0x00            Extensive interrupt enable 1
     ES_1               , 1,            //              0               Enable serial port 1 interrupt
     ET3                , 1,            //              0               Enable Timer 3 interrupt
     EWKT               , 1,            //              0               Enable WKT interrupt
     _Reserved          , 5);
SFRB(CHPCON             , 0x9F,,         //              0x00            Chip control (TA Protection)
     IAPEN              , 1,            //              0               IAP enable
     BS                 , 1,            //              0               Boot select
     _Reserved          , 4,
     IAPFF              , 1,            //              0               IAP fault flag
     SWRST              , 1);           //              0               Software reset
//----------------------------------------------------------------------------------------------------------------------
SFRB(AUXR1              , 0xA2,,         //              0x00            Auxiliary register 1
     DPS                , 1,            //              0               Data pointer select
     _Reserved          , 1,
     UART0PX            , 1,            //              0               Serial port 0 pin exchange
     GF2                , 1,            //              0               General purpose flag 2
     _Reserved1         , 1,
     HardF              , 1,            //              0               Hard Fault reset flag
     RSTPINF            , 1,            //              0               External reset flag
     SWRF               , 1);           //              0               Software reset flag
SFRB(BODCON0            , 0xA3,,         //              0x00            Brown-out detection control 0 (TA Protection)
     const BOS          , 1,            //              0               Brown-out status
     BORF               , 1,            //              0               Brown-out reset flag
     BORST              , 1,            //              0               Brown-out reset enable
     BOF                , 1,            //              0               Brown-out interrupt flag
     BOV                , 2,            //              0               Brown-out voltage select
     BODEN              , 1);           //              0               Brown-out detection enable
SFRB(IAPTRG             , 0xA4,,         //              0x00            IAP trigger (TA Protection)
    IAPGO               , 1,            //              0               IAP begins by setting this bit as logic 1
    _Reserved           , 7);
SFRB(IAPUEN             , 0xA5,,         //              0x00            IAP update enable (TA Protection)
     APUEN              , 1,            //              0               APROM updated enable
     LDUEN              , 1,            //              0               LDROM updated enable
     CFUEN              , 1,            //              0               CONFIG bytes updated enable
     _Reserved          , 5);
SFR(IAPAL               , 0xA6);        //              0x00            IAP address low byte
SFR(IAPAH               , 0xA7);        //              0x00            IAP address high byte
//----------------------------------------------------------------------------------------------------------------------
SFRB(IE                 , 0xA8,,         //              0x00            Interrupt enable 
     EX0                , 1,            //              0               Enable external interrupt 0
     ET0                , 1,            //              0               Enable Timer 0 interrupt
     EX1                , 1,            //              0               Enable external interrupt 1
     ET1                , 1,            //              0               Enable Timer 1 interrupt
     ES                 , 1,            //              0               Enable serial port 0 interrupt
     EBOD               , 1,            //              0               Enable brown-out interrupt
     EADC               , 1,            //              0               Enable ADC interrupt
     EA                 , 1);           //              0               Enable all interrupt
SFR(SADDR               , 0xA9);        //              0x00            Slave 0 address
SFRB(WDCON              , 0xAA,,         //              0x00            Watchdog Timer control (TA Protection)
     WDPS               , 3,            //              0               WDT clock pre-scalar select
     WDTRF              , 1,            //              0               WDT reset flag
     WIDPD              , 1,            //              0               WDT running in Idle or Power-down mode
     WDTF               , 1,            //              0               WDT time-out flag
     WDCLR              , 1,            //              0               WDT clear
     WDTR               , 1);           //              0               WDT run
SFRB(BODCON1            , 0xAB,,         //              0x00            Brown-out detection control 1 (TA Protection)
     BODFLT             , 1,            //              0               BOD filter control
     LPBOD              , 2,            //              0               Low power BOD enable
     _Reserved          , 5);
SFRxB(P3M1         , 0xAC,, 0, 7, 1);  //              0x01            P3 mode select 1
SFRxB(P3S          , 0xAC,, 0, 7, 1);  //              0x00            P3 Schmitt trigger input (Page1)
SFRxB(P3M2         , 0xAD,, 0, 7, 1);  //              0x00            P3 mode select 2
SFRxB(P3SR         , 0xAD,, 0, 7, 1);  //              0x00            P3 slew rate (Page1)
SFR(IAPFD               , 0xAE);        //              0x00            IAP flash data
SFRB(IAPCN              , 0xAF,,        //              0x30            IAP control
     FCTRL              , 4,            //              0               
     FCEN               , 1,            //              1               
     FOEN               , 1,            //              1               
     IAPA               , 2);           //              0               
//----------------------------------------------------------------------------------------------------------------------
SFRxB(P0M1          , 0xB1,, 0, 7, 1);  //              0xFF            P0 mode select 1
SFRxB(P0S           , 0xB1,, 0, 7, 1);  //              0x00            P0 Schmitt trigger input (Page1)
SFRxB(P0M2          , 0xB2,, 0, 7, 1);  //              0x00            P0 mode select 2
SFRxB(P0SR          , 0xB2,, 0, 7, 1);  //              0x00            P0 slew rate  (Page1)
SFRxB(P1M1          , 0xB3,, 0, 7, 1);  //              0xFF            P1 mode select 1
SFRxB(P1S           , 0xB3,, 0, 7, 1);  //              0x00            P1 Schmitt trigger input (Page1)
SFRxB(P1M2          , 0xB4,, 0, 7, 1);  //              0x00            P1 mode select 2
SFRxB(P1SR          , 0xB4,, 0, 7, 1);  //              0x00            P1 slew rate (Page1)
SFRB(P2S                , 0xB5,,         //              0x00            P20 Setting and Timer0/1 Output Enable
     P2S0               , 1,            //              0               P2.0 Schmitt triggered input
     _Reserved          , 1,
     T0OE               , 1,            //              0               Timer 0 output enable
     T1OE               , 1,            //              0               Timer 1 output enable
     _Reserved1         , 3,
     P20UP              , 1);           //              0               P2.0 pull-up enable
SFRB(IPH                , 0xB7,,         //              0x00            Interrupt priority high
     PX0H               , 1,            //              0               External interrupt 0 priority high bit
     PT0H               , 1,            //              0               Timer 0 interrupt priority high bit
     PX1H               , 1,            //              0               External interrupt 1 priority high bit
     PT1H               , 1,            //              0               Timer 1 interrupt priority high bit
     PSH                , 1,            //              0               Serial port 0 interrupt priority high bit
     PBODH              , 1,            //              0               Brown-out detection interrupt priority high bit
     PADCH              , 1,            //              0               ADC interrupt priority high bit
     _Reserved          , 1);
SFRB(PWMINTC            , 0xB7,,         //              0x00            PWM Interrupt Control (Page1)
     INTSEL             , 1,            //              0               PWM interrupt pair select
     _Reserved          , 1,
     INTTYP             , 2,            //              0               PWM interrupt type select
     _Reserved1         , 2);
//----------------------------------------------------------------------------------------------------------------------
SFRB(IP                 , 0xB8,,         //              0x00            Interrupt priority
     PX0                , 1,            //              0               External interrupt 0 priority low bit
     PT0                , 1,            //              0               Timer 0 interrupt priority low bit
     PX1                , 1,            //              0               External interrupt 1 priority low bit
     PT1                , 1,            //              0               Timer 1 interrupt priority low bit
     PS                 , 1,            //              0               Serial port 0 interrupt priority low bit
     PBOD               , 1,            //              0               Brown-out detection interrupt priority low bit
     PADC               , 1,            //              0               ADC interrupt priority low bit
     _Reserved          , 1);
SFR(SADEN               , 0xB9);        //              0x00            Slave 0 address mask
SFR(SADEN_1             , 0xBA);        //              0x00            Slave 1 address mask
SFR(SADDR_1             , 0xBB);        //              0x00            Slave 1 address
SFR(I2DAT               , 0xBC);        //              0x00            I2C data
SFRB(const I2STAT       , 0xBD,,         //              0xF8            I2C status
     _Reserved          , 2,
     const I2STAT       , 5);           //              0x1F            I2C status code
SFR(I2CLK               , 0xBE);        //              0x09            I2C clock
SFRB(I2TOC              , 0xBF,,         //              0x00            I2C time-out counter
     I2TOF              , 1,            //              0               I2C time-out flag
     DIV                , 1,            //              0               I2C time-out counter clock divider
     I2TOCEN            , 1,            //              0               I2C time-out counter enable
     _Reserved          , 5);
//----------------------------------------------------------------------------------------------------------------------
SFRB(I2CON              , 0xC0,,         //              0x00            I2C control
     I2CPX              , 1,            //              0               I2C pins select
     _Reserved          , 1,
     AA                 , 1,            //              0               Acknowledge assert flag
     SI                 , 1,            //              0               I2C interrupt flag
     STO                , 1,            //              0               STOP flag
     STA                , 1,            //              0               START flag
     I2CEN              , 1,            //              0               I2C bus enable
     _Reserved1         , 1);
SFRB(I2ADDR             , 0xC1,,         //              0x00            I2C own slave address
     GC                 , 1,            //              0               General Call bit
     ADDR               , 7);           //              0               I2C device’s own slave address
SFR(const ADCRL         , 0xC2);        //              0x00            ADC result low byte
SFR(const ADCRH         , 0xC3);        //              0x00            ADC result high byte
SFRB(T3CON              , 0xC4,,         //              0x00            Timer 3 control 
     T3PS               , 3,            //              0               Timer 3 pre-scalar
     TR3                , 1,            //              0               Timer 3 run control
     TF3                , 1,            //              0               Timer 3 overflow flag
     BRCK               , 1,            //              0               Serial port 0 baud rate clock source
     SMOD0_1            , 1,            //              0               Serial port 1 framing error access enable
     SMOD_1             , 1);           //              0               Serial port 1 double baud rate enable
SFR(PWM4H               , 0xC4);        //              0x00            PWM4 duty high byte (Page1)
SFR(RL3                 , 0xC5);        //              0x00            Timer 3 reload low byte
SFR(PWM5H               , 0xC5);        //              0x00            PWM5 duty high byte (Page1)
SFR(RH3                 , 0xC6);        //              0x00            Timer 3 reload high byte
SFRB(PIOCON1            , 0xC6,,         //              0x00            PWM I/O switch 1 (Page1)
     _Reserved          , 1,
     PIO11              , 1,            //              0               P1.4/PWM1 pin function select
     PIO12              , 1,            //              0               P0.5/PWM2 pin function select
     PIO13              , 1,            //              0               P0.4/PWM3 pin function select
     _Reserved1         , 1,
     PIO15              , 1,            //              0               P1.5/PWM5 pin function select
     _Reserved2         , 2);
SFR(TA                  , 0xC7);        //              0x00            Timed access protection
//----------------------------------------------------------------------------------------------------------------------
SFRB(T2CON              , 0xC8,,         //              0x00            Timer 2 control
     CM_RL2             , 1,            //              0               Timer 2 compare or auto-reload mode select
     _Reserved          , 1,
     TR2                , 1,            //              0               Timer 2 run control
     _Reserved1         , 4,
     TF2                , 1);           //              0               Timer 2 overflow flag
SFRB(T2MOD              , 0xC9,,         //              0x00            Timer 2 mode
     LDTS               , 2,            //              0               Auto-reload trigger select
     CMPCR              , 1,            //              0               Compare match auto-clear
     CAPCR              , 1,            //              0               Capture auto-clear
     T2DIV              , 3,            //              0               Timer 2 clock divider
     LDEN               , 1);           //              0               Enable auto-reload
SFR(RCMP2L              , 0xCA);        //              0x00            Timer 2 compare low byte
SFR(RCMP2H              , 0xCB);        //              0x00            Timer 2 compare high byte 
SFR(TL2                 , 0xCC);        //              0x00            Timer 2 low byte
SFR(PWM4L               , 0xCC);        //              0x00            PWM4 duty low byte (Page1)
SFR(TH2                 , 0xCD);        //              0x00            Timer 2 high byte
SFR(PWM5L               , 0xCD);        //              0x00            PWM5 duty low byte (Page1)
SFR(ADCMPL              , 0xCE);        //              0x00            ADC compare low byte
SFR(ADCMPH              , 0xCF);        //              0x00            ADC compare high byte
//----------------------------------------------------------------------------------------------------------------------
SFR(PWMPH               , 0xD1);        //              0x00            PWM period high byte
SFR(PWM0H               , 0xD2);        //              0x00            PWM0 duty high byte
SFR(PWM1H               , 0xD3);        //              0x00            PWM1 duty high byte
SFR(PWM2H               , 0xD4);        //              0x00            PWM2 duty high byte
SFR(PWM3H               , 0xD5);        //              0x00            PWM3 duty high byte 
SFRB(PNP                , 0xD6,,         //              0x00            PWM negative polarity 
     PNP0               , 1,            //              0               PWMn negative polarity output enable
     PNP1               , 1,            //              0
     PNP2               , 1,            //              0
     PNP3               , 1,            //              0
     PNP4               , 1,            //              0
     PNP5               , 1,            //              0
    _Reserved           , 2);
SFRB(FBD                , 0xD7,,         //              0x00            Brake data
     FPD0               , 1,            //              0               PWMn Fault Brake data
     FPD1               , 1,            //              0
     FPD2               , 1,            //              0
     FPD3               , 1,            //              0
     FPD4               , 1,            //              0
     FPD5               , 1,            //              0
     FBINLS             , 1,            //              0               FB pin input level selection
     FBF                , 1);           //              0               Fault Brake flag
//----------------------------------------------------------------------------------------------------------------------
SFRB(PWMCON0            , 0xD8,,         //              0x00            PWM control 0
     _Reserved          , 4,
     CLRPWM             , 1,            //              0               Clear PWM counter
     PWMF               , 1,            //              0               PWM flag
     LOAD               , 1,            //              0               PWM new period and duty load
     PWMRUN             , 1);           //              0               PWM run enable
SFR(PWMPL               , 0xD9);        //              0x00            PWM period low byte
SFR(PWM0L               , 0xDA);        //              0x00            PWM0 duty low byte
SFR(PWM1L               , 0xDB);        //              0x00            PWM1 duty low byte
SFR(PWM2L               , 0xDC);        //              0x00            PWM2 duty low byte
SFR(PWM3L               , 0xDD);        //              0x00            PWM3 duty low byte
SFRB(PIOCON0            , 0xDE,,         //              0x00            PWM I/O switch 0
     PIO00              , 1,            //              0               P1.2/PWM0 pin function select
     PIO01              , 1,            //              0               P1.1/PWM1 pin function select
     PIO02              , 1,            //              0               P1.0/PWM2 pin function select
     PIO03              , 1,            //              0               P0.0/PWM3 pin function select
     PIO04              , 1,            //              0               P0.1/PWM4 pin function select
     PIO05              , 1,            //              0               P0.3/PWM5 pin function select
     _Reserved          , 2);
SFRB(PWMCON1            , 0xDF,,         //              0x00            PWM control 1
     PWMDIV             , 3,            //              0               PWM clock divider
     FBINEN             , 1,            //              0               
     PWMTYP             , 1,            //              0               
     GP                 , 1,            //              0               Group mode enable
     PWMMOD             , 2);           //              0               
//----------------------------------------------------------------------------------------------------------------------
SFRB(ADCCON1            , 0xE1,,         //              0x00            ADC control 1
     ADCEN              , 1,            //              0               ADC enable
     ADCEX              , 1,            //              0               ADC external conversion trigger select
     ETGTYP             , 2,            //              0               External trigger type select
     _Reserved          , 2,
     STADCPX            , 1,            //              0               External start ADC trigger pin select
     _Reserved1         , 1);
SFRB(ADCCON2            , 0xE2,,         //              0x00            ADC control 2
     ADCDLY_8           , 1,            //              0               ADC external trigger delay counter bit 8
     _Reserved          , 3,
     const ADCMPO       , 1,            //              0               ADC comparator output value
     ADCMPEN            , 1,            //              0               ADC result comparator enable
     ADCMPOP            , 1,            //              0               ADC comparator output polarity
     ADFBEN             , 1);           //              0               ADC compare result asserting Fault Brake enable
SFR(ADCDLY              , 0xE3);        //              0x00            ADC trigger delay 
SFR(C0L                 , 0xE4);        //              0x00            Input capture 0 low byte
SFR(C0H                 , 0xE5);        //              0x00            Input capture 0 high byte
SFR(C1L                 , 0xE6);        //              0x00            Input capture 1 low byte
SFR(C1H                 , 0xE7);        //              0x00            Input capture 1 high byte
//----------------------------------------------------------------------------------------------------------------------
SFRB(ADCCON0            , 0xE8,,         //              0x00            ADC control 0 
     ADCHS              , 4,            //              0               A/D converting channel select
     ETGSEL             , 2,            //              0               External trigger source select
     ADCS               , 1,            //              0               A/D converting software start trigger
     ADCF               , 1);           //              0               ADC flag
SFRB(PICON              , 0xE9,,         //              0x00            Pin interrupt control
     PIPS               , 2,            //              0               Pin interrupt port select
     PIT0               , 1,            //              0               Pin interrupt channel 0 type select
     PIT1               , 1,            //              0               Pin interrupt channel 1 type select
     PIT2               , 1,            //              0               Pin interrupt channel 2 type select
     PIT3               , 1,            //              0               Pin interrupt channel 3 type select
     PIT45              , 1,            //              0               Pin interrupt channel 4 and 5 type select
     PIT67              , 1);           //              0               Pin interrupt channel 6 and 7 type select
SFRB(PINEN              , 0xEA,,         //              0x00            Pin interrupt low level/falling edge enable
     PINEN0             , 1,            //              0               Pin interrupt channel n negative polarity enable
     PINEN1             , 1,            //              0
     PINEN2             , 1,            //              0
     PINEN3             , 1,            //              0
     PINEN4             , 1,            //              0
     PINEN5             , 1,            //              0
     PINEN6             , 1,            //              0
     PINEN7             , 1);           //              0
SFRB(PIPEN              , 0xEB,,         //              0x00            Pin interrupt high level/rising edge enable
     PINEN0             , 1,            //              0               Pin interrupt channel n positive polarity enable
     PINEN1             , 1,            //              0
     PINEN2             , 1,            //              0
     PINEN3             , 1,            //              0
     PINEN4             , 1,            //              0
     PINEN5             , 1,            //              0
     PINEN6             , 1,            //              0
     PINEN7             , 1);           //              0
SFRB(PIF                , 0xEC,,         //              0x00            Pin interrupt flag
     PIF0               , 1,            //              0               Pin interrupt channel n flag
     PIF1               , 1,            //              0
     PIF2               , 1,            //              0
     PIF3               , 1,            //              0
     PIF4               , 1,            //              0
     PIF5               , 1,            //              0
     PIF6               , 1,            //              0
     PIF7               , 1);           //              0
SFR(C2L                 , 0xED);        //              0x00            Input capture 2 low byte
SFR(C2H                 , 0xEE);        //              0x00            Input capture 2 high byte
SFRB(EIP                , 0xEF,,         //              0x00            Extensive interrupt priority
     PI2C               , 1,            //              0               I2C interrupt priority low bit
     PPI                , 1,            //              0               Pin interrupt priority low bit
     PCAP               , 1,            //              0               Input capture interrupt priority low bit
     PPWM               , 1,            //              0               PWM interrupt priority low bit
     PWDT               , 1,            //              0               WDT interrupt priority low bit
     PFB                , 1,            //              0               Fault Brake interrupt priority low bit
     PSPI               , 1,            //              0               SPI interrupt priority low bit
     PT2                , 1);           //              0               Timer 2 interrupt priority low bit
//----------------------------------------------------------------------------------------------------------------------
SFRB(CAPCON3            , 0xF1,,         //              0x00            Input capture control 3 
     CAP0               , 4,            //              0               Input capture channel 0 input pin select
     CAP1               , 4);           //              0               Input capture channel 1 input pin select
SFRB(CAPCON4            , 0xF2,,         //              0x00            Input capture control 4
     CAP2               , 1,            //              0               Input capture channel 2 input pin select
     _Reserved          , 4);
SFRB(SPCR               , 0xF3,,         //              0x00            SPI control
     SPR                , 2,            //              0               
     CPHA               , 1,            //              0               SPI clock phase select
     CPOL               , 1,            //              0               SPI clock polarity select
     MSTR               , 1,            //              0               Master mode enable
     LSBFE              , 1,            //              0               LSB first enable
     SPIEN              , 1,            //              0               SPI enable
     SSOE               , 1);           //              0               Slave select output enable
SFRB(SPCR2              , 0xF3,,         //              0x00            SPI control 2 (Page1)
     SPIS               , 2,            //              0               SPI Interval time selection between adjacent bytes
     _Reserved          , 6);
SFRB(SPSR               , 0xF4,,         //              0x00            SPI status
     _Reserved          , 2,
     const TXBUF        , 1,            //              0               SPI writer data buffer status
     DISMODF            , 1,            //              0               Disable Mode Fault error detection
     MODF               , 1,            //              0               Mode Fault error flag
     SPIOVF             , 1,            //              0               SPI overrun error flag
     WCOL               , 1,            //              0               Write collision error flag
     SPIF               , 1);           //              0               SPI complete flag
SFR(SPDR                , 0xF5);        //              0x00            SPI data
SFRB(AINDIDS            , 0xF6,,         //              0x00            ADC channel digital input disable
     P17DIDS            , 1,            //              0               ADC Channel digital input disable
     P30DIDS            , 1,            //              0
     P07DIDS            , 1,            //              0
     P06DIDS            , 1,            //              0
     P05DIDS            , 1,            //              0
     P04DIDS            , 1,            //              0
     P03DIDS            , 1,            //              0
     P11DIDS            , 1);           //              0
SFRB(EIPH               , 0xF7,,         //              0x00            Extensive interrupt priority high
     PI2CH              , 1,            //              0               I2C interrupt priority high bit
     PPIH               , 1,            //              0               Pin interrupt priority high bit
     PCAPH              , 1,            //              0               Input capture interrupt priority high bit
     PPWMH              , 1,            //              0               PWM interrupt priority high bit
     PWDTH              , 1,            //              0               WDT interrupt priority high bit
     PFBH               , 1,            //              0               Fault Brake interrupt priority high bit
     PSPIH              , 1,            //              0               SPI interrupt priority high bit
     PT2H               , 1);           //              0               Timer 2 interrupt priority high bit
//----------------------------------------------------------------------------------------------------------------------
SFRB(SCON_1             , 0xF8,,         //              0x00            Serial port 1 control
     RI_1               , 1,            //              0               Receiving interrupt flag
     TI_1               , 1,            //              0               Transmission interrupt flag
     RB8_1              , 1,            //              0               9th received bit
     TB8_1              , 1,            //              0               9th transmitted bit
     REN_1              , 1,            //              0               Receiving enable
     SM2_1              , 1,            //              0               
     SM1_1              , 1,            //              0               
     SM0_1              , 1);           //              0               
SFRB(PDTEN              , 0xF9,,         //              0x00            PWM dead-time enable (TA Protection)
     PDT01EN            , 1,            //              0               PWM0/1 pair dead-time insertion enable
     PDT23EN            , 1,            //              0               PWM2/3 pair dead-time insertion enable
     PDT45EN            , 1,            //              0               PWM4/5 pair dead-time insertion enable
     _Reserved          , 1,
     PDTCNT_8           , 1,            //              0               PWM dead-time counter bit 8
     _Reserved1         , 3);
SFR(PDTCNT              , 0xFA);        //              0x00            PWM dead-time counter (TA Protection)
SFRB(PMEN               , 0xFB,,         //              0x00            PWM mask enable
     PMEN0              , 1,            //              0               PWMn mask enable
     PMEN1              , 1,            //              0
     PMEN2              , 1,            //              0
     PMEN3              , 1,            //              0
     PMEN4              , 1,            //              0
     PMEN5              , 1,            //              0
     _Reserved          , 2);
SFRB(PMD                , 0xFC,,         //              0x00            PWM mask data
     PMD0               , 1,            //              0               PWMn mask data
     PMD1               , 1,            //              0
     PMD2               , 1,            //              0
     PMD3               , 1,            //              0
     PMD4               , 1,            //              0
     PMD5               , 1,            //              0
     _Reserved          , 2);
SFR(PORDIS              , 0xFD);        //              0x00            POR disable (TA protected)
SFRB(EIP1               , 0xFE,,         //              0x00            Extensive interrupt priority 1
     PS_1               , 1,            //              0               Serial port 1 interrupt priority low bit
     PT3                , 1,            //              0               Timer 3 interrupt priority low bit
     PWKT               , 1,            //              0               WKT interrupt priority low bit
     _Reserved          , 5);
SFRB(EIPH1              , 0xFF,,         //              0x00            Extensive interrupt priority high 1
     PSH_1              , 1,            //              0               Serial port 1 interrupt priority high bit
     PT3H               , 1,            //              0               Timer 3 interrupt priority high bit
     PWKTH              , 1,            //              0               WKT interrupt priority high bit
     _Reserved          , 5);
//----------------------------------------------------------------------------------------------------------------------
#define EXTI0_IRQv      0x03
#define TIM0_OV_IRQv    0x0B
#define EXTI1_IRQv      0x13
#define TIM1_OV_IRQv    0x1B
#define UART0_IRQv      0x23
#define TIM2_EV_IRQv    0x2B
#define I2C_IRQv        0x33
#define PIN_IRQv        0x3B
#define BROWN_OUT_IRQv  0x43
#define SPI_IRQv        0x4B
#define WDT_IRQv        0x53
#define ADC_IRQv        0x5B
#define INCAP_IRQv      0x63
#define PWM_IRQv        0x6B
#define FAULT_BRK_IRQv  0x73
#define UART1_IRQv      0x7B
#define TIM3_OV_IRQv    0x83
#define WEAKUP_IRQv     0x8B

#endif