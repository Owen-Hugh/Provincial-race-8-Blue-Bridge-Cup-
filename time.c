#include "time.h"

void Timer0Init(void) //1毫秒@12.000MHz
{
    AUXR &= 0x7F; //定时器时钟12T模式
    TMOD &= 0xF0; //设置定时器模式
    TL0 = 0x18;   //设置定时初值
    TH0 = 0xFC;   //设置定时初值
    TF0 = 0;      //清除TF0标志
    TR0 = 1;      //定时器0开始计时
    ET0 = 1;
    EA = 1;
}
