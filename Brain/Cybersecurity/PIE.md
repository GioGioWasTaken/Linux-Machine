# What is PIE?

PIE, or position independent code , is a compilation option that allows executables to be loaded at any address in memory, making them independent of their load address. However, PIE alone does not provide randomization of the memory layout; it requires ASLR at the system level to achieve that.


- If the binary doesn't have PIE (Position-Independent Executable) enabled, the code segment (text section) AND ONLY THE CODE SEGMENT remains at a fixed address.

[!WARNING] However, the stack, heap, and libraries are still randomized by ASLR unless it's completely disabled.


- The stack address still varies because ASLR affects it, regardless of whether PIE is enabled or not.
- Disabling PIE just means the executable's code will have a fixed address, but other memory segments (like the stack) can still be randomized.
