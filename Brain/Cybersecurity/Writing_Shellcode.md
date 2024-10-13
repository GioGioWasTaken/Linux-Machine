- learning to write your own shellcode is integral for any attacker. Writing your own shellcode will allow you to do whatever you want to a compromised system. Want to add a new admin user to the target computer? Want it to recursively send its data to you, and then delete it? Shellcode, (from here the term payload comes) is the endgame of any attack.

- Shellcode must be self contained, in other words it must be PIC (Position Independent Code).
- To give an example, an ASM hello world program can store its "Hello, World!" string in the `.data` segment. We don't have that luxary.
    - In shellcode, the bytes for the string "Hello, world!" must be mixed together with the bytes for the assembly instructions, since there aren’t definable or predictable memory segments.
    - However, to access the string as data we need a pointer to it. When the shellcode gets executed, it could be any- where in memory. The string’s absolute memory address needs to be calcu- lated relative to EIP.
    - This is why we overwrite the return address on the stack.


- There are several techniques to avoid writing shellcode that contains null bytes. One such technique, is making a second function that calls upwards to the function that "replaces" the return address with the value we stored on the stack. Since we are jumping backwards, according to `Two's complement` the value will be very large and prepended by `0xffffff....`. So there are no dangerous null bytes.
- Using the small registers as described in [[Assemby_and_RE]] like `al` for EAX, will allow us to write small values to them, without having the registers prepended with 0x0000....
- both of these methods can be seen below:
```asm
BITS 32 ; Tell nasm this is 32-bit code.

jmp short one ; Jump down to a call at the end.

two:


; ssize_t write(int fd, const void *buf, size_t count);

pop ecx ; Pop the return address (string ptr) into ecx.
xor eax, eax ; Zero out full 32 bits of eax register.
mov al, 4 ; Write syscall #4 to the low byte of eax.
xor ebx, ebx ; Zero out ebx.
inc ebx ; Increment ebx to 1, STDOUT file descriptor.
xor edx, edx
mov dl, 15 ; Length of the string
int 0x80 ; Do syscall: write(1, string, 14)

; void _exit(int status);

mov al, 1 ; Exit syscall #1, the top 3 bytes are still zeroed.
dec ebx ; Decrement ebx back down to 0 for status = 0.
int 0x80 ; Do syscall: exit(0)


one:

call two ; Call back upwards to avoid null bytes
db "Hello, world!", 0x0a, 0x0d ; with newline and carriage return bytes.

```

"Hello World!\x0A\x0D" will be value at the top of the stack, so it will be popped into ECX, instead of the return address. We now have our own `data` segment, in our self contained shellcode!
