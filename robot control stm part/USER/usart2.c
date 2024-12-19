/***************************************
 * �ļ���  ��usart2.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�------------------------
 *          | PA2  - USART1(Tx)      |
 *          | PA3  - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  

**********************************************************************************/
#include "usart1.h"
#include <stdarg.h>

void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART2 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); 

	/* USART2 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART2 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);  //��ʼ��USART2
	USART_Cmd(USART2, ENABLE);// USART2ʹ��
}

 void UART2SendByte(unsigned char SendData)
{	   
		USART_SendData(USART2,SendData);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
}  
unsigned char UART2GetByte(unsigned char* GetData)
{   	   
		if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
			{  return 0;//û���յ����� 
			}
		*GetData = USART_ReceiveData(USART2); 
		return 1;//�յ�����
}