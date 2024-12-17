# Stack alignment
Alignment Requirement: Many systems require that memory allocations be aligned to certain boundaries (e.g., 16 bytes). Proper alignment can improve performance due to the way CPUs handle memory access, and certain types of data may have specific alignment requirements.

## How does this look in assembly?

Well, it can be as simple as:

```asm

sub     rsp, 15        ; Add padding
and     rsp, 0xFFFFFFFFFFFFFFF0 ; Align to 16 bytes
```
or, in 32 bit:
```asm

sub     esp, 15        ; Add padding
and     esp, 0xFFFFFFF0 ; Align to 16 bytes
```

... And it can also look like this:

```asm
lea    rdx, [rax+8]         ; Add 8 for alignment adjustment
mov    eax, 16              ; Set divisor to 16
sub    rax, 1               ; Subtract 1 for rounding up
add    rax, rdx             ; Add the current size plus 8 plus 15
mov    ecx, 16              ; Set divisor to 16
mov    edx, 0               ; Clear edx for division
div    rcx                  ; Divide rax by 16
imul   rax, rax, 16         ; Multiply quotient by 16
```

# Stack layout
- The stack layout can be read about [here](https://aeb.win.tue.nl/linux/hh/stack-layout.html)



# Program startup

When an ELF file starts The ELF loader parses the ELF file, maps the various program segments in the memory, sets up the entry point and initializes the process stack. It puts ELF auxiliary vectors on the process stack along with other information like argc, argv, envp. After initialization, a process' stack looks something like this: 


position            content                     size (bytes) + comment
  ------------------------------------------------------------------------

``` C
stack pointer ->  [ argc = number of args ]     4
[ argv[0] (pointer) ]         4   (program name)
[ argv[1] (pointer) ]         4
[ argv[..] (pointer) ]        4 * x
[ argv[n - 1] (pointer) ]     4
[ argv[n] (pointer) ]         4   (= NULL)

[ envp[0] (pointer) ]         4
[ envp[1] (pointer) ]         4
[ envp[..] (pointer) ]        4
[ envp[terminator] (pointer) ]      4   (= NULL)

[ auxv[0] (Elf32_auxv_t) ]    8
[ auxv[1] (Elf32_auxv_t) ]    8
[ auxv[..] (Elf32_auxv_t) ]   8
[ auxv[terminator] (Elf32_auxv_t) ] 8   (= AT_NULL vector)

[ padding ]                   0 - 16

[ argument ASCIIZ strings ]   >= 0
[ environment ASCIIZ str. ]   >= 0

  (0xbffffffc)      [ end marker ]                4   (= NULL)

  (0xc0000000)      < bottom of stack >           0   (virtual)

```

  ------------------------------------------------------------------------

Therefore, if we are able to leak info from the stack, we can leak the Vdso address using AT_SYSINFO(This is certain), as well as the stack address using the AT_RAND elf auxiliary, which points to the location in the stack right after the auxillary vector (I think, need further confirmation on this part.)

## ELF auxillary vectors:

 ELF auxiliary vectors are a mechanism to transfer certain kernel level information to the user processes. An example of such an information is the pointer to the system call entry point in the memory (AT_SYSINFO); this information is dynamic in nature and is only known after kernel has finished loading.

The information is passed on to the user processes by binary loaders which are part of the kernel subsystem itself; either built-in the kernel or a kernel module. Binary loaders convert a binary file, a program, into a process on the system. Usually there is a different loader for each binary format; thankfully there are not many binary formats - most of the linux based systems now use ELF binaries. ELF binary loader is defined in the following file /usr/src/linux/fs/binfmt_elf.c. 
