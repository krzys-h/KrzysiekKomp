#include <multiboot.h>
#include "common/asm.h"
#include "screen/text_screen.h"
#include "screen/serial.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "services/clock.h"
#include "services/keyboard.h"
#include "memory/memory.h"
#include "hdd/hdd.h"
#include "stdlib/printf.h"

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
	serial_init();
	sti(); // enable interrupts
	
	screen_clear();
	screen_print("KrzysiekKomp v1.0\nCompiled at: "__DATE__" "__TIME__"\n\n");
	serial_print("KrzysiekKomp v1.0\nCompiled at: "__DATE__" "__TIME__"\n\n");
	
	// memory test
	/*void* memtest1 = malloc(32);
	void* memtest2 = malloc(8);
	free(memtest1);
	memtest1 = malloc(16);*/
	
	// memory & keyboard test
	/*void* buf = malloc(SCREEN_WIDTH);
	getstring(buf);
	screen_print(buf);
	free(buf);*/
	
	// clock test
	/*while(true) {
		screen_printchar('.');
		delay(100);
	}*/
	
	// hdd read test
	/*u8int* buffer = malloc(512);
	hdd_read(0, 1, buffer);
	free(buffer);*/
	
	// printf test
	//printf("Printf test: %d\n", 5);
	
	screen_print("END OF KERNEL");
	hang();
}
