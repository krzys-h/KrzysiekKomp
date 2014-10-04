#pragma once

#include "common/types.h"

// http://lukaszsowa.pl/2010/10/gdt/

typedef struct gdt_descr
{
	u16int limit_low;
	u16int base_low;
	u8int base_middle;
	u8int access;
	u8int granularity;
	u8int base_high;
} __attribute__((packed)) gdt_descr_t;

typedef struct gdt_ptr
{
	u16int limit;
	u32int base;
} __attribute__((packed)) gdt_ptr_t;

#define GDT_LEN 5

void gdt_set_desc(gdt_descr_t* descr, u32int base, u32int limit, u8int access, u8int granularity);
extern void gdt_set(gdt_ptr_t* gdt_ptr);
void gdt_init();
