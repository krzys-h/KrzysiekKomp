#include "main.h"

extern void irq0(void);

u32int runtime;

void clock_init(int hz)
{
	runtime = 0;
	ustaw_czestotliwosc_pit(100);
	idt_set_intr_gate(&idt[0x20], (u32int)&irq0); 
	enable_irq(0); 
}

void do_irq0(void) 
{ 
	runtime++;
}

void delay(u32int czas)
{
	u32int start_runtime = runtime;
	while(runtime < (start_runtime + czas));
}