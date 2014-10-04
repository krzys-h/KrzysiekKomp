extern do_exc0
extern do_exc1
extern do_exc2
extern do_exc3
extern do_exc4
extern do_exc5
extern do_exc6
extern do_exc7
extern do_exc8
extern do_exc9
extern do_exc10
extern do_exc11
extern do_exc12
extern do_exc13
extern do_exc14

exception_table:
dd do_exc0,do_exc1,do_exc2,do_exc3,do_exc4
dd do_exc5,do_exc6,do_exc7,do_exc8,do_exc9
dd do_exc10,do_exc11,do_exc12,do_exc13,do_exc14

global exc0
exc0: 
	push dword 0 
	push dword 0 
	jmp handle_exception 


global exc1
exc1: 
	push dword 0	   
	push dword 1 
	jmp handle_exception 

global exc2
exc2: 
	push dword 0 
	push dword 2 
	jmp handle_exception 

global exc3
exc3: 
	push dword 0 
	push dword 3 
	jmp handle_exception 

global exc4
exc4: 
	push dword 0 
	push dword 4 
	jmp handle_exception 

global exc5
exc5: 
	push dword 5 
	jmp handle_exception 

global exc6
exc6: 
	push dword 0 
	push dword 6 
	jmp handle_exception 

global exc7
exc7: 
	push dword 0 
	push dword 7 
	jmp handle_exception 

global exc8
exc8: 
	push dword 8 
	jmp handle_exception 

global exc9
exc9: 
	push dword 0 
	push dword 9 
	jmp handle_exception 

global exc10
exc10: 
	push dword 10 
	jmp handle_exception 

global exc11
exc11: 
	push dword 11 
	jmp handle_exception 

global exc12
exc12: 
	push dword 12 
	jmp handle_exception 

global exc13
exc13: 
	push dword 13 
	jmp handle_exception 

global exc14
exc14: 
	push dword 14 
	jmp handle_exception
	
handle_exception: 
	xchg eax,[esp] 
	xchg ebx,[esp+4] 
	push gs 
	push fs 
	push es 
	push ds 
	push ebp 
	push edi 
	push esi 
	push edx 
	push ecx 
	push ebx 
	mov ecx,0x10 
	mov ds,cx 
	mov es,cx 
	call dword [exception_table+eax*4] 
	pop eax 
	pop ecx 
	pop edx 
	pop esi 
	pop edi 
	pop ebp 
	pop ds 
	pop es 
	pop fs 
	pop gs 
	pop eax 
	pop ebx 
	iret
