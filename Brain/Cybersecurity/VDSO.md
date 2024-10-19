# VDSO

The `VDSO` (Virtual Dynamically-linked Shared Object) memory page is used by a process to access to kernel features, without using a system call. This memory page is enabled when the kernel is compiled with CONFIG_COMPAT_VDSO.

However, this memory page is always located at the same address. Moreover, it contains instructions like POP+RET, which are used to redirect the execution path of an exploit.

When the Linux kernel is compiled with CONFIG_COMPAT_VDSO, a local attacker can, therefore, use it to bypass ASLR, in order to ease the development of an attack.


This is useful in terms of design, for Virtual syscalls.


There never was a physical linux-vdso.so.1 binary in the filesystem, it's a virtual shared object. 

The instructions or "gadgets" found in the VDSO, will vary depending on the CPU arch and OS .

The virtual file name also changes depending on CPU architecture. For example , common virtual filenames of vDSO include vdso64.so, vdso32.so, vdsox32.so, and are typically linked in the kernel module filesystem.


# Ret2vDSO:

We can use some gadgets found in this memory region in order to construct a rop attack.


# Virtual syscalls:

