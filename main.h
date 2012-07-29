#ifndef __MAIN_H_
#define __MAIN_H_

#include "lib/multiboot.h"

#include "common.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "asm.h"
#include "keyboard.h"
#include "clock.h"
#include "power.h"
#include "pisz.h"
#include "cmos.h"
#include "mouse.h"
#include "exception.h"
#include "sound.h"
#include "disc.h"

extern u32int total_memory_size;

#endif