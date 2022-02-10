#ifndef _GPIO_H_
#define _GPIO_H_

typedef enum
{
  GPIO_MODE_QUASI       = 0,
  GPIO_MODE_PUSHPULL    = 1,
  GPIO_MODE_INPUT       = 2,
  GPIO_MODE_OPEN_DRAIN  = 3,
} GPIO_MODE;

void GPIO0_Mode(unsigned char PIN, GPIO_MODE Mode);
void GPIO1_Mode(unsigned char PIN, GPIO_MODE Mode);
void GPIO3_Mode(unsigned char PIN, GPIO_MODE Mode);

#define GPIO_Mode(port,PIN,mode)        GPIO##port##_Mode(PIN,mode)

#endif