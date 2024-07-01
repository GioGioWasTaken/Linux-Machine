### Kernel space

Since the kernel provides an interface to all over programs, it makes sense for it to be more priviliged. A kernel runs in a more priviliged part of memory that can interact with hardware, and is allowed to modify things other programs can't. The kernel essentially puts every program in a jail, and only lets it perform operations according to its interface (syscalls or any form of API to a kernel.).
