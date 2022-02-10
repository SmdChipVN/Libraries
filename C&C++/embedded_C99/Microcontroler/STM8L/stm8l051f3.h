/*
  +Low-density, 8 KB flash, 256 byte eeprom, 1 KB ram
  +RTC (low power)
  +DMA:
      -4 channels supporting ADC, SPI, I2C, USART, timers
      -1 channel for memory-to-memory
  +12-bit ADC up to 1 Msps/10 channels
  +Timers:
      -Two 16-bit timers with 2 channels (used as IC, OC, PWM), quadrature encoder
      -One 8-bit timer with 7-bit prescaler
      -2 watchdogs: 1 Window, 1 Independent
      -Beeper timer with 1, 2 or 4 kHz frequencies
  +Communication interfaces:
      -SPI
      -Fast I2C 400 kHz SMBus and PMBus
      -USART
  +Up to 18 I/Os, all mappable on interrupt vectors
  +Development support:
      -Fast on-chip programming and nonintrusive debugging with SWIM
      -Bootloader using USART
*/

#ifndef _STM8L051F3_REGSMAP_H_
#define _STM8L051F3_REGSMAP_H_

//Interrupt vector numbers
#define FLASH_IRQn              3
#define DMA_CH01_IRQn           4
#define DMA_CH23_IRQn           5
#define RTC_IRQn                6
#define ITC_EXTI_EFPVD_IRQn     7
#define ITC_EXTI_B_IRQn         8
#define ITC_EXTI_D_IRQn         9
#define ITC_EXTI_0_IRQn         10
#define ITC_EXTI_1_IRQn         11
#define ITC_EXTI_2_IRQn         12
#define ITC_EXTI_3_IRQn         13
#define ITC_EXTI_4_IRQn         14
#define ITC_EXTI_5_IRQn         15
#define ITC_EXTI_6_IRQn         16
#define ITC_EXTI_7_IRQn         17
#define CLK_IRQn                19
#define ADC1_IRQn               20
#define TIM2_IRQn               21
#define TIM2_CAPCOM_IRQn        22
#define TIM3_IRQn               23
#define TIM3_CAPCOM_IRQn        24
#define RI_IRQn                 25
#define TIM4_IRQn               27
#define SPI_IRQn                28
#define UART_TX_IRQn            29
#define UART_RX_IRQn            30
#define I2C_IRQn                31
//==============================   GPIO   ==============================================================================
#include <gpio.h>
__root __no_init volatile GPIO_TypeDef GPIOA            @ 0x5000;
__root __no_init volatile GPIO_TypeDef GPIOB            @ 0x5005;
__root __no_init volatile GPIO_TypeDef GPIOC            @ 0x500A;
__root __no_init volatile GPIO_TypeDef GPIOD            @ 0x500F;
//==============================   FLASH   ============================================================================= 
#define EEPROM_SIZE             0xFF
#define EEPROM_BASE_ADDRESS     0x001000
#define FLASH_BASE_ADDRESS      0x008100
#define FLASH_SIZE              0x2000
#include <flash.h>
__root __no_init volatile FLASH_TypeDef FLASH           @ 0x5050;
//==============================    DMA    =============================================================================
#include <dma.h>
__root __no_init volatile DMA_TypeDef DMA1              @ 0x5070;
//==============================  SYSTEM CONFIG  =======================================================================
#include <syscfg.h>
__root __no_init volatile SYSCFG_TypeDef SYSCFG         @ 0x509D;
//==============================    ITC    =============================================================================
#include <itc.h>
__root __no_init volatile ITC_EXTI_TypeDef ITC_EXTI     @ 0x50A0;
#define WFE     ITC_EXTI.WFE
__root __no_init volatile ITC_SPR_TypeDef ITC_SPR       @ 0x7F70;
//==============================   RESET    ============================================================================
#include <rst.h>
__root __no_init volatile RST_TypeDef RST               @ 0x50B0;
//==============================   POWRR    ============================================================================
#include <pwr.h>
__root __no_init volatile PWR_TypeDef PWR               @ 0x50B2;
//==============================   CLOCK   =============================================================================
//#define FSYS_DEFAULT            16000000
#include <clk.h>
__root __no_init volatile CLK_TypeDef CLK               @ 0x50C0;
//==============================  WINDOW WATCH DOG  ====================================================================
#include <wwdg.h>
__root __no_init volatile WWDG_TypeDef WWDG             @ 0x50D3;
//==============================   INDEPENDENT WATCHDOG  ===============================================================
#include <iwdg.h>
__root __no_init volatile IWDG_TypeDef IWDG             @ 0x50E0;
//==============================     BEEP  =============================================================================
#include <beep.h>
__root __no_init volatile BEEP_TypeDef BEEP             @ 0x50F0;
//==============================    RTC    =============================================================================
#include <rtc.h>
__root __no_init volatile RTC_TypeDef RTC               @ 0x5140;
//==============================    SPI    =============================================================================
#include <spi.h>
__root __no_init volatile SPI_TypeDef SPI1              @ 0x5200;
//==============================    I2C    =============================================================================
#include <i2c.h>
__root __no_init volatile I2C_TypeDef I2C               @ 0x5210;
//==============================    UART   =============================================================================
#include <uart.h>
__root __no_init volatile UART_TypeDef UART1            @ 0x5230;
//==============================  TIMER GENERAL PURPOSE 16BIT  =========================================================
#include <general_timer.h>
__root __no_init volatile GENERAL_TIMER_TypeDef TIM2    @ 0x5250;
__root __no_init volatile GENERAL_TIMER_TypeDef TIM3    @ 0x5280;
//==============================  BASIC 8 BIT TIMER  ===================================================================
#include <basic_timer.h>
__root __no_init volatile BASIC_TIMER_TypeDef TIM4      @ 0x52E0;
//==============================    IRTIM     ==========================================================================
#include <irtim.h>
__root __no_init volatile IRTIM_TypeDef IRTIM           @ 0x52FF;
//==============================     ADC      ==========================================================================
#include <adc.h>
__root __no_init volatile ADC_TypeDef ADC1              @ 0x5340;
//==============================     RI       ==========================================================================
#include <ri.h>
__root __no_init volatile RI_TypeDef RI                 @ 0x5430;

#endif