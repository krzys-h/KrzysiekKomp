#include "main.h"

void do_exc0(void)
{
	vga_puts("Wyjatek 0");
	cli();
 	hlt();
}

void do_exc1(void)
{
	vga_puts("Wyjatek 1");
	cli();
 	hlt();
}

void do_exc2(void)
{
	vga_puts("Wyjatek 2");
	cli();
 	hlt();
}

void do_exc3(void)
{
	vga_puts("Wyjatek 3");
	cli();
 	hlt();
}

void do_exc4(void)
{
	vga_puts("Wyjatek 4");
	cli();
 	hlt();
}

void do_exc5(void)
{
	vga_puts("Wyjatek 5");
	cli();
 	hlt();
}

void do_exc6(void)
{
	vga_puts("Wyjatek 6");
	cli();
 	hlt();
}

void do_exc7(void)
{
	vga_puts("Wyjatek 7");
	cli();
 	hlt();
}

void do_exc8(void)
{
	vga_puts("Wyjatek 8");
	cli();
 	hlt();
}

void do_exc9(void)
{
	vga_puts("Wyjatek 9");
	cli();
 	hlt();
}

void do_exc10(void)
{
	vga_puts("Wyjatek 10");
	cli();
 	hlt();
}


void do_exc11(void)
{
	vga_puts("Wyjatek 11");
	cli();
 	hlt();
}

void do_exc12(void)
{
	vga_puts("Wyjatek 12");
	cli();
 	hlt();
}

void do_exc13(void)
{
	vga_puts("Wyjatek 13");
	cli();
 	hlt();
}

void do_exc14(void)
{
	vga_puts("Wyjatek 14");
	cli();
 	hlt();
}

void exception_init(void)
{
	idt_set_trap_gate(&idt[0],(u32int)&exc0);
	idt_set_trap_gate(&idt[1],(u32int)&exc1);
	idt_set_trap_gate(&idt[2],(u32int)&exc2);
	idt_set_system_gate(&idt[3],(u32int)&exc3);
	idt_set_system_gate(&idt[4],(u32int)&exc4);
	idt_set_system_gate(&idt[5],(u32int)&exc5);
	idt_set_trap_gate(&idt[6],(u32int)&exc6);
	idt_set_trap_gate(&idt[7],(u32int)&exc7);
	idt_set_trap_gate(&idt[8],(u32int)&exc8);
	idt_set_trap_gate(&idt[9],(u32int)&exc9);
	idt_set_trap_gate(&idt[10],(u32int)&exc10);
	idt_set_trap_gate(&idt[11],(u32int)&exc11);
	idt_set_trap_gate(&idt[12],(u32int)&exc12);
	idt_set_trap_gate(&idt[13],(u32int)&exc13);
	idt_set_trap_gate(&idt[14],(u32int)&exc14);
}
