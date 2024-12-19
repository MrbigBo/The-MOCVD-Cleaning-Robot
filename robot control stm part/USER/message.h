#ifndef __MESSAGE_H
#define	__MESSAGE_H

#include "stm32f10x.h"
#include <stdio.h>

void mess(int32_t arr[] , uint16_t *buf);
unsigned int crc16(uint16_t buf[] , int len);
void comb(unsigned int crc16 , uint16_t *buf);

#endif /* __MESSAGE_H */
