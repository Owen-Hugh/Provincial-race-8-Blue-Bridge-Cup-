#include "ds1302.h"
#include <intrins.h>

unsigned char Time[7] = {0x50, 0x59, 0x23, 0x22, 0x03, 0x01, 0x21}; //秒 分 时 月 周 年
unsigned char Time_1[7];                                            //main函数 声明 extern unsigned char Time_1[7]；
sbit SCK = P1 ^ 7;
sbit SDA = P2 ^ 3;
sbit RST = P1 ^ 3; // DS1302复位

void Write_Ds1302(unsigned char temp)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        SCK = 0;
        SDA = temp & 0x01;
        temp >>= 1;
        SCK = 1;
    }
}

void Write_Ds1302_Byte(unsigned char address, unsigned char dat)
{
    RST = 0;
    _nop_();
    SCK = 0;
    _nop_();
    RST = 1;
    _nop_();
    Write_Ds1302(address);
    Write_Ds1302(dat);
    RST = 0;
}

unsigned char Read_Ds1302_Byte(unsigned char address)
{
    unsigned char i, temp = 0x00;
    RST = 0;
    _nop_();
    SCK = 0;
    _nop_();
    RST = 1;
    _nop_();
    Write_Ds1302(address);
    for (i = 0; i < 8; i++)
    {
        SCK = 0;
        temp >>= 1;
        if (SDA)
            temp |= 0x80;
        SCK = 1;
    }
    RST = 0;
    _nop_();
    SCK = 0;
    _nop_();
    SCK = 1;
    _nop_();
    SDA = 0;
    _nop_();
    SDA = 1;
    _nop_();
    return (temp);
}

void DS1302_Init() //初始化
{
    unsigned char add = 0x80, i = 0;
    Write_Ds1302_Byte(0x8E, 0x00); //关闭写保护
    for (i = 0; i < 7; i++)
    {

        Write_Ds1302_Byte(add, Time[i]);
        add += 2;
    }
    Write_Ds1302_Byte(0x8E, 0x80); //打开写保护
}

void DS1302_Read() //读取时间
{
    unsigned char n = 0, add = 0x81;
    for (n = 0; n < 7; n++)
    {
        Time_1[n] = Read_Ds1302_Byte(add);
        add += 2;
    }
}