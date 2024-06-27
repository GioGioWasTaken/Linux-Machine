Recall that an assembly instruction is simply a fixed-size series of bits.
The length of an instruction varies and depends on how complicated an
instruction is. What every instruction shares is a common format described
in the figure above that divides the bits of an instruction into smaller
parts that encode different types of information.

![[Pasted image 20240627174501.png]]

- An instruction prefix is an optional prefix to an instruction that makes it behave a bit differently. For example:
	- ``` add eax, ecx``` -> 66  01 C8 -> 66 is a prefix 
	-  The 0x66 prefix limits the operand sizes to 16 bits when in 32 bit mode. The opposite happens when the CPU is in 16 bit mode.

-  MODR/M is the register or memory address to be used as an operand
	- mod field, or modifier field, is combined with r/m field for a total of 5 bits of information to encode 32 possible values: 8 registers and 24 addressing modes.
	- reg/opcode field encodes either a register operand, or extends the Opcode field with 3 more bits.
	- there are a lot of possible ModR/M values...
		![[Pasted image 20240627175121.png]]
		- TO READ THIS TABLE
			- look at the byte value next to the Opcode to know what the corresponding operands are
- ![[Pasted image 20240627175656.png]]
	- Effective address = 1 ∗ (12 ∗ n) + base
	- Base is the starting address
	- We can observe the same thing, in C, when dereferencing a pointer. E.g.
		```C
	int num[4]= {1,2,3,4}) ;
	num[1] -> *(num+1*elementsize)
	```
- ![[Pasted image 20240627180329.png]]