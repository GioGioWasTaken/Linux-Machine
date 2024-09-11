# Primitives

- FSB of size 0x20(32 decimal):
    * `libc.so.6 : 0x7ffff7f57e43 --> 0x68732f6e69622f ('/bin/sh')` we will leak the addresses of this string
    * and `system` function using the FSB: `0x7ffff7df9c30`
- UAF: 
    - Free up `o`
    - call 3
    - write the text to `echo3`
    - call 3 again:
```asm

0x000000000040088f <+8>:     mov    rax,QWORD PTR [rip+0x201802]        # 0x602098 <o>
0x0000000000400896 <+15>:    mov    rdx,QWORD PTR [rax+0x18]

```

- the address it's referencing, o, now points to the newly allocated address that I control :)
- we will point it at `name`, and put shellcode to call the system function in name.
