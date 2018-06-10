#include<reg52.h>

typedef unsigned char uchar; 
typedef unsigned int uint;
typedef unsigned long ulong;
sbit dat=P3^7;	  //datΪDHT11�������ݽӿ�
sbit led1=P1^0;
sbit led2=P1^2;
sbit led3=P1^4;
sbit led4=P1^6;


uchar rec_data[10];

void delayms(uint xms);
void delay_10us();
void sent(uchar code str[]);
void display(uint w1,uint w2,uint w3,uint w4);

char temp_init_l,temp_init_h,humi_init_l,humi_init_h,\
temp_l,temp_h,humi_l,humi_h,data_check;

void dht11_start()
{
	dat=1;
	delay_10us;	// ��ʱ10us
	dat=0;
	delayms(20);
	dat=1;
	delay_10us(); //��������40us
	delay_10us();
	delay_10us();
	delay_10us();
	//dat=1;
 	/*while(dat);
	delay_10us();  //DHT��Ӧ80us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	while(!dat);
	delay_10us();  //DHT����80us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	 */
} 

void dht11_over()	//����ͨ��
{	
	delay_10us();	  //��ʱ50us
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	dat=1;
}  	   

char dht11_data_analyse()
{
	uchar i,data_analyse=0;
	for(i=0;i<8;i++)
	{
		while(!dat);
		data_analyse=data_analyse<<1;
		delay_10us();    //��ʱ50us����dat��Ϊ����˵������Ϊ1������Ϊ0
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		if(dat)		 //�ж�����Ϊ1����Ϊ0
			data_analyse=data_analyse+1;   //����Ϊ1ʱ��ʹdat��1����������1
		while(dat);	
	}

	return data_analyse;
}

void dht11_data_read()
{
	dht11_start();
	led1=dat;				//���ָʾ1
	if(!dat)
	{
		led2=0;           //���ָʾ��2
		while(!dat);
		led3=0;       //���ָʾ��3
		delay_10us();    //��ʱ80us
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();    
		delay_10us();
		delay_10us();
		humi_init_h=dht11_data_analyse();
		humi_init_l=dht11_data_analyse();
		temp_init_h=dht11_data_analyse();
		temp_init_l=dht11_data_analyse();
		data_check=dht11_data_analyse();

		dht11_over();    
		led4=0;       //���ָʾ��4
		if((humi_init_h+humi_init_l+temp_init_h+temp_init_l)==data_check)	//����У��
		{
			humi_h=humi_init_h;
			humi_l=humi_init_l;
			temp_h=temp_init_h;
			temp_l=temp_init_l;	
			
		}
		rec_data[0]='0'+(humi_h/10);	  //�����ݴ����������У����㷢�͸�����
 	  	rec_data[1]='0'+(humi_h%10);
 	  	rec_data[2]='R';
 	   	rec_data[3]='H';
	    rec_data[4]=' ';
 	  	rec_data[5]=' ';
 	  	rec_data[6]='0'+(temp_h/10);
	   	rec_data[7]='0'+(temp_h%10);
	    rec_data[8]='C';

	}
		
}

void main()
{
	while(1)
	{
		uint w1,w2,w3,w4;	
		delayms(1000);
		dht11_data_read();
		sent(rec_data);	  //���ڷ��ͺ���
		while(1);
	}	
}	