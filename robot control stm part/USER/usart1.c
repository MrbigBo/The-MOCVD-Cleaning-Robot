/***************************************
 * 文件名  ：usart1.c
 * 描述    ：配置USART1         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.0.0  

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

	/* 使能 USART1 时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 使用IO端口配置 */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	  
	/* USART1 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);  //初始化USART1
	
	USART_Config();
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);// USART1使能
}

 /*发送一个字节数据*/
 void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*接收一个字节数据*/
unsigned char UART1GetByte(unsigned char* GetData)
{   	   
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {  return 0;//没有收到数据 
				}
        *GetData = USART_ReceiveData(USART1); 
        return 1;//收到数据
}
/*接收一个数据，马上返回接收到的这个数据*/
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








