# Solution

- First of all there is a known bug with alloca. Look into that
- Perhaps also try to overflow int with a negative value.
# Approach:

- After some testing, we observe that whatever value i allocate, 22 more bytes  will be allocated so that esp is properly alligned.
- The stack must always be aligned, so we can't control the increment by the byte
- butttt we can control the increment by the stack alignment factor
- on this binary it happens to be 8 since it's a 32 bit binary
- so we have our exploit: move ESP upwards (deallocate data)
- and use our fgets to overwrite main's return address on the stack.
- 
-   look for this addr 0xf7d91a77
-  return address is stored at: 0xffffd6dc
-  the difference at the point where fgets executes:
-   ESP is 15 dwords below our target, let's go up by -(16*4)
-   we have to be careful to write the same value to the canary as it had before.

-  sad discovery: fgets does not take user input when it's given a negative integer
- solution: we just need the memcpy call to copy our "canary" value,to the location where main's return address is stored in the stack.


0x080487c1 <+350>:	mov    eax,ds:0x804a050
