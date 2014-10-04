#pragma once

#include "common/types.h"

extern void clock_init();
extern void irq0(); // ASM code
extern void do_irq0();
extern void delay(u32int time);
extern u32int runtime;
