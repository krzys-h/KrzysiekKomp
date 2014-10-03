#include "main.h"

void disc_read(u8int disc, u32int lba, u8int sector_count, void* buffer)
{
	bool timedout = false;
	int retrycount = 0;

	retry_read:
	outportb(0x1F6, ((lba >> 24) & 0x0000000F) | 0xE0);
	outportb(0x1F2, sector_count);
	outportb(0x1F3, lba & 0x000000FF);
	outportb(0x1F4, (lba >> 8) & 0x000000FF);
	outportb(0x1F5, (lba >> 16) & 0x000000FF);
	outportb(0x1F7, 0x20); // READ WITH RETRY
	u8int _status = 0;
	u32int start_runtime = runtime;
	while(!(_status & 0x08)) {
		_status = inportb(0x1F7);
		if(runtime >= (start_runtime + 100)) {
			timedout = true;
			break;
		}
	}
	if(timedout) {
		timedout = false;
		if(retrycount < 3) {
			vga_puts("ERROR! Read timed out, retrying...\n");
			retrycount++;
			goto retry_read;
		} else {
			vga_puts("ERROR! Too many errors, aborting...\n");
		}
	}
	u32int _counter = 0;
	u16int* _buffer = (u16int*)buffer;
	for(_counter = sector_count*(512/2); _counter>0; _counter--) {
		*_buffer = inportw(0x1F0);
		_buffer++;
	}
}

void disc_read_chs(u8int disc, u8int head, u16int cylinder, u8int sector, u8int sector_count, void* buffer)
{
	bool timedout = false;
	int retrycount = 0;

	retry_read:
	outportb(0x1F6, 0xA0 | (disc << 4) | head);
	outportb(0x1F2, sector_count);
	outportb(0x1F3, sector);
	outportb(0x1F4, cylinder);
	outportb(0x1F5, cylinder >> 8);
	outportb(0x1F7, 0x20); // READ WITH RETRY
	u8int _status = 0;
	u32int start_runtime = runtime;
	while(!(_status & 0x08)) {
		_status = inportb(0x1F7);
		if(runtime >= (start_runtime + 100)) {
			timedout = true;
			break;
		}
	}
	if(timedout) {
		timedout = false;
		if(retrycount < 3) {
			vga_puts("ERROR! Read timed out, retrying...\n");
			retrycount++;
			goto retry_read;
		} else {
			vga_puts("ERROR! Too many errors, aborting...\n");
		}
	}
	u32int _counter = 0;
	u16int* _buffer = (u16int*)buffer;
	for(_counter = sector_count*(512/2); _counter>0; _counter--) {
		*_buffer = inportw(0x1F0);
		_buffer++;
	}
}
