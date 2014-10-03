#pragma once

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
