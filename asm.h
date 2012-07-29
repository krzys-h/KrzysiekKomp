#ifndef __ASM_H_
#define __ASM_H_

static inline void hlt()
{
	asm volatile("hlt");
}

static inline void cli()
{
	asm volatile("cli");
}

static inline void sti()
{
	asm volatile("sti");
}

static inline void outportb(unsigned short port,unsigned char val)
{
	asm volatile("outb %%al,%%dx"::"a"(val),"d"(port));
}

static inline unsigned char inportb(unsigned short port)
{
 unsigned char __ret;
 asm volatile("inb %%dx,%%al":"=a"(__ret):"d"(port));
 return __ret;
}

#define outb(val,port)	outportb(port,val)
#define inb(port)	inportb(port)

#endif
