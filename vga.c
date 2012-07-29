#include "main.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

static u16int* vga_mem;
int cursor;

void vga_init()
{
	if ((*((volatile u16int*) 0x410) & 0x30) == 0x30) // detecting monochrome monitor
		vga_mem = (u16int*) 0xB0000;
	else
		vga_mem = (u16int*) 0xB8000; // it's color
	
	vga_cls();
}

void vga_cls()
{
	cursor = 0;
	vga_setcursorposraw(cursor);
	
	int i;
	for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
		*(vga_mem + i) = (u16int) 3872; // ((((0 << 4) | (15 & 0xFF)) << 8) | 0x20) // white spaces on black background
}

static void vga_scroll()
{
	int i;
	// rewrite lines one up
	for (i = 0; i < SCREEN_WIDTH * (SCREEN_HEIGHT - 1); ++i)
		vga_mem[i] = vga_mem[i + SCREEN_WIDTH];

	// clear last line
	for(i = 0; i < SCREEN_WIDTH; ++i)
		vga_mem[SCREEN_WIDTH * (SCREEN_HEIGHT - 1) + i] = 3872; // ((((0 << 4) | (15 & 0xFF)) << 8) | 0x20) // white spaces on black background
}

void vga_puts(const char* str)
{
	// white letters on black background
	const u16int attribute = 3840; // ((((0 << 4) | (15 & 0x0F)) << 8))

	int i = 0;
	while (str[i] != '\0')
	{
		vga_putch(str[i]);

		++i;
	}
}

void vga_putch(char znak)
{
	const u16int attribute = 3840; // ((((0 << 4) | (15 & 0x0F)) << 8))
	
	if (cursor == SCREEN_WIDTH * SCREEN_HEIGHT)
	{
		vga_scroll();
		cursor = SCREEN_WIDTH * (SCREEN_HEIGHT - 1);
	}

	switch (znak)
	{
	case '\n':
		cursor = cursor + 80 - cursor % 80;
		break;
	case '\r':
		cursor = cursor - cursor % 80;
		break;
	case '\t':
		// increment to align to 8
		while ((cursor % 80) % 8 != 0)
			++cursor;
		break;
	case '\b':
		--cursor;
		vga_mem[cursor] = (u16int) (attribute | ' ');
		break;
	default:
		vga_mem[cursor] = (u16int) (attribute | znak);
		++cursor;
	}
	
	vga_setcursorposraw(cursor);
}

void vga_setcursorpos(int x,int y) 
{ 
	int temp; 
	temp=(y*80+x); 
	outportb(0x3D4+0,14); 
	outportb(0x3D4+1,temp>>8); 
	outportb(0x3D4+0,15); 
	outportb(0x3D4+1,temp); 
}

void vga_setcursorposraw(int temp) 
{ 
	outportb(0x3D4+0,14); 
	outportb(0x3D4+1,temp>>8); 
	outportb(0x3D4+0,15); 
	outportb(0x3D4+1,temp); 
}