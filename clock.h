#ifndef __CLOCK_H_
#define __CLOCK_H_

void clock_init(int hz);

void do_irq0(void);

extern u32int runtime;

#endif