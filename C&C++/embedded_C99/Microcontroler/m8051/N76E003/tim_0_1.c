//#include <n76e003_regsmap.h>
//
//#pragma vector = TIM0_OV_IRQv
//__interrupt void TIM0_OV()
//{
//  TH0 = (65536 - 1334) >> 8;
//  TL0 = (65536 - 1334) & 0xFF;
//}
//#pragma vector = TIM1_OV_IRQv
//__interrupt void TIM1_OV()
//{
//  TH1 = (65536 - 1334) >> 8;
//  TL1 = (65536 - 1334) & 0xFF;
//}
//
//void TIM0_Init(unsigned char Time)
//{
//  TMOD.REG = BIT0;
////  P2S.BITS.T0OE = 1;
//  TH0 = (65536 - 1334) >> 8;
//  TL0 = (65536 - 1334) & 0xFF;
//
//  IE.BITS.ET0 = 1;
//  TCON.BITS.TR0 = 1;
//  IE.BITS.EA = 1;
//}
//
//void TIM1_Init(unsigned char Time)
//{
//  TMOD.REG = BIT4 | BIT0;
////  P2S.BITS.T1OE = 1;
//  TH1 = (65535 - 1334) >> 8;
//  TL1 = (65535 - 1334) & 0xFF;
//
//  IE.BITS.ET1 = 1;
//  TCON.BITS.TR1 = 1;  
//  IE.BITS.EA = 1;
//}