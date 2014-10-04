#include "arch/idt.h"

#include "common/asm.h"
#include "common/types.h"
#include "common/ports.h"

idt_descr_t idt[IDT_LEN];
idt_ptr_t idt_ptr;

void idt_set_desc(idt_descr_t* descr, u32int handler, u8int type, u8int dpl)
{
   descr->offset_0  = handler;
   descr->selector  = 0x08;
   descr->type = (u16int)(0x8000+(dpl<<13)+(type<<8));
   descr->offset_16 = (handler >> 16);
}

void idt_set_intr_gate(idt_descr_t* descr, u32int handler)
{
	idt_set_desc(descr, handler, 14, 0);
}

void idt_set_trap_gate(idt_descr_t* descr, u32int handler)
{
	idt_set_desc(descr, handler, 15, 0);
}

void idt_set_system_gate(idt_descr_t* descr, u32int handler)
{
	idt_set_desc(descr, handler, 15, 3);
}

void idt_init()
{
	idt_ptr.base = (u32int) &idt;
	idt_ptr.limit = sizeof(idt_descr_t) * IDT_LEN - 1;

	idt_set(&idt_ptr);
	reroute_irqs();
}

static unsigned int irq_mask = 0xffff; // (cached)

void enable_irq(unsigned int irq)
{
	irq_mask &= ~(1 << irq);
	if(irq & 8) {
		outb(((unsigned char*)&irq_mask)[1], 0xA1);
	} else {
		outb(((unsigned char*)&irq_mask)[0], 0x21);
	}
}

void disable_irq(unsigned int irq)
{
	irq_mask |= (1 << irq);
	if(irq & 8) {
		outb(((unsigned char*)&irq_mask)[1], 0xA1);
	} else {
		outb(((unsigned char*)&irq_mask)[0], 0x21);
	}
}

void set_clock_frequency(unsigned long f)
{
	unsigned long val=1193180/f;
	outb(0x36, 0x43);
	outb(val&0xff, 0x40);
	outb((val>>8)&0xff, 0x40);
}
