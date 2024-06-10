## NX  : 

also referred to as XN and DEP, no execute. The `stack` and `Heap` cannot be executed. 

(* The Windows version of NX is DEP, which stands for Data Execution Prevention)

**Mitigation:** 

Use [ROP](ROP)  to redirect code execution. 

**mmap with NX:** 

0x00007ffffffde000 0x00007ffffffff000 0x0000000000000000 rw- \[stack\]
0x0000555555559000 0x000055555557a000 rw-p	\[heap\]

