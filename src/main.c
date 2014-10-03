#include <multiboot.h>
#include "common/asm.h"
#include "screen/text_screen.h"

int main(multiboot_info_t* mbinfo, unsigned int mbmagic)
{
	screen_clear();
	screen_print("Hello world!");
	
	while(1)
		hlt();
}
