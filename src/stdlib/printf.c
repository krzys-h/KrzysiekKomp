#include "stdlib/printf.h"

#include "screen/text_screen.h"
#include "stdlib/va_list.h"

int printf_fnc(unsigned char c, void **ptr)
{
	screen_printchar(c);
}

void printf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	do_printf(format, args, printf_fnc, 0);
	va_end(args);
}
