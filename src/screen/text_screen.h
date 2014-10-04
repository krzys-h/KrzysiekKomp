#pragma once

#include "common/types.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
#define SCREEN_DEFAULT_COLOR 3840
//TODO: 3840 = ((((0 << 4) | (15 & 0x0F)) << 8))

void screen_clear();
void screen_setcursor(int cursorpos);
void screen_printchar(char c);
void screen_printcharcolor(char c, u16int color);
void screen_print(const char* s);
void screen_printcolor(const char* s, u16int color);
