#include "services/clock.h"

#include "arch/idt.h"

u32int runtime;

void clock_init()
{
	runtime = 0;
	set_clock_frequency(100);
	idt_set_intr_gate(&idt[0x20], (u32int)&irq0);
	enable_irq(0);
}

void do_irq0()
{
	runtime++;
}

void delay(u32int time)
{
	u32int start = runtime;
	while(runtime < (start+time));
}
