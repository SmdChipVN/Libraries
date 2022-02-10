#ifndef _IAP_H_
#define _IAP_H_

void IAP_AP_ErasePage(unsigned short Address);    //128 bytes
void IAP_Init();
unsigned char IAP_AP_ReadByte(unsigned short Address);
void IAP_AP_WriteByte(unsigned short Address, unsigned char Value);

#endif