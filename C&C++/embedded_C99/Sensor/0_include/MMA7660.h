#ifndef _MMA7660_H_
#define _MMA7660_H_

#include <define.h>
//                                      //Address       Default         Description
typedef struct                          //0x00
{
  BUNION(, unsigned char,                //              0x00
        Value                   , 5,    //0:4           0
        Negative                , 1,    //4             0
        Alert                   , 1,    //5             0               1: must be read again
        _reserved               , 1) X, Y, Z;
  BUNION(TILT, unsigned char,            //              0x00            Tilt Status
        BaFro                   , 2,    //0-1           0                       0: Unknown condition of front or back
                                        //                                      1: Front: Equipment is lying on its front
                                        //                                      2: Back: Equipment is lying on its back
        PoLa                    , 3,    //2:4           0                       0: Unknown condition of up or down or left or right
                                        //                                      1: Left: Equipment is in landscape mode to the left
                                        //                                      2: Right: Equipment is in landscape mode to the right
                                        //                                      5: Down: Equipment standing vertically in inverted orientation
                                        //                                      6: Up: Equipment standing vertically in normal orientation
        Tap                     , 1,    //5             0               1: Equipment has detected a tap
        Alert                   , 1,    //6             0               1: Re-read the register
        Shake                   , 1);   //7             0               1: Equipment is experiencing shake in one or more of the axes enabled by SHINTX, SHINTY, and SHINTZ
  BUNION(SRST, unsigned char,            //              0x00            Sample Rate Status Register
        AMSRS                   , 1,    //0             0               1: Samples per second specified in AMSR[2:0] is active
        AWSRS                   , 1,    //1             0               1: Samples per second specified in AWSR[1:0] is active
        _reserved               , 6);
  unsigned char SPCNT;                  //              0x00            Sleep Count Register
  BUNION(INTSU, unsigned char,           //              0x00            Interrupt Setup Register
        FB_INT                  , 1,    //0             0               1: Front/Back position change causes an interrupt
        PL_INT                  , 1,    //1             0               1: Up/Down/Right/Left position change causes an interrupt
        PD_INT                  , 1,    //2             0               1: Successful tap detection causes an interrupt
        AS_INT                  , 1,    //3             0               1: Exiting Auto-Sleep causes an interrupt
        G_INT                   , 1,    //4             0               1: There is an automatic interrupt after every measurement
        SH_INT_Z                , 1,    //5             0               1: Shake detected on the X-axis causes an interrupt
        SH_INT_Y                , 1,    //6             0               1: Shake detected on the Y-axis causes an interrupt
        SH_INT_X                , 1);   //7             0               1: Shake detected on the Z-axis causes an interrupt
  BUNION(MODE, unsigned char,            //              0x00            Mode Register
        MODE                    , 1,    //0             0               Active Mode
        _reserved               , 1,
        TON                     , 1,    //2             0               Test Mode
        AWE                     , 1,    //3             0               1: Auto-Wake is enabled
        ASE                     , 1,    //4             0               1: Auto-Sleep is enabled
        SCPS                    , 1,    //5             0               1: Prescaler is divide-by-16
        IPP                     , 1,    //6             0               1: Interrupt output INT is push-pull
        IAH                     , 1);   //7             0               1: Interrupt output INT is active high
  BUNION(SR, unsigned char,              //              0x00            Auto-Wake and Active Mode Portrait/Landscape Samples per Seconds Register
        AMSR                    , 3,    //0:2           0               Samples/Second Active and Auto-Sleep Mode
        AWSR                    , 2,    //3-4           0               Samples/Second Auto-Wake Mode
        FILT                    , 3);   //5:7           0               ?
  BUNION(PDET, unsigned char,            //              0x00            Tap/Pulse Detection Register
        PDTH                    , 5,    //0:4           0               Tap detection threshold
        XDA                     , 1,    //5             0               1: X-axis is disabled for tap detection
        YDA                     , 1,    //6             0
        ZDA                     , 1);   //7             0
  unsigned char PD;                     //              0x00            Tap/Pulse Debounce Count Register
} MMA7760Regs_TypeDef;
//======================================================================================================================
unsigned char MMA7760_Begin();
//======================================================================================================================
unsigned char MMA7760_ReadAxis(MMA7760Regs_TypeDef* MMA7760Regs);        //read only 3 bytes axis
//======================================================================================================================
typedef BUNION(MMA7760_Shake_TypeDef, unsigned char,
              ERROR             , 1,
              X                 , 1,
              Y                 , 1,
              Z                 , 1,
              _reserved         , 4);
MMA7760_Shake_TypeDef MMA7760_ReadShake();
//======================================================================================================================
unsigned char MMA7760_Read(unsigned char* Buffer, unsigned char Length);

#endif