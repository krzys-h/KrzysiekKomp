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
	
	char* buf = new char[128];
	std::cin >> buf;
	std::cout << buf << std::endl;
	delete buf;
	
	std::cout << "END OF KERNEL";
	hang();
}
