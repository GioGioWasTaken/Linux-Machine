The purpose of this file is to gather some details about the way the assembler should work in one central local file. This was used across my development process to reduce the overhead of checking my browser for details every time I want to code something.


# targeted Architecture details

8 registers: r0, r1, r2, r3, r4, r5, r6, r7.
the size of a register is 15 bits.

The LSB is is the 0th bit, and the MSB is the 14th bit. 
As well as a PSW ( program status word) register

memory size of 4096 cells, each cell has a size of 15 bytes. A word is defined as one cell.

16 instructions:

0 mov
1 cmp
2 add
3 sub
4 lea
5 clr
6 not
7 inc
8 dec
9 jmp
10 bne
11 red
12 prn
13 jsr
14 rts
15 stop

 


# Lexer details
- Needs to ignore all whitespaces, tabs, etc.
- a number is defined as a + or - symbol followed by numbers in decimal -- C standard lib's atoi function complies under this.
- printable ascii characters only

# General info

- All data structures except the data and instruction memory images , are to be implemented as a linked list or some other data structure whose size is not predetermined.

# Macro/ preprocessor details
- Assume no macro calls are made before the decleration (if there are such calls this is undefined)
- Duplicate macros , as well as macros with register, instruction, or label names, are not allowed


# Label details
- labels are case sensitive
- labels may not be defined more than once
- labels may not use register or instruction words
- labels may get called before their definition, this is proper.
- when a label's address is stored in the tables (data and code respectively),
    - if it's a code label, the address will be the address of the first word of the instruction. 
    - if it's a data label, the address will be the current DC address 
- A label may be composed out of no more than 31 characters
- A la

# Anatomy of an instruction (binary) 
## first word
in little endian: 
- (14-11): OPCODE in binary
- (10-7): Toggle the correct bit according to the addressing type of the source operand.
# Addressing: 
bit number | rule
4 --> 10
- 0 | prepended by a pound symbol
- 2 | prepended by an asterisk
- 3 | is the name of a register
- 1 | is none of the above (assumed to be a label, either defined or to be defined)



- (6-3): Toggle the correct bit according to the addressing type of the source operand.
- (2-0): ARE:
    - the first word (of a statement, not a .data or .string directive) will always have A (absolute) toggled on.

## Second and third words
- Depending on how many arguments the instruction takes
- 

