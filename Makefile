all: kernel
	

run: kernel
	qemu-system-i386 -monitor stdio -kernel ./bin/kernel.bin

prepare:
	mkdir -p bin

loader: prepare
	nasm -f elf -o ./bin/loader.o loader.asm

kernel: loader main.c
	nasm gdt.asm -f elf32 -o ./bin/gdt_asm.o
	nasm idt.asm -f elf32 -o ./bin/idt_asm.o
	nasm exception.asm -f elf32 -o ./bin/exception_asm.o
	nasm keyboard.asm -f elf32 -o ./bin/keyboard_asm.o
	nasm clock.asm -f elf32 -o ./bin/clock_asm.o
	nasm power.asm -f elf32 -o ./bin/power_asm.o
	gcc -o ./bin/gdt.o -c gdt.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/idt.o -c idt.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/exception.o -c exception.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/vga.o -c vga.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/disc.o -c disc.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/keyboard.o -c keyboard.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/clock.o -c clock.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/sound.o -c sound.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/pisz.o -c pisz.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/mouse.o -c mouse.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/cmos.o -c cmos.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/parttable.o -c parttable.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/fs_fat32.o -c fs_fat32.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/commands.o -c commands.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	gcc -o ./bin/main.o -c main.c -m32 -nostdlib -nostartfiles -nodefaultlibs
	ld -melf_i386 -T linker.ld -o ./bin/kernel.bin ./bin/loader.o ./bin/main.o ./bin/commands.o ./bin/vga.o ./bin/disc.o ./bin/gdt.o ./bin/gdt_asm.o ./bin/idt.o ./bin/idt_asm.o ./bin/exception.o ./bin/exception_asm.o ./bin/keyboard.o ./bin/keyboard_asm.o ./bin/clock.o ./bin/clock_asm.o ./bin/sound.o ./bin/power_asm.o ./bin/pisz.o ./bin/cmos.o ./bin/mouse.o ./bin/parttable.o ./bin/fs_fat32.o

clean:
	rm -rf ./bin/*
