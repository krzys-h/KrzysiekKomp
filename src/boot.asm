global loader
extern main

FLAGS     equ	0                ; Multiboot header: flags
MAGIC     equ	0x1BADB002       ; Multiboot header: magic number
CHECKSUM  equ	-(MAGIC + FLAGS) ; Multiboot header: checksum
STACKSIZE equ	0x4000		     ; Stack size - 16 KB

section .multiboot
multiboot_header:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
align 4
loader:
	mov		esp, stack + STACKSIZE ; set up the stack
	
	push	eax		; (2nd arg) Multiboot: Magic number
	push	ebx		; (1st arg) Multiboot: Info structure
 
	call	main	; go to C code
 
section .bss
align 4
stack:
	resb 	STACKSIZE	; reserve stack space
