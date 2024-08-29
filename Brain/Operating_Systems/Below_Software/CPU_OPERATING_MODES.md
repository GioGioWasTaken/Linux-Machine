## Overview
The `CPU operating modes`, or `CPU execution mdoes` dictate how the `CPU` accesses memory, handles instructions, and interacts with other system components.

### Real mode
- The initial operating mode of x86 CPUs, dating back to the original Intel 8086 processor. 
- It is characterized by:
	-  20-bit addressing, allowing access to 1 MB of memory.
	- No memory protection or multitasking.
	- Direct access to hardware and peripherals.
	- It does not support virtual memory
Since old registers were 16 bits, the theoretical amount of memory that could be accessesed was smaller than the actual amount of memory that was available. To resolve this we used `segmentation` which allows more efficient use of memory. The formula for `segmentation` goes as following:

Physical address = 16 * segmentat_selector + offset

```
hex((0x2000 << 4) + 0x0010)
'0x20010' 
```
*NOTE*: shifting 4 bits to the left (<<) is akin to multipling by 16, since we are shifting in base 2.


**Use Case**: BIOS initialization, DOS-based systems, and early boot stages of modern operating systems. Some kernel code is written in `real` mode, before the kernel moves to protected mode.

### System Management Mode:
- The most privilged mode. Its memory is protected even from the OS. Its job is to do stuff almost exclusively on hardware. E.g. Power management. 

### Protected mode
*NOTE* : `virtual-8086` mode isn't actually a mode. It's an attribute that can be enabled from within protected mode. It allows running `Real Mode` inside `protected mode`, for backwards comptability with older programs.


Characterized by:
- 32-bit addressing, allowing access to 4 GB of memory (and up to 64 GB with PAE).
 - Memory protection, enabling isolation of processes to prevent them from interfering with each other. 
 - Supports multitasking and advanced features like virtual memory.

 Read more at:
[[Protected_Mode]]
### Unreal mode

**Use Case:** Modern operating systems, applications that require memory protection and multitasking.
