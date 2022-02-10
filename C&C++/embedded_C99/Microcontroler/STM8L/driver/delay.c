#include <config.h>

void delay_us(unsigned short time)
{
  while(time--)
  {
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
  }
}

#ifdef DELAY_NORMAL
void delay_ms(unsigned short time)
{
  while (time--)
    delay_us(1000);
}
#endif
#ifdef DELAY_MILLIS_TICK
void delay_ms(unsigned short time)
{
  while (Time--)
  {
    unsigned char millis_lowbit;
    millis_lowbit = ((unsigned char*)&Millis())[3];
    while (millis_lowbit == ((unsigned char*)&Millis())[3]);
  }
}
#endif
#ifdef DELAY_MILLIS_TICK_SLEEP
void delay_ms(unsigned short time)
{
  while (time--)
    asm("WFI");
}
#endif
#ifdef DELAY_RTC_WEAKUP
#include <rtc.h>
void delay_ms(unsigned short time)
{  
  RTC_ConfigTick(false);
  RTC_Weakup(time);
  asm("HALT");
  RTC_DisableWeakup();
  RTC_ConfigTick(true);
}
#endif
#ifdef DELAY_RTOS_NORMAL
void delay_ms(unsigned short time)
{

}
#endif
#ifdef DELAY_RTOS_SLEEP
void delay_ms(unsigned short time)
{

}
#endif