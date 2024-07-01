	msg2 db "Open the gate", 0ah, 0dh, 0h ; message to print

Print:
	mov ah, 0x0E 
	mov al, [msg2 + si]
	int 0x10
	add si, 1
	cmp byte [msg2+si], 0 ; al wasn't updated yet.
	je halt
	jmp Print
halt: 
	hlt
