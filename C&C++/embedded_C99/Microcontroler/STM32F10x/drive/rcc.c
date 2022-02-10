#include <rcc.h>
#include <bitband.h>

void RCC_Init(volatile RCC_TypeDef* RCC, const RCCInit_TypeDef* RCCInit)
{
  if (!RCCInit)    
  {
    static const RCCInit_TypeDef rcc_init_default = {
      .Source = RCC_SOURCE_HSI,
      .PLL = {.BITS = { .Source = PLL_SOURCE_HSI_DIV_2, .Multiple = 1, }},      //Real multiple += 2
      .Prescale = {.BITS = { .AHB = AHB_PRESCALE_1, .APB1 = APB_PRESCALE_2, .APB2 = APB_PRESCALE_1, .ADC = ADC_PRESCALE_2, .USB_NotDiv = 1, }},
    };
    RCCInit = &rcc_init_default;
  }
  //disable peripheral
  unsigned int ahb_en = RCC->AHB_ENR.REG;
  unsigned int apb1_en = RCC->APB1_ENR.REG;
  unsigned int apb2_en = RCC->APB2_ENR.REG;
  RCC->AHB_ENR.REG = 0;
  RCC->APB1_ENR.REG = 0;
  RCC->APB2_ENR.REG = 0;
  //switch system clock to hsi
  RCC_BITBAND_TypeDef* RCC_BITBAND = (RCC_BITBAND_TypeDef*)BITBAND_PERIPHERAL_POINTER((unsigned int)RCC, 0);
  RCC_BITBAND->CR.HSION = 1;
  while (!RCC_BITBAND->CR.HSI_RDY);
  RCC->CFGR.BITS.SW = RCC_SOURCE_HSI;
  while (RCC->CFGR.BITS.SWS != RCC_SOURCE_HSI);
  //config prescale & pll
  RCC_BITBAND->CR.PLL_ON = 0;
  RCC_BITBAND->CR.HSE_ON = 0;
  RCC->CFGR.REG &= ~BIT(4, 22);
  RCC->CFGR.REG |= RCCInit->Prescale.REG | RCCInit->PLL.REG;
  //config rcc source
  if (RCCInit->Source)
  {
    if (RCCInit->Source == RCC_SOURCE_HSE || RCCInit->PLL.BITS.Source)
    {
      RCC_BITBAND->CR.HSE_ON = 1;
      while (!RCC_BITBAND->CR.HSE_RDY);
    }
    if (RCCInit->Source == RCC_SOURCE_HSE)
    {
      RCC->CFGR.BITS.SW = RCC_SOURCE_HSE;
      while (RCC->CFGR.BITS.SWS != RCC_SOURCE_HSE);
      RCC_BITBAND->CR.HSION = 0;
    }
    else
    {
      RCC_BITBAND->CR.PLL_ON = 1;
      while (!RCC_BITBAND->CR.PLL_RDY);
      RCC->CFGR.BITS.SW = RCC_SOURCE_PLL;
      while (RCC->CFGR.BITS.SWS != RCC_SOURCE_PLL);
      if (RCCInit->PLL.BITS.Source)
        RCC_BITBAND->CR.HSION = 0;
    }
  }
  //back-up peripheral
  RCC->AHB_ENR.REG = ahb_en;
  RCC->APB1_ENR.REG = apb1_en;
  RCC->APB2_ENR.REG = apb2_en;
}