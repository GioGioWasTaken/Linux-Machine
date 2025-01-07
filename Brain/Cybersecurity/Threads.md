# Definition:
A thread is the smallest unit of execution within a process. It shares:
- The process's memory space.
- Global variables and resources of the process.

# Characteristics:
- Threads within the same process can communicate more efficiently than processes, as they share memory.
- Threads allow concurrent execution within a single process, making them lightweight compared to processes.
- Examples: A browser's tabs might run as threads within the same process (or as separate processes in modern browsers).

# Proccesses vs threads:

Threads are considered more lightweight than processes because they share resources within the same process and require less overhead to create, manage, and switch between. Here's a detailed breakdown:

## Shared Resources

Threads:
    Threads within a process share:
	The same memory space (heap, global variables).
	Open file descriptors.
	Network sockets and other system resources.
    This eliminates the need to duplicate these resources, reducing memory usage and setup time.
Processes:
    Each process has its own:
	Separate memory space.
	Copies of system resources (file descriptors, environment variables).
    Creating a new process involves duplicating and initializing these resources, which is more resource-intensive.

## Creation Cost

Threads:
Creating a thread typically involves:
    - Allocating a small amount of memory for the thread's stack and control block.
    - Registering the thread with the operating system.

This is relatively fast and lightweight.

Processes:

Creating a new process involves:
- Allocating and initializing a full memory space.
    * A full memory space will include some memory for the stack, the `.text` section, `.bss` and `.data` sections, and a kernel context stack for syscalls.
- Setting up a new process control block (PCB) with details like page tables and scheduling information.
Copying resources or setting up shared resources (e.g., fork semantics in Unix-like systems can use copy-on-write but still incurs more cost than thread creation).


## Context Switching

Threads:

Switching between threads within the same process is faster because:
- The memory space remains the same.
- Only the CPU registers, program counter, and stack pointer need to be updated.

Processes:

Switching between processes requires:
- Flushing and reloading memory mappings (virtual memory).
- Switching page tables and possibly invalidating caches.
- This involves more work for the CPU and operating system.
