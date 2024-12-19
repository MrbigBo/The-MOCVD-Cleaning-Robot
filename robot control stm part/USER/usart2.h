#ifndef __USART2_H
#define	__USART2_H

#include "stm32f10x.h"
#include <stdio.h>

void USART2_Config(void);
void UART2SendByte(unsigned char SendData);
unsigned char UART2GetByte(unsigned char* GetData);
#endif /* __USART2_H */
