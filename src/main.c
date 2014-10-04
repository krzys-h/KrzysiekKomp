#include <multiboot.h>
#include "common/asm.h"
#include "screen/text_screen.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "services/clock.h"
#include "services/keyboard.h"

int main(multiboot_info_t* mbinfo, unsigned int mbmagic)
{
	if(mbmagic != MULTIBOOT_BOOTLOADER_MAGIC) {
		screen_print("Multiboot error!");
		hang();
	}
	
	gdt_init();
	idt_init();
	clock_init();
	keyboard_init();
	sti(); // enable interrupts
	
	screen_clear();
	screen_print("KrzysiekKomp v1.0\nCompiled at: "__DATE__" "__TIME__"\n\n");
	
	// keyboard test
	char buf[SCREEN_WIDTH];
	getstring(&buf[0]);
	screen_print(buf);
	
	// clock test
	while(1) {
		screen_printchar('.');
		delay(100);
	}
}
