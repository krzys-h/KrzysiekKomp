#include "main.h"

void pisz_u32int(u32int liczba)
{
	char bufor[10];
	int i = 0;
	int licz = liczba;
	if(licz==0) vga_putch('0');
	else {
		while(licz!=0) {
			bufor[i] = (licz%10) + '0';
			licz = licz/10;
			i++;
		}
		i--;
		while(i>=0) {
			vga_putch(bufor[i]);
			i--;
		}
	}
}

void pisz_s32int(s32int liczba)
{
	if(liczba>=0) {
		pisz_u16int(liczba);
	} else {
		vga_putch('-');
		pisz_u16int(-liczba);
	}
}

void pisz_u16int(u16int liczba)
{
	pisz_u32int((u32int)liczba);
}
	
void pisz_s16int(s16int liczba)
{
	pisz_s32int((s32int)liczba);
}

void pisz_u8int(u8int liczba)
{
	pisz_u32int((u32int)liczba);
}
	
void pisz_s8int(s8int liczba)
{
	pisz_s32int((s32int)liczba);
}

void pisz_time_ms(u32int czas)
{
	u32int time = czas;
	u16int ms;
	u16int s;
	u16int m;
	u16int h;
	
	ms = time%100;
	time = (time - ms)/100;
	s = time%60;
	time = (time - s)/60;
	m = time%60;
	time = (time - m)/60;
	h = time;
	
	pisz_u16int(h);
	vga_putch(':');
	pisz_u16int(m);
	vga_putch(':');
	pisz_u16int(s);
	vga_putch('.');
	pisz_u16int(ms);
}

void pisz_time(u32int czas)
{
	u32int time = czas;
	u16int s;
	u16int m;
	u16int h;
	
	s = time%60;
	time = (time - s)/60;
	m = time%60;
	time = (time - m)/60;
	h = time;
	
	pisz_u16int(h);
	vga_putch(':');
	pisz_u16int(m);
	vga_putch(':');
	pisz_u16int(s);
}

u8int getnum()
{
	char i = 0;
	char enter = 0;
	int buffer = 0;
	while(!enter) {
		char c = getch();
		if(!c) continue;
		switch(c) {
			case '\b':
				if(i>0) {
					i--;
					buffer = (buffer-(buffer%10))/10;
					vga_putch('\b');
				}
				break;
			case '\n':
				enter = 1;
				vga_putch('\n');
				break;
			default:
				vga_putch(c);
				buffer = (buffer*10)+c;
				i++;
		}
	}
	return buffer;
}