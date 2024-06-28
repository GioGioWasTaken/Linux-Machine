# CPU
- A CPU is a piece of hardware that, effectively, implements an assembly language in the lowest possible level: hardware. It's the interface of the programmer to the computer. It implements an ISA (instruction set architecture).

-  For example, in the x86 architecture, the pattern 10100000 is telling a CPU to add two numbers, and 000000101 to halt a computer.

- In the early days of computers, people had to write completely in binary. This might make one ask oneself, how does such a bit pattern cause a device to do something?
	- The reason is that underlying each instruction is a small circuit that implements the instruction. Similar to how a function/subroutine in a computer program is called by its name, a bit pattern is a name of a little function inside a CPU that got executed when the CPU finds one.

- A device with its own machine language is a programmable device, since a user can use the language to command the device to perform different actions

 - To write an OS for a Von Neumann computer, a programmer needs to be able to understand and write code that controls the cores components: CPU, memory, I/O devices, and bus. The CPU,  is the heart and brain of any computer system. Understanding a CPU is essential to writing an OS from scratch.

-  The CPU is the only direct device a programmer can use and the only device that can understand code written by a programmer.

- In a CPU, many OS concepts are already implemented directly in hard- ware, e.g. task switching, paging. A kernel programmer needs to know how to use the hardware features, to avoid duplicating such concepts in software, thus wasting computer resources.

- To effectively use the CPU, a programmer needs to understand the documentation provided from CPU manufacturer. For example, `Intel® 64 and IA-32 Architectures Software Developer Manuals`.

# CPUs from the perspective of an OS developer
- The CPU has different operating modes. Read more [here](CPU_OPERATING_MODES.md)
### Reference to:
 - [[BINARY_DECODERS]]
 