#include <beep.h>
#include <clk.h>

void BEEP_Init(unsigned short Frequency)
{
  // switch beep clock to LSI
  CLK.PCKENR1.BITS.BEEP = 1;
  CLK.CBEEPR.BITS.CLKBEEPSEL = 1;
  while (CLK.CBEEPR.BITS.BEEPSWBSY);

  BEEP_SetFrequency(Frequency);
}

void BEEP_SetFrequency(unsigned short Frequency)
{
  if (Frequency < 148 || Frequency > 6333)
    return;
  if (Frequency <= (9500 / 32))
    BEEP.CSR2.REG = (((47500 / Frequency) + 5) / 10) - 2;
  else if (Frequency <= (19000 / 32))
    BEEP.CSR2.REG = BIT6 | ((((95000L / Frequency) + 5) / 10) - 2);
  else
    BEEP.CSR2.REG = BIT7 | ((((190000L / Frequency) + 5) / 10) - 2);
}