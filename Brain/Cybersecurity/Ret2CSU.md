# Ret2CSU

Dynamically linked binaries need to have some code stored on them in order for the dynmic linking process to be even viable.
In certain cases,   where the amount of gadgets available for use is scarce, it might be wise to turn to these functions, for more gadgets.


CSU stands for C Startup. It refers to the set of object files and source code that handle the initialization of a C program before the main function is called. This includes:
    - Setting up the runtime environment (the stack, for example.)
    - Initializing global variables.
    - Calling constructors of C++ objects (if present).
    - Finally, invoking the main function.



These functions contain within them a selection of gadgets that we can use to populate registers we lack gadgets for, most importantly `__libc_csu_init`, which contains the following two gadgets:

`
0x004011a2      5b             pop rbx
0x004011a3      5d             pop rbp
0x004011a4      415c           pop r12
0x004011a6      415d           pop r13
0x004011a8      415e           pop r14
0x004011aa      415f           pop r15
0x004011ac      c3             ret
`

`
0x00401188      4c89f2         mov rdx, r14                ; char **ubp_av
0x0040118b      4c89ee         mov rsi, r13                ; int argc
0x0040118e      4489e7         mov edi, r12d               ; func main
0x00401191      41ff14df       call qword [r15 + rbx*8]
`
