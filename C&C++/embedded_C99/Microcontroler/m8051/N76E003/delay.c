void delay_us(unsigned char time)
{
  while (time--)
  {
    asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");
    asm("NOP");
  }
}

void delay_ms(unsigned short time)
{
  unsigned short i;
  while (time--)
    for (i = 0; i < 944; i++);  
}