#include <adc.h>
#include <common.h>

void ADC_Init(volatile ADC1_TypeDef* ADC1)
{
  ADC1->CR3.REG = 0;
  ADC1->CR2.REG = BIT3;  
}

void ADC_Start(volatile ADC1_TypeDef* ADC1, unsigned char Channel)
{
  ADC1->CSR.REG = Channel;
  ADC1->CR1.REG = BIT0;
  ADC1->CR1.REG = BIT0;
}