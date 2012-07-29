#ifndef __VGA_H_
#define __VGA_H_

#include "common.h"

extern int cursor;

void vga_init();

void vga_cls();

void vga_puts(const char* str);

void vga_putch(char znak);

static void vga_scroll();

void vga_setcursorpos(int x, int y);

void vga_setcursorposraw(int temp);

#endif
