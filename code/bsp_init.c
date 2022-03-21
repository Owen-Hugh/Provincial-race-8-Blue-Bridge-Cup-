#include "bsp_init.h"

//这个数组用于位选,只给一个引脚高电平
const char which[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//段选,根据数字编码
const char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xbf};

sbit ch138_C = P2 ^ 7;
sbit ch138_B = P2 ^ 6;
sbit ch138_A = P2 ^ 5;

/*
38译码器选择
0:no choose
4:LED
5:buzz
6:位选
7段选
*/
void HC138(unsigned char n)
{
	switch (n)
	{
	case /* constant-expression */ 0:
		/* code */
		ch138_C = ch138_B = ch138_A = 0;
		break;
	case 4:
		ch138_C = 1;
		ch138_B = ch138_A = 0;
		break;
	case 5:
		ch138_C = ch138_A = 1;
		ch138_B = 0;
		break;
	case 6:
		ch138_C = ch138_B = 1;
		ch138_A = 0;
		break;
	case 7:
		ch138_C = ch138_B = ch138_A = 1;
	default:
		break;
	}
}

void delay(unsigned int i)
{
	while (i--)
		;
}

//关闭蜂鸣器andLED
void bsp_Init(void)
{
	HC138(4);
	P0 = 0xff;
	HC138(5);
	P0 = 0;
	HC138(0);
}

void dis_smg(unsigned char n, unsigned char m)
{
	HC138(6);
	P0 = which[n - 1];
	HC138(7);
	P0 = num[m];
	delay(100);
	P0 = 0xff;
	delay(10);
	HC138(0);
}