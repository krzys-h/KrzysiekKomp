#include "screen/text_screen.h"

#include "common/types.h"
#include "common/ports.h"

static u16int* screen_mem = (u16int*) 0xB8000;
int cursor;

void screen_setcursor(int cursorpos)
{
	cursor = cursorpos;
	outportb(0x3D4+0, 14);
	outportb(0x3D4+1, cursor>>8);
	outportb(0x3D4+0, 15);
	outportb(0x3D4+1, cursor);
}

void screen_clear()
{
	screen_setcursor(0);
	for(int i=0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
		screen_mem[i] = 0;
}

void screen_scroll()
{
	// Scroll everything up
	for(int i=0; i < SCREEN_WIDTH*(SCREEN_HEIGHT-1); i++)
		screen_mem[i] = screen_mem[i+SCREEN_WIDTH];
	
	// Clear last line
	for(int i=0; i < SCREEN_WIDTH; i++)
		screen_mem[SCREEN_WIDTH*(SCREEN_HEIGHT-1)+i] = 0;
}

void screen_printcharcolor(char c, u16int color)
{
	if(cursor == SCREEN_WIDTH * SCREEN_HEIGHT) {
		screen_scroll();
		screen_setcursor(SCREEN_WIDTH*(SCREEN_HEIGHT-1));
	}
	
	switch(c) {
		case '\n':
			// Move cursor to the beginning of the next line
			screen_setcursor(cursor+SCREEN_WIDTH - cursor%SCREEN_WIDTH);
			break;
		
		case '\b':
			// Backspace - move back and clear this position
			screen_setcursor(cursor-1);
			screen_mem[cursor] = 0;
			break;
		
		default:
			screen_mem[cursor] = (c | color);
			screen_setcursor(cursor+1);
	}
}

void screen_printchar(char c)
{
	screen_printcharcolor(c, SCREEN_DEFAULT_COLOR);
}

void screen_printcolor(const char* s, u16int color)
{
	for(int i=0; s[i] != 0; i++)
	{
		screen_printcharcolor(s[i], color);
	}
}

void screen_print(const char* s)
{
	screen_printcolor(s, SCREEN_DEFAULT_COLOR);
}
