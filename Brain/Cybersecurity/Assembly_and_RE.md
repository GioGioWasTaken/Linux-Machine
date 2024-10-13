# useful interfaces to assembly
- Debug using GDB-Peda
    - [Short Cheatsheet](https://github.com/nnamon/linux-exploitation-course/blob/master/lessons/3_intro_to_tools/lessonplan.md)

- Use Ghidra
    - [Ghidra start](https://guyinatuxedo.github.io/02-intro_tooling/ghidra/index.html) 
- To write assembly comfortambly, use neovim with an LSP server.


# Some referesher on assembly: 
 - The registers EAX, EBX, ECX, EDX, ESI, EDI, EBP, and ESP can all be used as operands, while the EIP register cannot.
- The int instruction (which stands for interrupt) sends an interrupt signal to the system. Interrupts are used to handle events like system calls, hardware signals, or exceptions. Two common interrupt signals are:
    - int 0x80, which sends a syscall interrupt in linux
    - int 0x21, which is used for DOS interrupts. This is no longer used in modern windows systems, which use the `windows-api` instead.
    - when the OS executes a syscall, it checks `EAX` for the syscall number, and `EBX, ECX, EDX` to hold the first, second, and third arguments respectively.
# basic assembly:
```asm

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
```

# Register variations

The EAX, EBX, ECX, EDX, ESI, EDI, EBP, and ESP registers are 32 bits in width. 

The E stands for extended, because these were originally 16-bit registers called AX, BX, CX, DX, SI, DI, BP, and SP.

These original 16-bit versions of the registers can still be used for accessing the first 16 bits of each corresponding 32-bit register.

Furthermore, the individual bytes of the AX, BX, CX, and DX registers can be accessed as 8-bit registers called AL, AH, BL, BH, CL, CH, DL, and DH, where L stands for low byte and H for high byte.

A lower, A higher
B lower, B higher... etc. The registers, at the start, were just , then, register A, B, C ....

Naturally, assembly instructions using the smaller registers only need to specify operands up to the register’s bit width. The three variations of a mov instruction are shown below.

![[Pasted image 20240611120537.png]]
Using the AL, BL, CL, or DL register will put the correct least significant
byte into the corresponding extended register without creating any null bytes in the machine code. This makes them ideal for shellcode writing.
# C Code as it is seen in assembly
- X86_64 parameter call convention is as follows: 

| Register | Argument|
|----------|----------|
| 1. `RDI`    | First argument|
| 2. `RSI`    | Second argument|
| 3. `RDX`    | Third argument |
| 4. `RCX`    | Fourth argument|
| 5. `R8`     | Fifth argument |
| 6. `R9`     | Sixth argument |

- GDB has an option to deobscuify CPP function names. Use it.

- Since function arguments are also passed on the stack, there needs to be space for any that this function wants to pass to another.  So while a function might only need x amount of bytes for local variables, $esp is often decremented by a bigger bytesize so that there is space for function arguments.
# More assembly instructions

- `sete`, `setl`, `setge`, all check the result of the previous `cmp` operation, stored in the CPU flags, and respectively store the result in the operand passed to it(set equal, set less, set greater equal )
- `shl` and `shr` are used to shift bits left and right. 
- `movzx` is a `mov` instruction that also pads the remaining bytes with zeros. 

- [[Writing_Shellcode]]

# Possible reasons for segfaults:
- Read more about data alignment and its role [here](Data_alignment).

- In assembly, the OS expects some values, depending on their size, to be aligned in some specific manner. 4 byte values must end in a hex digit that's divisible by 4, and the same goes for 8 byte values such as ESP. More info about stack alignment right below.  
	- This can be beaten by chaining a return addresses into the payload, before the target address, thus moving ESP to a location so that it's properly aligned and a segfault doesn't occur.

- Remember that not only stack allignment matters, but also ESP. In some instances, your shellcode has potential to move ESP to a location such that it overwrites itself on the stack. 




[Reverse engineering Resource list](https://gist.github.com/DtxdF/9c9297945bd7165c53b264ec597a9c39)

