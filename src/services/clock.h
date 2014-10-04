#pragma once

#include "common/types.h"

void clock_init();
extern void irq0();
void do_irq0();
void delay(u32int time);
u32int runtime;
