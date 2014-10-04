#include <multiboot.h>
#include "common/asm.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/exceptions.h"
#include "services/clock.h"
#include "services/keyboard.h"
#include "memory/memory.h"
#include "stdlib/iostream.h"

int main(multiboot_info_t* mbinfo, unsigned int mbmagic)
{
	if(mbmagic != MULTIBOOT_BOOTLOADER_MAGIC) {
		std::cout << "Multiboot error!";
		hang();
	}
	
	gdt_init();
	idt_init();
	exceptions_init();
	clock_init();
	keyboard_init();
	sti(); // enable interrupts
	
	std::cout.clear();
	std::cout << "KrzysiekKomp v1.0" << std::endl;
	std::cout << "Compiled at: " << __DATE__ << " " << __TIME__ << std::endl << std::endl;
	
	dump_memory();
	char* buf1 = new char[512];
	char* buf2 = new char[256];
	dump_memory();
	delete buf1;
	dump_memory();
	buf1 = new char[128];
	char* buf3 = new char[128];
	dump_memory();
	delete buf2;
	dump_memory();
	delete buf1;
	delete buf3;
	dump_memory();
	
	std::cout << "END OF KERNEL";
	hang();
}
