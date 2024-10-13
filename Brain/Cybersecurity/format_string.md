## Useful tricks

- Leak the nth address of size %x. E.G:
     * %<n>$X —> : ("%3$d", var1, var2, var3) —> Access to var3

- It is possible to trigger a `malloc` call with a FSB. If we write more bytes then the size of the stack, the program will start allocating memory on the heap.

## Different modifiers and their sizes:

- %x: Prints an unsigned integer in hexadecimal format. By default, it prints a unsigned int, which is usually 4 bytes (32 bits) on most systems.
- %lx: Prints an unsigned long in hexadecimal format. The size of unsigned long can vary depending on the platform:
     - On 32-bit systems, unsigned long is typically 4 bytes (32 bits).
     - On 64-bit systems, unsigned long is typically 8 bytes (64 bits).
- %d —> Entire
- %u —> Unsigned
- %p —> Pointer
- %n —> Number of written bytes
- %hn —> Occupies 2 bytes instead of 4


