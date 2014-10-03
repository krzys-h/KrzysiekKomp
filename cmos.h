#ifndef __CMOS_H_
#define __CMOS_H_

typedef struct time {
	u8int second;
	u8int minute;
	u8int hour;
	u8int day;
	u8int month;
	u16int year;
} __attribute__((packed)) time_t;

u8int getcmos(u8int komorka);
void setcmos(u8int komorka, u8int wartosc);
int cmos_time_get_update_flag();
time_t gettime();

#endif