- GDB tricks that could be useful:
	-  use `/s` to include source code before assembly
	- use `until <linenumber>` to make gdb continue until a line number. This is useful when trying to skip loops that loop over many times. (or just set a breakpoint after.)

- * note: learn about DWARF and DIE*


# Display formats

x – Hexadecimal
d – Signed decimal
u – Unsigned decimal
o – Octal
t – Binary (t = two)
f – Floating-point
a – Address (in hexadecimal with symbolic representation if available)
i – Instruction (disassembles and shows assembly instructions)
c – Character (interprets each byte as an ASCII character)
s – String (interprets memory as a null-terminated string)

# Size modifiers

b: byte (1 byte, 8 bits)
h: halfword (2 bytes, 16 bits)
w: word (4 bytes, 32 bits)
g: giant/quad word (8 bytes, 64 bits)

So, the general form x/Nx<size> lets you specify the number (N) of units and the size (b, h, w, g) of data you want to inspect.
