# GOT

Without PIE, the addreses of the GOT table and PLT table are known statically. 

Pseudo code to explain them:
``````
; In the main program
call read@plt

; In the PLT (Procedure Linkage Table)
read@plt:
    jmp *read@got
    push #relocation_offset
    jmp .resolve

; In the dynamic linker's resolver
.resolve:
    ; Find the actual address of read in libc
    ; Write this address to read@got
    jmp read@libc

; In the GOT (Global Offset Table)
read@got: 
    .quad 0x4141414141414141  ; Initially points back to PLT, later filled with actual address
    ;  ...or  .quad [jmp .resolve]
``````


# Note:

## Fixed vs. Randomized Addresses:

With PIE disabled, the GOT's location is fixed and known.
However, the contents of the GOT (addresses in libc) are still randomized by ASLR.
Essentially, while I know statically the value of func@got(a fixed memory address), I don't know the value of *func@got.


## The Attacker's Challenge:

The attacker knows where the GOT is but doesn't know what values it contains.
They can't simply write a new address to the GOT because they don't know the correct address to write (due to ASLR).

If he knew what value it contains, he could use this information by calculating the offset of said function, from the target function.


## A Clever Workaround, that might sometimes work:

Instead of writing a full address, the attacker modifies the existing address in the GOT.
They use a gadget that adds a value to the contents of a memory location.
By carefully choosing this value, they can adjust the existing libc address to point to their desired function (one_gadget).

Essentially, even if I have no way of leaking *(func@got), it doesn't matter if i have a gadget that does:

add (func@got), value

seeing as add (similarly to functions that can be used to leak its value like puts), takes a pointer to a value, and reads it for me.

Look for gadgets that use a register or memory address in your control, as a pointer.

searching for [] might be wise.



## Why This Works:

The offset between functions within libc remains constant, even when ASLR randomizes the base address.
By adding or subtracting this offset from the existing GOT entry, the attacker can redirect execution without knowing absolute addresses.
