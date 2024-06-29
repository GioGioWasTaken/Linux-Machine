; bootloader.asm
; A Simple Bootloader
;******************************************

org 0x7c00
bits 16

start: jmp boot

	msg db "Let's all love Lain.", 0ah, 0dh, 0h ; message to print

	mov cx , 0
	mov si, 0
boot:
	cli ; disable interrupts and thus prevent undefined behaviour
	cld ; make sure we are reading words in correct order
	jmp Welcome
Welcome:
	mov ah, 0x0E 
	mov al, [msg + si]
	int 0x10
	add si, 1
	cmp byte [msg+si], 0 ; al wasn't updated yet.
	je Spam_Count
	jmp Welcome

Spam_Count:
	cmp cx,0x64	

	je halt

	add cx, 1
	jmp Spam



Spam:
	mov si, 0
	jmp Welcome
halt:
	hlt
	
times 510 -($-$$) db 0
	; a sector is 512 bytes
	; $: Represents the current assembly address.
	; $$: Represents the starting address of the current section (in this case, 0x7C00 as set by org 0x7c00).
dw 0xAA55 ;bootloader unique signature
