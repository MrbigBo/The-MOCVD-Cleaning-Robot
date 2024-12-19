/***************************************
 * 文件名  ：usart2.c
 * 描述    ：配置USART1         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA2  - USART1(Tx)      |
 *          | PA3  - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.0.0  

**********************************************************************************/
#include "usart1.h"
#include <stdarg.h>

void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 USART2 时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); 

	/* USART2 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	  
	/* USART2 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);  //初始化USART2
	USART_Cmd(USART2, ENABLE);// USART2使能
}

 void UART2SendByte(unsigned char SendData)
{	   
		USART_SendData(USART2,SendData);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
}  
unsigned char UART2GetByte(unsigned char* GetData)
{   	   
		if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
			{  return 0;//没有收到数据 
			}
		*GetData = USART_ReceiveData(USART2); 
		return 1;//收到数据
}