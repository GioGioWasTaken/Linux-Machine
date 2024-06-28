## Overview
The `CPU operating modes` dictate how the `CPU` accesses memory, handles instructions, and interacts with other system components.

### Real mode
- The initial operating mode of x86 CPUs, dating back to the original Intel 8086 processor. 
- It is characterized by:
	-  20-bit addressing, allowing access to 1 MB of memory.
	- No memory protection or multitasking.
	- Direct access to hardware and peripherals.
**Use Case**: BIOS initialization, DOS-based systems, and early boot stages of modern operating systems.
### Protected mode
Characterized by:
- 32-bit addressing, allowing access to 4 GB of memory (and up to 64 GB with PAE).
 - Memory protection, enabling isolation of processes to prevent them from interfering with each other. 
 - Supports multitasking and advanced features like virtual memory.
### Unreal mode


**Use Case:** Modern operating systems, applications that require memory protection and multitasking.