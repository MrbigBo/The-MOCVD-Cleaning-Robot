#include "message.h"

void mess(int32_t arr[] , uint16_t *buf)
{
	int i , j , k , m ;
	unsigned int buffer[6][4];
	for ( k = 0;k < 6;k++)
	{
		unsigned int temp_HL = 0xff000000;
		for ( i = 0;i < 4;i++ )
		{
			unsigned int temp_b =  arr[k]  & temp_HL;
			temp_b >>= (3 - i) * 8;
			buffer[k][i] = temp_b;
			temp_HL >>= 8;
		}
	}
	for ( j = 0;j < 6;j++ )
	{
			int lenth = 6 + 4 * j;
			for (m = 1; m < 5; m++)
			{
					buf[m + lenth] = buffer[j][m - 1];
			}
	}
}

unsigned int crc16(uint16_t buf[] , int len)
{
	int i;
	unsigned int crc16 = 0xffff;
	unsigned int temp ;
	
	for ( i = 0; i < len; i++)
	{
		int j ;
		crc16 ^= buf[i];
		for ( j = 0; j < 8; j++)
		{
				temp = (unsigned int)(crc16 & 0x0001);
				crc16 >>= 1;
				if (temp == 1)
				{
						crc16 ^= 0xa001;
				}
		}
	}
	return crc16;
}

void comb(unsigned int crc16 , uint16_t *buf)
{
	uint16_t crc16_H , crc16_L;
	crc16_H = (crc16 & 0x00ff);
	crc16_L = (crc16 & 0xff00) >> 8;
	buf[31] = crc16_H;
	buf[32] = crc16_L;
}


