#include <cortex_m3.h>
#include <rcc.h>

void SystemInit(RCC_TypeDef* RCC)
{
  RCC->CR.REG |= 0x00000001U;
  RCC->CFGR.REG &= 0xF8FF0000U;
  RCC->CR.REG &= 0xFEF6FFFFU;
  RCC->CR.REG &= 0xFFFBFFFFU;
  RCC->CFGR.REG &= 0xFF80FFFFU;
  RCC->CIR.REG = 0x009F0000U;
//#ifdef VECT_TAB_SRAM
//  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
//#else
//  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
//#endif 
}