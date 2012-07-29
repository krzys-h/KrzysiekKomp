[GLOBAL irq1]
irq1: 
      push gs
      push fs
      push es
      push ds
      pusha
      mov ax,0x10
      mov ds,ax
      mov es,ax
      mov al,0x61
      out 0x20,al
[EXTERN do_irq1]
      call do_irq1
      popa
      pop ds
      pop es
      pop fs
      pop gs
      iret