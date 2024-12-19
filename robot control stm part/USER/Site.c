#include "Site.h"
#include "usart1.h"
#include "message.h"
#include "math.h"
#include "stdlib.h"

int ena = 0;
uint16_t data[17];

int reacH( int32_t* slte )
{
	int j , k ;
	int Flag = 0;
	uint16_t ider;
	uint16_t senr[] = { 0x01 , 0x03 , 0x08 , 0xDC , 0x00 , 0x06 , 0x06 , 0x52 };
	Delay(100000);
	for ( j=0;j<8;j ++ )
	{
		Delay(600);
		USART_SendData(USART1 , senr[j]);
	}
	while( ena == 0 );	
	ider = crc16(data , 15);
	if ( ((ider & 0x00ff) == data[15]) && ( ((ider & 0xff00)>>8) == data[16]) )
	{
		Flag = calC( slte , data );
	}
	ena = 0;
	for ( k=0;k<17;k++ )
	{
		data[k] = 0;
	}
	return Flag;
}
int calC( int32_t* slte , uint16_t* sitc )
{
	int x_c , y_c , z_c , x_p , y_p , z_p , x_d , y_d, z_d;
	x_p = ( sitc[3]  << 24 ) |  ( sitc[4]  << 16 ) | ( sitc[5]  << 8 ) | sitc[6]  ;
	y_p = ( sitc[7]  << 24 ) |  ( sitc[8]  << 16 ) | ( sitc[9]  << 8 ) | sitc[10] ;
	z_p = ( sitc[11] << 24 ) |  ( sitc[12] << 16 ) | ( sitc[13] << 8 ) | sitc[14] ;
	x_c = slte[0] ;
	y_c = slte[1] ; 
	z_c = slte[2] ;

	x_d = abs( x_c - x_p );
	y_d = abs( y_c - y_p ); 
	z_d = abs( z_c - z_p ); 
	if ( x_d < 1000 && y_d < 1000 && z_d < 1000 )
	{
		return 1;
	}
	return 0;
}

