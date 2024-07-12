Are devices that interpret opcodes, such as `0x00` as assembly instructions.

We can use binary decoders to simplify calling specific physical implementations of instructions on the CPU. Now we can simplify this even further by making a program that translates `text` to `OPCODES`. For this we need some storage device that can store data.


Once the above has been defined, it is easy to conclude that a computer runs programs by following the following:
- Fetch an instruction from a storage device.
-  Decode the instruction.
-  Execute the instruction.

This is called a `fetch-decode-execute` cycle.


Assembly language is a step up from writing 0 and 1. As time goes by,
people realized that many pieces of assembly code had repeating patterns
of usages. It would be nice if instead of writing all the repeating blocks
of code all over again in all places, we simply refer to such blocks of code
with easier to use text forms. For example, a block of assembly code checks
whether one variable is greater than another and if so, execute a block
of code, else execute another block of code; in C, such block of assembly
code is represented by an if statement that is close to human language.

Programming is all about generalizing and abstracting.

![[Pasted image 20240627145622.png]]

