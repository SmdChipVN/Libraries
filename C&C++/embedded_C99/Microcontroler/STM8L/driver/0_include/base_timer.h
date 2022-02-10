#ifndef _BASE_TIMER_H
#define _BASE_TIMER_H

//======================================================================================================================
/*
+) NOTE:
  -IRQ function must clear flag
*/
#define BASE_TIMER_EnableInterrupt(TIMER)       (TIMER)->IER.REG=1
#define BASE_TIMER_DisableInterrupt(TIMER)      (TIMER)->IER.REG=0
//======================================================================================================================
#define BASE_TIMER_EnableDMA(TIMER)             (TIMER)->DIER.REG=1
#define BASE_TIMER_DisableDMA(TIMER)            (TIMER)->DIER.REG=0
//======================================================================================================================

#endif