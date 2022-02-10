#ifndef _STM8S003F3_REGSMAP_H_
#define _STM8S003F3_REGSMAP_H_

#include <common.h>

#define AWU_IRQv                        3
#define CLK_IRQv                        4
#define EXTI_GPIOA_IRQv                 5
#define EXTI_GPIOB_IRQv                 6
#define EXTI_GPIOC_IRQv                 7
#define EXTI_GPIOD_IRQv                 8
#define EXTI_GPIOE_IRQv                 9
#define SPI_IRQv                        12
#define TIM1_OVR_IRQv                   13
#define TIM1_CAPCOM_IRQv                14
#define TIM2_OVR_IRQv                   15
#define TIM2_CAPCOM_IRQv                16
#define UART1_TX_IRQv                   19
#define UART1_RX_IRQv                   20
#define I2C_IRQv                        21
#define ADC1_IRQv                       24
#define TIM4_OVR_IRQv                   25
#define FLASH_IRQv                      26

#include <clk.h>
__no_init volatile CLK_TypeDef CLK              @ 0x50C0;

#include <gpio.h>
__no_init volatile GPIO_TypeDef GPIOA           @ 0x5000;
__no_init volatile GPIO_TypeDef GPIOB           @ 0x5005;
__no_init volatile GPIO_TypeDef GPIOC           @ 0x500A;
__no_init volatile GPIO_TypeDef GPIOD           @ 0x500F;
__no_init volatile GPIO_TypeDef GPIOE           @ 0x5014;
__no_init volatile GPIO_TypeDef GPIOF           @ 0x5019;

#include <beep.h>
__no_init volatile BEEP_TypeDef BEEP            @ 0x50F3;

#include <basic_timer.h>
__no_init volatile BASIC_TIMER_TypeDef TIM4     @ 0x5340;

#include <itc.h>
__no_init volatile ITC_EXTI_TypeDef ITC_EXTI    @ 0x50A0;

#include <adc.h>
__no_init volatile ADC1_TypeDef ADC1            @ 0x53E0;

#include <uart.h>
__no_init volatile UART1_TypeDef UART1          @ 0x5230;

#include <general_timer.h>
__no_init volatile GENERAL_TIMER_TypeDef TIM2   @ 0x5300;

#include <advanced_timer.h>
__no_init volatile ADVANCED_TIMER_TypeDef TIM1  @ 0x5250;

#include <flash.h>
#define EEPROM_BASE_ADDRESS                     0x4000
#define FLASH_BASE_ADDRESS                      0x8000
__no_init volatile FLASH_TypeDef FLASH          @ 0x505A;


#endif