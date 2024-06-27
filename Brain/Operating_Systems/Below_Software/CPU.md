# CPU
- A CPU is a piece of hardware that, effectively, implements an assembly language in the lowest possible level: hardware. It's the interface of the programmer to the computer. It implements an ISA (instruction set architecture).


-  For example, in the x86 architecture, the pattern 10100000 is telling a CPU to add two numbers, and 000000101 to halt a computer.


- In the early days of computers, people had to write completely in binary. How does such a bit pattern cause a device to do something?
	- The reason is that underlying each instruction is a small circuit that implements the instruction. Similar to how a function/subroutine in a computer program is called by its name, a bit pattern is a name of a little function inside a CPU that got executed when the CPU finds one.

- A device with its own machine language is a programmable device, since a user can use the language to command the device to perform different actions

 - To write an OS for a Von Neumann computer, a programmer needs to be able to understand and write code that con- trols the cores components: CPU, memory, I/O devices, and bus. The CPU,  is the heart and brain of any com- puter system. Understanding a CPU is essential to writing an OS from scratch.


- To use these devices, a programmer needs to controls the CPU to use the programming interfaces of other devices. CPU is the only way, as CPU is the only direct device a programmer can use and the only de- vice that understand code written by a programmer.

- In a CPU, many OS concepts are already implemented directly in hard- ware, e.g. task switching, paging. A kernel programmer needs to know how to use the hardware features, to avoid duplicating such concepts in software, thus wasting computer resources.

- To effectively use the CPU, a programmer needs to understand the documentation provided from CPU manufacturer. For example, `Intel® 64 and IA-32 Architectures Software Developer Manuals`.
### Reference to:
 - [[BINARY_DECODERS]]
 