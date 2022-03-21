#include "bsp_init.h"
#include "smg_init.h"
#include "ds1302.h"
#include "time.h"

void Time_LED(void);
unsigned char sec, sce_2;					 //秒 0.2秒
extern unsigned char Time_1[7];				 //当前时间
unsigned char Timer[3] = {0x00, 0x00, 0x00}; //闹钟定时时间设置 00-00-00
unsigned char Key = 0;						 //按键参数

sbit H1 = P3 ^ 2;
sbit H2 = P3 ^ 3;
sbit L1 = P4 ^ 4;
sbit L2 = P4 ^ 2;

void Key_Down(void)
{
	H1 = H2 = L1 = 1;
	L2 = 0;
	if (H1 == 0)
	{
		delay(10);
		if (H1 == 0)
		{
			Key = 9;
			while (!H1)
				;
		}
	}
	if (H2 == 0)
	{
		delay(10);
		if (H2 == 0)
		{
			Key = 8;
			while (!H2)
				;
		}
	}
	H1 = H2 = L2 = 1;
	L1 = 0;
	if (H1 == 0)
	{
		delay(10);
		if (H1 == 0)
		{
			Key = 5;
			while (!H1)
				;
		}
	}
	if (H2 == 0)
	{
		delay(10);
		if (H2 == 0)
		{
			Key = 4;
			while (!H2)
				;
		}
	}
}

/*
	当前时间显示
*/
void smg_timing()
{
	dis_smg(1, Time_1[2] / 16);
	dis_smg(2, Time_1[2] % 16);
	dis_smg(3, 10);
	dis_smg(6, 10);
	dis_smg(4, Time_1[1] / 16);
	dis_smg(5, Time_1[1] % 16);
	dis_smg(7, Time_1[0] / 16);
	dis_smg(8, Time_1[0] % 16);
}

void main(void)
{
	bsp_Init();
	DS1302_Init();
	Timer0Init();
	DS1302_Read();
	while (1)
	{
		if (Timer[2] == Time_1[2] && Timer[1] == Time_1[1] && Timer[0] == Time_1[0])
		{
			sec = 0;
			while (sec < 5)
			{
				Time_LED();
				/* code */
				Key_Down();
				if (Key != 0)
					break;
			}
		}
	}
}

/*闹钟提醒*/
void Time_LED(void)
{
	HC138(4);
	if (sce_2 % 2)
	{
		P0 = 0xfe;
	}
	else if (!(sce_2 % 2))
	{
		P0 = 0xff;
	}

	HC138(0);
}

void Timer0() interrupt 1
{
	static unsigned int n, m, Man;
	n++;
	m++;
	Man++;

	if (n == 1000)
	{
		n = 0;
		sec++;
	}
	if (m == 200)
	{
		m = 0;
		sce_2++;
	}
	/*主程序*/
	if (Man == 10) // 10ms
	{
		DS1302_Read();
		smg_timing();

		Man = 0;
	}
}