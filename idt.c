#include "main.h"

idt_descr_t idt[IDT_LEN];
idt_ptr_t idt_ptr;

void idt_init()
{
	idt_ptr.base = (u32int) &idt;
	idt_ptr.limit = sizeof(idt_descr_t) * IDT_LEN - 1;

	idt_set(&idt_ptr);
	reroute_irqs();
}

void idt_set_desc(idt_descr_t* descr, u32int handler, u8int type, u8int dpl)
{
   descr->offset_0  = handler;
   descr->selector  = 0x08;
   //descr->type      = type;
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

static unsigned int cached_irq_mask = 0xffff; 

#define __byte(x,y)       (((unsigned char *)&(y))[x]) 
#define cached_21      (__byte(0,cached_irq_mask)) 
#define cached_A1      (__byte(1,cached_irq_mask)) 

void disable_irq(unsigned int irq) 
{ 
	unsigned int mask = 1 << irq; 
	cached_irq_mask |= mask; 
	if (irq & 8) 
	{ 
		outb(cached_A1,0xA1); 
	} else { 
		outb(cached_21,0x21); 
	} 
} 

void enable_irq(unsigned int irq) 
{ 
	unsigned int mask = ~(1 << irq); 
	cached_irq_mask &= mask; 
	if (irq & 8) { 
		outb(cached_A1,0xA1); 
	} else { 
		outb(cached_21,0x21); 
	} 
}

void ustaw_czestotliwosc_pit(unsigned long hz) 
{ 
	unsigned long val=1193180/hz; 
	outb(0x36,0x43); 
	outb(val&0xff,0x40); 
	outb((val>>8)&0xff,0x40); 
}