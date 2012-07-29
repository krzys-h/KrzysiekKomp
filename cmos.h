#ifndef __CMOS_H_
#define __CMOS_H_

typedef struct time {
	s8int h;
	s8int m;
	s8int s;
} __attribute__((packed)) time_t;

s8int getcmos(u8int komorka);
void setcmos(u8int komorka, s8int wartosc);
time_t gettime();
void settime(time_t godzina);

#endif