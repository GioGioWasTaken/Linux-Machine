## Lazy binding process:
Whenever an external symbol is called, the assembly will call a stub, which is a block of assembly code that either invokes the dynamic linker to locate and write the address of the symbol into the GOT, or if the address exists jumps there.
