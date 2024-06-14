A compiled program’s memory is divided into five segments: `text`, `data`, `bss`, `heap`, and `stack`. Each segment represents a special portion of memory that is set aside for a certain purpose.

- the `text` also referred to as the `code segment` stores the assembly instructions executed by the binary. Execution is obviously not linear, with jumps and branches utilized constantly.
    - as an ELF binary executes the `text` segment, the following loop is iterated through:
        1. Reads the instruction that EIP is pointing to
        2. Adds the byte length of the instruction to EIP. See [[ARM assembly]] for more info about its eccentricities. 
        3. Executes the instruction that was read in step 1
        4. Goes back to step 1
    - the `text` segment is not writable. Attempts to write to it would result in a segfault and warning. Since it's not writable, it has a fixed size.
- the `data` and `bss` segments are used to store `global` and `static` variables(each one stores both. See the below).
    - `static variables` are variables that are only initialized once, and their value is retained through subsequent functions calls. They exist, of course, only inside the scope of the function that calls them. 
    - `data` has initialized globals, while `bss` has uninitiliazed globals (globals that are not initiliazed with any data.)
    - this is why global and static variables persist throughout the lifetime of the program -- they have their own memory segments.
    - the `data` and `bss` segments, also have a fixed size. `If it has a fixed size, it can be overflowed.`
- You are already very familiar with `The Heap` and `The Stack` so there is no need to mention them.
- Finally, one can assume what happens when `The Heap` and `The Stack` meet!
	![[Pasted image 20240607151555.png]]

Helpful information curated:
[ELF binary cheatsheet](https://gist.github.com/DtxdF/e6d940271e0efca7e0e2977723aec360)
