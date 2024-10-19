# ASLR

- Differently from the other protections, ASLR is a kernel level protection. It's enabled per system and not per binary.

- [!WARNING] I am not sure about the truth of the below statement. PIE is a compiliation protection, yet I saw this somewhere.
 
A PIE executable is an ELF shared object (like a .so), as opposed to an ELF "executable".


- An ELF executable has a base address in the ELF headers(see [[ELF]]), set by the linker, so absolute addresses can be hard-coded into the machine code and data without needing relocations for fixups.

- It stands for "Address space layout randomization"
- `ASLR` does not move the stack. `ASLR` moves the code, which the stack references.


# Bypass

See: [[GOT_PLT]]


Article about ASLR in modern linux systems [here](http://rk700.github.io/2016/11/22/mmap-aslr/)
