#include "screen/serial.h"

#include "common/types.h"
#include "common/ports.h"

#define PORT 0x3f8 /* COM1 */

void serial_init()
{
	outportb(PORT + 1, 0x00);    // Disable all interrupts
	outportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outportb(PORT + 1, 0x00);    //                  (hi byte)
	outportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

void serial_printchar(char c)
{
	while((inportb(PORT + 5) & 0x20) == 0); // Wait for transmit queue to be empty
	outportb(PORT, c);
}

void serial_print(const char* s)
{
	for(int i=0; s[i] != 0; i++)
	{
		serial_printchar(s[i]);
	}
}

char serial_readchar()
{
	while((inportb(PORT + 5) & 1) == 0); // Wait for input
	return inportb(PORT);
}

int serial_read(char* buf)
{
	char i = 0;
	bool enter = false;
	while(!enter) {
		char c = serial_readchar();
		if(!c) continue;
		switch(c) {
			case '\b':
				if(i>0) {
					i--;
					buf[i] = 0;
					serial_printchar('\b');
				}
				break;
			case '\n':
				buf[i] = 0;
				enter = true;
				serial_printchar('\n');
				break;
			default:
				serial_printchar(c);
				buf[i] = c;
				i++;
		}
	}
	return i;
}
