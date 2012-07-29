[GLOBAL irq0]
irq0: 
      push gs 
      push fs 
      push es 
      push ds 
      pusha 
      mov ax,0x10 
      mov ds,ax 
      mov es,ax 
      mov al,0x60 
      out 0x20,al 
[EXTERN do_irq0]
      call do_irq0 
      popa 
      pop ds 
      pop es 
      pop fs 
      pop gs 
      iret