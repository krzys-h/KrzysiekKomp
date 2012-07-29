#include "main.h"

s8int getcmos(u8int komorka)
{
	outportb(0x70, komorka);
	return inportb(0x71);
}

void setcmos(u8int komorka, s8int wartosc)
{
	outportb(0x70, komorka);
	outportb(0x71, wartosc);
}

time_t gettime()
{
	time_t godzina;
	godzina.h = getcmos(0x04);
	godzina.m = getcmos(0x02);
	godzina.s = getcmos(0x00);
	return godzina;
}

void settime(time_t godzina)
{
	setcmos(0x04, godzina.h);
	setcmos(0x02, godzina.m);
	setcmos(0x00, godzina.s);
}