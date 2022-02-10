#include <dma.h>

#ifdef DMA_DIRECT
  #define DMA_MASK      DMA_DIRECT
#else
  #define DMA_MASK      (*DMA_Channel)
#endif

#ifdef DMA_DIRECT
void DMA_Init(const DMAInit_TypeDef* DMAInit)
#else
void DMA_Init(volatile DMA_Channel_TypeDef* DMA_Channel, const DMAInit_TypeDef* DMAInit)
#endif
{
  if (!DMAInit)
  {
    static const DMAInit_TypeDef dma_default = {
      .Mode = {.BITS = {.IsReadFromMem = 1, .IsCircleMode = 0, .Mem_IsIncrement = 1, .MemTransfer = 1, .Size = 0, .Priority = 0, },},
      .Interrupt = {.BITS = {.Trans_Complete = 0, .Trans_Half = 0, }, }
    };
    DMAInit = &dma_default;
  }
  DMA_MASK.CR.REG = DMAInit->Mode.REGS.r1 | DMAInit->Interrupt.REG;
  DMA_MASK.SPR.REG = DMAInit->Mode.REGS.r2;
  DMA1.GCSR.BITS.GEN = 1;
}

#ifdef DMA_DIRECT
unsigned char DMA_Transfer(const volatile void* MemPointer, const volatile void* PeriPointer, unsigned char Length)
#else
unsigned char DMA_Transfer(volatile DMA_Channel_TypeDef* DMA_Channel, const volatile void* MemPointer, const volatile void* PeriPointer, unsigned char Length)
#endif
{
  if (DMA_MASK.NDTR)
    return 0;
  DMA_MASK.CR.BITS.EN = 0;
  DMA_MASK.NDTR = Length;
  DMA_MASK.M0AR.REGS.LOW = (unsigned short)MemPointer;
  DMA_MASK.M0AR.REGS.HIGH = ((unsigned short)MemPointer) >> 8;
  DMA_MASK.PAR.REGS.LOW = (unsigned short)PeriPointer;
  DMA_MASK.PAR.REGS.HIGH = ((unsigned short)PeriPointer) >> 8;
  DMA_MASK.CR.BITS.EN = 1;
  return 1;
}