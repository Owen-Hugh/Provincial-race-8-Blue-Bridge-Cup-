#ifndef _DS1302_H
#define _DS1302_H

#include "stc15f2k60s2.h"

void DS1302_Init();
void DS1302_Read();
void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte(unsigned char address, unsigned char dat);
unsigned char Read_Ds1302_Byte(unsigned char address);

#endif