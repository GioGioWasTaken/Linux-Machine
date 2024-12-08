## General information
- If a binary file were to only consist of `data` and `code`, from the perspective of the OS the file is undefined. Which region is code? which region is `protected`? This is why we have file formats.

- When a source file is compiled, the generated machine code is stored in an `object file`, which is just a block of binary. `Object Files` can be combined to produce an executable binary, which is a complete binary program runnable in an operating system.

- ELF is a common file format for all: `executables, object code, shared libraries`, and `core dumps`.

- Segments and sections are the main content of an ELF binary, which are the code and data, divided into chunks of different purposes.

- A `segment` is a composition of zero or more `sections` and is directly loaded by an operating system at runtime.

- A section is a block of binary that is either:
	-  actual program code and data that is available in memory when a
	program runs.
	-  metadata about other sections used only in the linking process, that disappears from the final executable.

- The linker uses `sections` to build `segments`. Object files, are ELFs before the linking stage. They are made of `sections`.

## ELF header

- All of this information can be viewed by running: `readelf -h <filename>`

![[Pasted image 20240628190409.png]]
To be more easy on the eyes, let's treat it as a struct (which is how it's implemented either way). 
- It starts with a sequence of 4 `'magic'` bytes. the value `0x7f` followed by ELF in ascii this lets the OS (or any program that would like to know) that the file is the ELF type. 
- After that, We have the filetype halfword(here a word is defined as 4 bytes)which defines the type of the file. 
	- `0x0001` is used for `object` files.
	- `0x0002` is used for binaries without ASLR.
	-  `0x0003` is used for  binaries that have ASLR(or PIE) enabled, and shared object files.
	- `0x004` is used for core dumps.
 ![[Pasted image 20240628191009.png]] 
- the version byte is always 1. ELF has been in version 1 since it's first release!
- to avoid clobbering this document with barely relevant information, simply refer to [this YouTube video ](https://www.youtube.com/channel/UC3S8vxwRfqLBdIhgRlDRVzw) for more information.


## Sections and the Section Header Table
* note that sections are largely irrelavent to reverse engineering and debugging , seeing as binaries only use segments
- we can strip a binary of its sections, and it will work perfectly fine.

As we know already, code and data compose a program. However, not all types of code and data have the same purpose. For that reason, instead of a big chunk of code and data, they are divided into smaller chunks(`sections`), and each section must satisfy the following conditions:

- Every section in an object file has exactly one section header describing it. But, section headers may exist that do not have a section.

-  Each section occupies one contiguous (possibly empty) sequence of bytes within a file. That means, there’s no two regions of bytes that are the same section.

-  Sections in a file may not overlap. No byte in a file resides in more than one section.

-  An object file may have inactive space. The various headers and the sections might not “cover” every byte in an object file. The contents of the inactive data are unspecified.
#### Relocation
- `Relocation` is the process of adjusting addresses within a program so that it can execute correctly when loaded into memory. During compilation, the compiler generates object files with placeholder addresses for functions and variables. The linker combines these object files into an executable or shared library, creating relocation entries for addresses that need adjustment.
	- this is the reason why object file sections address info are not set.


- When the program is loaded into memory, the loader uses these relocation entries to modify addresses so they point to the correct memory locations. This ensures that all references within the program are accurate, allowing it to run correctly. For dynamic linking, mechanisms like the Global Offset Table (GOT) and Procedure Linkage Table (PLT) handle runtime relocation, resolving addresses of global variables and functions in shared libraries. The dynamic linker updates the GOT and PLT entries, enabling the program to access shared library symbols efficiently.


## Segments and the Program Header Table
- we can look at  segments using `readelf --segments <filename>`

A program header table is an array of `program headers` that defines the memory layout of a program at runtime. A `program header` is a description of a `program segment`. A `program segment` is a collection of related sections. A segment contains zero or more sections. OSes only look at segments.
![[Pasted image 20240628195931.png]]
We define a `segment` as an array that contains the following: (I will not be writing about everything, reference video linked above):

- A type 
	-  PT_NULL is a placeholder that disables a segment
	- PT_LOAD refers to segments that will be loaded into memory. How they will be loaded is specified in the `flags` field.
	- PT_DYNAMIC contains information required for dynamically linked binaries.
- An offset
- virtual and physical address


## An ELF's sections

[!note] Note: For an executable program, an ELF header and a segment are the bare minimum, with sections being optional.

[!Attention] But even so, it's common for an executable to have a ".text" section for the code and ".data" section for initialized data.


Sections can be viewed with `objdump <binary> -h`

- Libraries don't have segments, but only sections because they are used for linking purposes.

A compiled program’s memory is (mainly) divided into five sections: `text`, `data`, `bss`, `heap`, and `stack`. Each segment represents a special portion of memory that is set aside for a certain purpose.
- **Note:** there's also `.rodata` which is for read-only data.
- the `text` also referred to as the `code segment` stores the assembly instructions executed by the binary. Execution is obviously not linear, with jumps and branches utilized constantly.
    - as an ELF binary executes the `text` segment, the following loop is iterated through:
        1. Reads the instruction that EIP is pointing to
        2. Adds the byte length of the instruction to EIP. See [[ARM assembly]] for more info about its eccentricities. 
        3. Executes the instruction that was read in step 1
        4. Goes back to step 1
    - the `text` segment is not writable. Attempts to write to it would result in a segfault and warning. Since it's not writable, it has a fixed size.
- the `data` and `bss` sections are used to store `global` and `static` variables(each one stores both. See the below).
    - `static variables` are variables that are only initialized once, and their value is retained through subsequent functions calls. They exist, of course, only inside the scope of the function that calls them. 
    - `data` has initialized globals, while `bss` has uninitiliazed globals (globals that are not initiliazed with any data.)
    - this is why global and static variables persist throughout the lifetime of the program -- they have their own memory sections.
    - the `data` and `bss` sections, also have a fixed size. `If it has a fixed size, it can be overflowed.`

- You are already very familiar with `The Heap` and `The Stack` so there is no need to mention them.
- Finally, one can assume what happens when `The Heap` and `The Stack` meet!
	![[Pasted image 20240607151555.png]]

Helpful information curated:
[ELF binary cheatsheet](https://gist.github.com/DtxdF/e6d940271e0efca7e0e2977723aec360)


### ReadELF output:

`
readelf -l <binary>
`
E.X:

`
LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
0x000000000000073c 0x000000000000073c  R E    0x200000
`

- Interpretation: 
	* file Offset (0x0000000000000000):

	    * This tells you where in the file this segment begins. In this case, it starts at offset 0 in the ELF file, meaning it's the first segment loaded into memory.

	- Virtual Address (0x0000000000400000):

	    * This is where the segment is loaded into memory. Here, it starts at the virtual address 0x400000. This is the memory address where the executable (or the program) will place this segment.

	- Physical Address (0x0000000000400000):

	    *This field is generally used by systems with physical memory addressing (like embedded systems). In most user-level ELF files on modern systems (like Linux on x86-64), this field is not used and mirrors the virtual address (0x400000).

	- File Size (`FileSiz` = 0x000000000000073c):

	    * This is the size of the segment on disk. The value 0x73c means 1,860 bytes are present in the file.
	    Typically, this segment contains the code section (.text), which is why it's marked R E (Read, Execute). It means this part of the binary contains executable code.

	- Memory Size (`MemSiz` = 0x000000000000073c):

	    *This is the size of the segment in memory. In this case, MemSiz matches FileSiz (0x73c), which means the entire segment is loaded into memory, with no additional space required.
	    This is typical for the code section, which doesn't need extra memory for uninitialized data.

	- And lastly, `Align` (0x200000).



```

readelf -lW lnstat (W for wide, better output)

Elf file type is DYN (Position-Independent Executable file)
Entry point 0x1c00
There are 9 program headers, starting at offset 64

Program Headers:
Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align
PHDR           0x000040 0x0000000000000040 0x0000000000000040 0x0001f8 0x0001f8 R   0x8
INTERP         0x000238 0x0000000000000238 0x0000000000000238 0x00001b 0x00001b R   0x1
[Requesting program interpreter: /lib/ld-linux-aarch64.so.1]
LOAD           0x000000 0x0000000000000000 0x0000000000000000 0x003f7c 0x003f7c R E 0x10000
LOAD           0x00fc48 0x000000000001fc48 0x000000000001fc48 0x000528 0x001190 RW  0x10000
DYNAMIC        0x00fc58 0x000000000001fc58 0x000000000001fc58 0x000200 0x000200 RW  0x8
NOTE           0x000254 0x0000000000000254 0x0000000000000254 0x0000e0 0x0000e0 R   0x4
GNU_EH_FRAME   0x003610 0x0000000000003610 0x0000000000003610 0x0001b4 0x0001b4 R   0x4
GNU_STACK      0x000000 0x0000000000000000 0x0000000000000000 0x000000 0x000000 RW  0x10
GNU_RELRO      0x00fc48 0x000000000001fc48 0x000000000001fc48 0x0003b8 0x0003b8 R   0x1

 Section to Segment mapping:
 Segment Sections...
 00     
 01     .interp 
 02     .interp .note.gnu.build-id .note.ABI-tag .note.package .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame 
 03     .init_array .fini_array .dynamic .got .data .bss 
 04     .dynamic 
 05     .note.gnu.build-id .note.ABI-tag .note.package 
 06     .eh_frame_hdr 
 07     
 08     .init_array .fini_array .dynamic .got 

```
The above program has 9 program headers, then, the segment mapping indicates in which program header (from 00 to 08) each section is located.

PHDR = 00
Dynamic = 05, etc.

### An ELF's Segments:

#### PHDR:

Program HeaDeR, for its metadata and the header tables.

#### INTRP

Indicates the path of the loader to use to load the binary into memory.

#### LOAD

These headers are used to indicate how to load a binary into memory. Each LOAD header indicates a region of memory (size, permissions and alignment) and indicates the bytes of the ELF binary to copy in there.

Breakdown example:

the second one has a size of 0x1190, should be located at 0x1fc48 with permissions read and write and will be filled with 0x528 from the offset 0xfc48 (it doesn't fill all the reserved space). This memory will contain the sections : `.init_array .fini_array .dynamic .got .data .bss`

#### Dynamic

This header helps to link programs to their library dependencies and apply relocations. Check the 
`.dynamic` section, which is the only section mapped to the segment.

More info found [here](https://book.hacktricks.xyz/binary-exploitation/basic-stack-binary-exploitation-methodology/elf-tricks).

#### Misc: 

- The BSS section immediately follows the .data section in memory. 
- The memory range for .bss starts after .data and occupies the extra space defined by MemSiz - FileSiz
