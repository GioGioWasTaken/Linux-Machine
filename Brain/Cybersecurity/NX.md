## NX  : 

also referred to as XN and DEP, no execute. The stack cannot be executed. 

(* The Windows version of NX is DEP, which stands for Data Execution Prevention)

**Mitigation:** 

pie and libc memory regions have some executable memory spaces where instructions are stored.

**mmap with NX:** 

0x00007ffffffde000 0x00007ffffffff000 0x0000000000000000 rw- \[stack\]

but observe:
