# VDSO

The `VDSO` (Virtual Dynamically-linked Shared Object) memory page is used by a process to access to kernel features, without using a system call. This memory page is enabled when the kernel is compiled with CONFIG_COMPAT_VDSO.

However, this memory page is always located at the same address. Moreover, it contains instructions like POP+RET, which are used to redirect the execution path of an exploit.

When the Linux kernel is compiled with CONFIG_COMPAT_VDSO, a local attacker can, therefore, use it to bypass ASLR, in order to ease the development of an attack.


This is useful in terms of design, for Virtual syscalls.


# Ret2vDSO:

We can use some gadgets found in this memory region in order to construct a rop attack.


# Virtual syscalls:

