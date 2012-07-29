#include "main.h"

int cmpstr(char *str1, char *str2)
{
  while(*str1 == *str2 && *str1!=0 && *str2!=0)
  { str1++; str2++; }
  if(*str1 == *str2) return 0;
  if(*str1 > *str2) return 1;
  if(*str1 < *str2) return -1;
  return -1;
}

int cmpbytes(char *str1, char *str2, int ile)
{
  while(*str1 == *str2 && *str1!=0 && *str2!=0 && ile)
  { str1++; str2++; }
  if(*str1 == *str2) return 0;
  if(*str1 > *str2) return 1;
  if(*str1 < *str2) return -1;
  return -1;
}

void split(char *zrodlo, char *cmd, char *param1)
{
	while(*zrodlo==' ') zrodlo++;
	while(1) {
		if( *zrodlo==' ') break;
		if(!*zrodlo     ) break;
		*cmd=*zrodlo;
		zrodlo++;
		cmd++;
	}
	*cmd=0;

	while(*zrodlo==' ') zrodlo++;
	while(1) {
		/* if( *zrodlo==' ') break; */
		if(!*zrodlo     ) break;
		*param1=*zrodlo;
		zrodlo++;
		param1++;
	}
	*param1=0;
}

u32int total_memory_size;

int main(multiboot_info_t* mbd, unsigned int magic)
{
	total_memory_size = mbd->mem_lower + mbd->mem_upper;

	gdt_init();
	idt_init();
	exception_init();
	
	vga_init();
	kbd_init();
	mouse_init();
	clock_init(100);

	sti();
	
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		vga_puts("Multiboot error!");
		while (1)
			hlt();
	}

	vga_puts("KrzysiekKomp v1.0\nKompilacja: "__DATE__" "__TIME__"\n\n");

	char komenda[65];
	char cmd[33];
	char param1[33];
	
	for(;;)
	{
		vga_puts("#KrzysiekKomp#> ");
		int num = getstr(&komenda[0]);
		if(num) {
			split(komenda,cmd,param1);
			     if(!cmpstr(cmd,"echo"    )) cmd_echo(param1);
			else if(!cmpstr(cmd,"clrscr"  )) cmd_clrscr();
			else if(!cmpstr(cmd,"time"    )) cmd_time();
			else if(!cmpstr(cmd,"runtime" )) cmd_runtime();
			else if(!cmpstr(cmd,"memory"  )) cmd_memory();
			else if(!cmpstr(cmd,"help"    )) cmd_help();
			else if(!cmpstr(cmd,"reboot"  )) cmd_reboot();
			else if(!cmpstr(cmd,"shutdown")) cmd_shutdown();
			else cmd_nieznana(komenda);
			if(cmpstr(cmd,"clrscr")) {
				vga_putch('\n');
				vga_putch('\n');
			}
		}

	}

	return 0;
}
