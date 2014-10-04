#include <multiboot.h>
#include "common/asm.h"
#include "screen/text_screen.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "services/clock.h"

int main(multiboot_info_t* mbinfo, unsigned int mbmagic)
{
	if(mbmagic != MULTIBOOT_BOOTLOADER_MAGIC) {
		screen_print("Multiboot error!");
		hang();
	}
	
	gdt_init();
	idt_init();
	clock_init();
	sti();
	
	screen_clear();
	screen_print("KrzysiekKomp v1.0\nCompiled at: "__DATE__" "__TIME__"\n\n");
	while(1) {
		screen_printchar('.');
		delay(100);
	}
}
