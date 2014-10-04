global idt_set
idt_set:
	mov		eax, [esp+4]	; (1st arg) pointer to IDT
	lidt	[eax]			; Load new IDT pointer
	ret

; TODO: Where did I take this snippet from? I want more documentation
; Przekierowanie przerwań sprzętowych
global reroute_irqs
reroute_irqs:
        cli
        in      al,0x21
        mov     ah,al
        in      al,0xA1
        mov     cx,ax

        mov     al,0x11
        out     0x20,al
        out     0xEB,al
        out     0xA0,al
        out     0xEB,al

        mov     al,0x20
        out     0x21,al
        out     0xEB,al

        add     al,0x8
        out     0xA1,al
        out     0xEB,al

        mov     al,0x04
        out     0x21,al
        out     0xEB,al
        shr     al,1
        out     0xA1,al
        out     0xEB,al
        shr     al,1
        out     0x21,al
        out     0xEB,al
        out     0xA1,al
        out     0xEB,al

        mov     ax,cx
        out     0xA1,al
        mov     al,ah
        out     0x21,al
        mov     ecx,0x1000
        cld
picl1:  out     0xEB,al
        loop    picl1

        cli
        mov     al,255
        out     0xa1,al
        out     0x21,al

        ret
