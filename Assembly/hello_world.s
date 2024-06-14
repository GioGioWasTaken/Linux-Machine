; Example of using int 0x80 for a system call
section .data
msg db 'Hello, world!', 0xA  ; Message to print with newline

section .text
global _start

_start:
    ; Write system call
    mov eax, 4          ; sys_write system call number
    mov ebx, 1          ; File descriptor 1 (stdout)
    mov ecx, msg        ; Pointer to the message
    mov edx, 14         ; Length of the message + 0xA
    int 0x80            ; Invoke the system call

    ; Exit system call
    mov eax, 1          ; sys_exit system call number
    xor ebx, ebx        ; Exit code 0
    int 0x80            ; Invoke the system call
