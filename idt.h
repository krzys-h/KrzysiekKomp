#ifndef __IDT_H_
#define __IDT_H_

#include "primitives.h"

#define IDT_LEN 256

typedef struct idt_descr {
  u16int offset_0;
  u16int selector;
  u16int type;
  u16int offset_16;
} __attribute__((packed)) idt_descr_t;

typedef struct idt_ptr {
	u16int limit;
	u32int base;
} __attribute__((packed)) idt_ptr_t;

void idt_init();

void idt_set_desc(idt_descr_t* descr, u32int handler, u8int type, u8int dpl);
void idt_set_intr_gate(idt_descr_t* descr, u32int handler);
void idt_set_trap_gate(idt_descr_t* descr, u32int handler);
void idt_set_system_gate(idt_descr_t* descr, u32int handler);

static void idt_set(idt_ptr_t* gdt_ptr);

static void reroute_irqs();

void disable_irq(unsigned int irq);

void enable_irq(unsigned int irq);

extern idt_descr_t idt[IDT_LEN];

void ustaw_czestotliwosc_pit(unsigned long hz) ;

#endif
