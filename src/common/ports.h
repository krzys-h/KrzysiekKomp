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

static inline void outportw(unsigned short port,unsigned short val)
{
	asm volatile("outw %%ax,%%dx"::"a"(val),"d"(port));
}

static inline unsigned short inportw(unsigned short port)
{
	unsigned short __ret;
	asm volatile("inw %%dx,%%ax":"=a"(__ret):"d"(port));
	return __ret;
}

#define outb(val,port)	outportb(port,val)
#define inb(port)	inportb(port)
#define outw(val,port)	outportw(port,val)
#define inw(port)	inportw(port)
