global gdt_set

gdt_set:
	mov		eax, [esp+4]	; (1st arg) pointer to GDT
	lgdt	[eax]			; Load new GDT pointer

	; Load all data segment registers
	mov	ax, 0x10
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax
	jmp	0x08:.flush	; Far jump to code segment
.flush:
	ret
