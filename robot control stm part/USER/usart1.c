/***************************************
 * �ļ���  ��usart1.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  

**********************************************************************************/

#include "usart1.h"
#include "misc.h"
#include <stdarg.h>
#include "Site.h"

extern int i;
extern int ena;
extern uint16_t data[];

int p = 0 ;
uint16_t soC[17];
uint16_t reV[8];
uint16_t reC[8] = {0x01 ,0x10 ,0x55 ,0x8C ,0x00 ,0x0C ,0x10 ,0x2B};

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
	
	USART_Config();
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);// USART1ʹ��
}

 /*����һ���ֽ�����*/
 void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*����һ���ֽ�����*/
unsigned char UART1GetByte(unsigned char* GetData)
{   	   
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {  return 0;//û���յ����� 
				}
        *GetData = USART_ReceiveData(USART1); 
        return 1;//�յ�����
}
/*����һ�����ݣ����Ϸ��ؽ��յ����������*/
void UART1Test(void)
{
       unsigned char i = 0;

       while(1)
       {    
				while(UART1GetByte(&i))
        {
         USART_SendData(USART1,i);
        }      
       }     
}

void USART_Config(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure);
	
}

void recV(void)
{
	soC[p] = USART_ReceiveData(USART1);
	p++;
}

int judJ(void)
{
	int u ;
	int i = 0;
	for ( u=0;u<8;u++ )
	{
		if ( reV[u] != reC[u] )
		{
			i++;
		}
	}
	return i;
}
void USART1_IRQHandler(void)
{
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET )
	{
		int j ,v ,l;
		recV();
		if ( (p == 8) && (soC[2] == 0x55) ) 
		{	
			for ( v=0;v<8;v++ )
			{
				reV[v] = soC[v];
			}
			if ( judJ() == 0 )
			{
				i++;
			}
			p = 0;
			for ( j=0;j<8;j++ )
			{
				reV[i] = 0;
			}
		}
		if ( (p == 17) && (soC[2] == 0x0C) )
		{
			for ( l=0;l<17;l++ )
			{
				data[l] = soC[l];
			}
			ena = 1;
			p = 0;
		}
		if (p >= 17)
		{
				p = 0;
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}


void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 








