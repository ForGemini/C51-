#include<intrins.h>
typedef unsigned char uchar;   
typedef unsigned int uint;

void delayms(uint xms)	//ѭ����ʱXms����
{			  
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void delay_10us()  //��ʱ10us����
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}