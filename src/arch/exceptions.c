#include "arch/exceptions.h"

#include "common/asm.h"
#include "common/types.h"
#include "screen/text_screen.h"
#include "arch/idt.h"

extern void exc0(void);
extern void exc1(void);
extern void exc2(void);
extern void exc3(void);
extern void exc4(void);
extern void exc5(void);
extern void exc6(void);
extern void exc7(void);
extern void exc8(void);
extern void exc9(void);
extern void exc10(void);
extern void exc11(void);
extern void exc12(void);
extern void exc13(void);
extern void exc14(void);

void do_exc0()
{
	screen_print("\n\n\nException 0");
	hang();
}

void do_exc1()
{
	screen_print("\n\n\nException 1");
	hang();
}

void do_exc2()
{
	screen_print("\n\n\nException 2");
	hang();
}

void do_exc3()
{
	screen_print("\n\n\nException 3");
	hang();
}

void do_exc4()
{
	screen_print("\n\n\nException 4");
	hang();
}

void do_exc5()
{
	screen_print("\n\n\nException 5");
	hang();
}

void do_exc6()
{
	screen_print("\n\n\nException 6");
	hang();
}

void do_exc7()
{
	screen_print("\n\n\nException 7");
	hang();
}

void do_exc8()
{
	screen_print("\n\n\nException 8");
	hang();
}

void do_exc9()
{
	screen_print("\n\n\nException 9");
	hang();
}

void do_exc10()
{
	screen_print("\n\n\nException 10");
	hang();
}


void do_exc11()
{
	screen_print("\n\n\nException 11");
	hang();
}

void do_exc12()
{
	screen_print("\n\n\nException 12");
	hang();
}

void do_exc13()
{
	screen_print("\n\n\nException 13");
	hang();
}

void do_exc14()
{
	screen_print("\n\n\nException 14");
	hang();
}

void exception_init()
{
	idt_set_trap_gate(&idt[0], (u32int)&exc0);
	idt_set_trap_gate(&idt[1], (u32int)&exc1);
	idt_set_trap_gate(&idt[2], (u32int)&exc2);
	idt_set_system_gate(&idt[3], (u32int)&exc3);
	idt_set_system_gate(&idt[4], (u32int)&exc4);
	idt_set_system_gate(&idt[5], (u32int)&exc5);
	idt_set_trap_gate(&idt[6], (u32int)&exc6);
	idt_set_trap_gate(&idt[7], (u32int)&exc7);
	idt_set_trap_gate(&idt[8], (u32int)&exc8);
	idt_set_trap_gate(&idt[9], (u32int)&exc9);
	idt_set_trap_gate(&idt[10], (u32int)&exc10);
	idt_set_trap_gate(&idt[11], (u32int)&exc11);
	idt_set_trap_gate(&idt[12], (u32int)&exc12);
	idt_set_trap_gate(&idt[13], (u32int)&exc13);
	idt_set_trap_gate(&idt[14], (u32int)&exc14);
}
