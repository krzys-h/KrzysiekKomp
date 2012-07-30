#include "main.h"

void disc_read(u8int disc, u8int head, u16int cylinder, u8int sector, u8int sector_count, u8int* buffer)
{
	outportb(0x1F6, 0xA0 | (disc << 4) | head);
	outportb(0x1F2, sector_count);
	outportb(0x1F3, sector);
	outportb(0x1F4, cylinder);
	outportb(0x1F5, cylinder >> 8);
	outportb(0x1F7, 0x20); // READ WITH RETRY
	u8int _status = 0;
	while(!(_status & 0x08)) _status = inportb(0x1F7);
	u32int _counter = 0;
	u16int* _buffer = (u16int*)buffer;
	for(_counter = sector_count*(512/2); _counter>0; _counter--) {
		*_buffer = inportw(0x1F0);
		_buffer++;
	}
}