void delay_us(unsigned short Time)
{
  while (Time--)
    asm("NOP");
}

void delay_ms(unsigned short Time)
{
  while (Time--)
    delay_us(1000);
}