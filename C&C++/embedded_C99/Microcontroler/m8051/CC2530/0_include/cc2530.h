#ifndef _CC2530_H_
#define _CC2530_H_

#include <clock.h>
#include <gpio.h>
#include <flash.h>

#include <timer_8bit.h>

#include <aes.h>

#include <interrupt.h>
#include <cpu.h>


//#define RFERR_IRQn      0
//#define RFERR_IRQv      0x03
//
//#define T3_IRQn         11
//#define T3_IRQv         0x5B


#include <radio.h>
__root __no_init __xdata volatile RADIO_TypeDef RADIO           __at(0x6000);

#endif