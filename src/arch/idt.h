#pragma once

#include "common/types.h"

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

#define IDT_LEN 256

void idt_set_desc(idt_descr_t* descr, u32int handler, u8int type, u8int dpl);
void idt_set_intr_gate(idt_descr_t* descr, u32int handler);
void idt_set_trap_gate(idt_descr_t* descr, u32int handler);
void idt_set_system_gate(idt_descr_t* descr, u32int handler);
extern void idt_set(idt_ptr_t* idt_ptr);
extern void reroute_irqs();
void enable_irq(unsigned int irq);
void disable_irq(unsigned int irq);
void set_clock_frequency(unsigned long f);
void idt_init();
extern idt_descr_t idt[IDT_LEN];
