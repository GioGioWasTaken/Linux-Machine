- Differently from the other protections, ASLR is a kernel level protection. It's enabled per system and not per binary.

[!WARNING] I am not too sure what's the dynamic between ASLR and PIE as of my writing this. Keep getting conflicting answers.

- A PIE executable is an ELF shared object (like a .so), as opposed to an ELF "executable".
- An ELF executable has a base address in the ELF headers(see [[ELF]]), set by the linker, so absolute addresses can be hard-coded into the machine code and data without needing relocations for fixups.

- It stands for "Address space layout randomization"
- `ASLR` does not move the stack. `ASLR` moves the code, which the stack references.
