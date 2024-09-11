Differently from the other protections, ASLR is a kernel level protection. It's enabled per system and not per binary.

if [[PIE]] is enabled, the OS will do ASLR on the binary. If ASLR is turned off in the OS, the binary wouldn't have PIE , even if it was compiled as to have it.

It stands for "Address space layout randomization"

`ASLR` does not move the stack. `ASLR` moves the code, which the stack references.
