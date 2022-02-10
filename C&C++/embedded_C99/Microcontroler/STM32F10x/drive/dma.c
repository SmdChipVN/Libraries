#include <dma.h>
#include <common.h>

void DMA_Init(volatile DMAChannel_TypeDef* DMAChannel, const DMAInit_TypeDef* DMAInit)
{
  if (!DMAInit)
  {
    static const DMAInit_TypeDef dma_default = {
      .Mode = {.BITS = {.IsReadFromMem = 0, .IsCircleMode = 0, .Peri_IsIncrement = 0, .Mem_IsIncrement = 0, .Peri_Size = 0, .Mem_Size = 0, .PriorityLevel = 0, .IsMemToMem = 0, }},
      .Interrupt = {.BITS = {.Trans_Compelete = 0, .HalfTrans = 0, .Error = 0, }},
    };
    DMAInit = &dma_default;
  }
  DMAChannel->CCR.REG = DMAInit->Interrupt.REG | DMAInit->Mode.REG;
}

void DMA_Transfer(volatile DMAChannel_TypeDef* DMAChannel, volatile void* MemPointer, volatile void* PeriPointer, unsigned int Length)
{
  DMAChannel->CCR.BITS.EN = 0;
  DMAChannel->CNDTR = Length;
  DMAChannel->CMAR = (unsigned int)MemPointer;
  DMAChannel->CPAR = (unsigned int)PeriPointer;
  DMAChannel->CCR.BITS.EN = 1;
}