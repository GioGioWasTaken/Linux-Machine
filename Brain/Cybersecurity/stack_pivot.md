# Stack pivoting
Stack pivoting, is a general name for any exploitation technique that relies on moving ESP to a new address. This can have many uses.

(The below is in 32 bit. Of course, the numbers vary in 64 bit systems.)
## EBP2RET 
Situation: One can overwrite the saved `EBP` of the previous stack frame, but not the return address. We want to jump to `0xDEADBEEF`. 

`0xCAFEBABE` points to `0xDEADBEEF`

solution: overwrite `EBP` with `0xCAFEBABE-0x4`. This abuses the `leave` and `ret` instructions.

[!ATTENTION] The reason the overwrite also overwrites the value of `EBP` register, and not only the `EBP` value pushedto the stack, is that the **current frame's**  `EBP` register points to the location of the saved ebp.  

```asm

leave:
    mov ESP, EBP // move EBP of current frame to ESP 
    pop EBP // 

pop EBP:
    mov EBP, [ESP] // = saved ebp value
    add ESP, 0x4 // increment ESP since the stack moved.

ret:
    jmp [ESP] // ESP = 0xCAFEBABE now, and it points to our target address.

```


