#include "hdd/hdd.h"

#include "common/ports.h"

void hdd_read(u32int lba, u8int sector_count, u8int* buffer)
{
	outportb(0x1F6, (u8int)(0xE0 | (lba >> 24)));	// DRIVE, MODE & LBA BITS 24-27		bit 6 on => LBA mode
	outportb(0x1F2, sector_count);					// SECTOR COUNT
	outportb(0x1F3, (u8int)(lba));					// LBA BITS 0-7
	outportb(0x1F4, (u8int)(lba >> 8));				// LBA BITS 8-15
	outportb(0x1F5, (u8int)(lba >> 16));			// LBA BITS 16-23
	outportb(0x1F7, 0x20);							// COMMAND 							=> READ WITH RETRY
	// Wait for data to be available
	u8int status;
	do {
		status = inportb(0x1F7);
	} while(!(status & 0x08));
	// Read data
	for(unsigned int i = sector_count*(512/2); i > 0; i--) {
		u16int data = inportw(0x1F0);
		*((u16int*)buffer) = data;
		buffer += 2;
	}
}
