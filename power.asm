[GLOBAL reboot]
reboot:
	mov	al, 0feh
	out	64h, al
	ret