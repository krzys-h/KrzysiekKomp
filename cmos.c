#include "main.h"

u8int getcmos(u8int komorka)
{
	outportb(0x70, komorka);
	return inportb(0x71);
}

void setcmos(u8int komorka, u8int wartosc)
{
	outportb(0x70, komorka);
	outportb(0x71, wartosc);
}

#define CURRENT_YEAR        2012                            // Change this each year!
 
int century_register = 0x00;                                // Set by ACPI table parsing code if possible
 
int cmos_time_get_update_flag() {
      return (getcmos(0x0A) & 0x80);
}
 
time_t gettime() {
	u8int century;
	u8int last_second;
	u8int last_minute;
	u8int last_hour;
	u8int last_day;
	u8int last_month;
	u8int last_year;
	u8int last_century;
	u8int registerB;
	time_t czas;
 
	// Note: This uses the "read registers until you get the same values twice in a row" technique
	//       to avoid getting dodgy/inconsistent values due to RTC updates

	while (cmos_time_get_update_flag());                // Make sure an update isn't in progress
	czas.second = getcmos(0x00);
	czas.minute = getcmos(0x02);
	czas.hour = getcmos(0x04);
	czas.day = getcmos(0x07);
	czas.month = getcmos(0x08);
	czas.year = getcmos(0x09);
	if(century_register != 0) {
		century = getcmos(century_register);
	}

	do {
		last_second = czas.second;
		last_minute = czas.minute;
		last_hour = czas.hour;
		last_day = czas.day;
		last_month = czas.month;
		last_year = czas.year;
		last_century = century;

		while (cmos_time_get_update_flag());           // Make sure an update isn't in progress
		czas.second = getcmos(0x00);
		czas.minute = getcmos(0x02);
		czas.hour = getcmos(0x04);
		czas.day = getcmos(0x07);
		czas.month = getcmos(0x08);
		czas.year = getcmos(0x09);
		if(century_register != 0) {
			century = getcmos(century_register);
		}
	} while( (last_second == czas.second) && (last_minute == czas.minute) && (last_hour == czas.hour) &&
			 (last_day == czas.day) && (last_month == czas.month) && (last_year == czas.year) &&
			 (last_century == century) );
 
	registerB = getcmos(0x0B);
 
	// Convert BCD to binary values if necessary
 
	if (!(registerB & 0x04)) {
		czas.second = (czas.second & 0x0F) + ((czas.second / 16) * 10);
		czas.minute = (czas.minute & 0x0F) + ((czas.minute / 16) * 10);
		czas.hour = ( (czas.hour & 0x0F) + (((czas.hour & 0x70) / 16) * 10) ) | (czas.hour & 0x80);
		czas.day = (czas.day & 0x0F) + ((czas.day / 16) * 10);
		czas.month = (czas.month & 0x0F) + ((czas.month / 16) * 10);
		czas.year = (czas.year & 0x0F) + ((czas.year / 16) * 10);
		if(century_register != 0) {
			century = (century & 0x0F) + ((century / 16) * 10);
		}
	}
 
	// Convert 12 hour clock to 24 hour clock if necessary
 
	/*if (!(registerB & 0x02) && (czas.hour & 0x80)) {
		czas.hour = ((czas.hour & 0x7F) + 12) % 24;
	}*/

	// Calculate the full (4-digit) year

	if(century_register != 0) {
		czas.year += century * 100;
	} else {
		czas.year += (CURRENT_YEAR / 100) * 100;
		if(czas.year < CURRENT_YEAR) czas.year += 100;
	}
	
	return czas;
}