# ROP :

The basis of ROP is chaining together small chunks of code already present within the binary itself in such a way to do what you wish. This often involves passing parameters to functions already present within libc, such as system.


More info [here](https://ir0nstone.gitbook.io/notes/types/stack/return-oriented-programming/calling-conventions) 


## Types of ROP:

- [[Ret2CSU]]
- [[Ret2PLT]]
- [[Ret2libc]]
- [[Ret2Syscall]]
- [[SRop]]

# NOTE!!!!

My mind is completely blown!!!! x86_64/32 DOES NOT have any demand that code exeuction must be aligned to a specific number. That is to say, if you can jump to the middle of the gadget, and if that happens to be valid assmebly code, it will run perfectly!!!!!


1. Of course, `mov`s between registers are equivalent to having control over all of these regs. 
2. xor gadgets can be used instead of pop, since `xor num, num` is always 0, and `xor 0, num`, is always num. Therefore:
    a. `pop r13`
    b. `xor r12, r12` 
    c. `xor r12, r13`
will allow us full control over both r12 and r13.
3. xchg will allow us to switch values between two registers.



## Finding gadgets

1. You can use ROPGadget
2. And radare2's `/R` command (`/Rl` for the chain to be in the same line)
3. Ropper also exists, though i haven't tried it so far.
