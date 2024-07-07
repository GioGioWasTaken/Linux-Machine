# Why do we need virtual memory?

# Problem 1: Memory fragmentation:
![[Pasted image 20240610174759.png]]
How do we access an array index here? How do we not accidentally read values out of bound? Sure, this can be worked around, but the solution will be convoluted. We need some sort of indirection.

# Problem 2 Security:
If multiple programs attempt to write to the same location, they will constantly corrupt each other's state, and may lead to undefined behaviour, and crushes.

# Problem 3: There's simply not enough memory
When we don't have enough memory, the program crashes. This is why old 20th century programs crushed all the time. We can use SWAP files if we run out of RAM.


# To summarise:
1. Not enough memory -> Crash if we run out of RAM.
2. Memory fragmentation -> run out of space. `The Heap` also has to deal with this issue
4. Security -> Corrupt other programs' data.


# The solution

Each program gets its own `virtual memory space`. From henceforth `RAM` (See [[RAM]]) will be referred to as `physical memory` (from here `physical address space`). We need to map `Virtual memory` to `physical memory`. Another reason we refer to it as `physical memory` is that RAM isn't the only physical memory the program can access. It can also access memory or registers of other devices that are mapped to the same address space. Upon booting, the OS reserves some of the RAM for itself, while the rest is used for programs.


# This is done using `Page tables`

- Virtual memory allows a program to access memory beyond its physical limits by mapping virtual addresses to physical addresses.

- Page tables are used to store the mappings between virtual and physical addresses.

- Each page table entry stores a physical address for a corresponding virtual address.

- The size of a page table can be large, so the memory is divided into pages, and pages are mapped instead of individual words.

- Each page table entry represents a range of virtual addresses (typically 4 kilobytes). For example, page table entry #1 might have the range 0-4095

- The trade-off is that instead of moving a single word out of memory at a time, 4 kilobytes of data are moved, but this works well in practice because nearby memory locations are often accessed at the same time.

- There is a special piece of hardware called the TLB whose job is translating these page table entries into physical memory when a process attempts to write to them. Virtual memory, is divided into segments. See: [[ELF]]

# Page files/ swap files
Even if a program exhausts all of the virtual memory assigned to it, we can use something called a swap file or swap space, in order to use more storage. This is yet another benefit of virtual memory

A swap file extends the virtual memory available to the system by using disk space. When the system's RAM is fully utilized, inactive pages of memory are moved to the swap file to free up RAM for active processes. This helps to prevent the system from running out of memory and potentially crashing.

However, swap space is much slower than RAM because it involves disk I/O operations. Therefore, it should be used as a fallback mechanism and not as a replacement for adequate physical memory.
