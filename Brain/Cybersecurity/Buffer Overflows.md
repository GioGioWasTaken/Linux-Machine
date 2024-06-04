- Debug using GDB-Peda
    - [Short Cheatsheet]()
- Use Ghidra
    - [Ghidra start](https://guyinatuxedo.github.io/02-intro_tooling/ghidra/index.html) 
- There are several very commonly used buffer overflow mitigations. Here is a short description of them:
	- [NX](NX) 
	- [RELRO](RELRO) 
    - [ASLR](ASLR) 
    - [PIE](PIE)

## RELRO:

Makes some areas in memory, most notably the GOT table, only readable and not writable.

**Mitigations:** 

Do not write to these areas, this would result in a segfault. Find a different area to target.

