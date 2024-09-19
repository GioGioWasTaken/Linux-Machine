# Primitives

- FSB of size 0x20(32 decimal):
    * `libc.so.6 : 0x7ffff7f57e43 --> 0x68732f6e69622f ('/bin/sh')` we will leak the addresses of this string
    * and the address of the `system` function using the FSB: `0x7ffff7df9c30`
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
- we will point it at the stack address of `name`, to call the shellcode stored there.
    * for that we need to find the address of name. First we leak main's `RBP`, from which it is in offset 0x20.
    * shellcode gets injected at expected location, control flow is redirected
VICTORYYYYYYYYYYYYYYYYYYYYYYY
VICTORYYYYYYYYYYYYYYYYYYYYYYY
VICTORYYYYYYYYYYYYYYYYYYYYYYY
VICTORYYYYYYYYYYYYYYYYYYYYYYY
VICTORYYYYYYYYYYYYYYYYYYYYYYY

## check out

- instant segfault when name is too long since it overwrites a value used for a `call function ` offset
