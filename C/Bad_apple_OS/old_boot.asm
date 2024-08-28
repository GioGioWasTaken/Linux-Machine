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
	jmp print
print:
	mov ah, 0x0E 
	mov al, [msg + si]
	int 0x10
	add si, 1
	cmp byte [msg+si], 0 ; al wasn't updated yet.
	je Spam_Count
	jmp print

Spam_Count:
	cmp cx,0x64	

	je Kernel

	add cx, 1
	jmp Spam



Spam:
	mov si, 0
	jmp print
Kernel:
	mov si, 0 ; Kernel expects this state

	mov al, 2 ; read 2 sectors
	mov ch, 0 ; track 0
	mov cl, 2 ; sector to read (The second sector)


	mov dl, 0 ; drive number
	mov dh, 0 ; head number

	mov ah, 0x02 ; read sectors from disk
	int 0x13 ; call the BIOS routine
	jmp 0x50:0x0 ; jump and execute the sector!

	hlt

	
times 510 -($-$$) db 0
	; a sector is 512 bytes
	; $: Represents the current assembly address.
	; $$: Represents the starting address of the current section (in this case, 0x7C00 as set by org 0x7c00).
dw 0xAA55 ;bootloader unique signature
