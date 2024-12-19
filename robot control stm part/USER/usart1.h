#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

int judJ(void);
void recV(void);
void USART1_Config(void);
void UART1Test(void);
void UART1SendByte(unsigned char SendData);
void USART_Config(void);
void USART1_IRQHandler(void);
void Delay(__IO u32 nCount);
#endif /* __USART1_H */
