# Primitives:

We have no direct way of writing to the stack, and in face of that, similarly to the `tiny` challenge I did previously, we can use stack variables to do our bidding.

# Constraints:

NX is enabled. 

# Approach :

The binary doesn't link against anything. It's not connected to libc. It has no gadgets. In face of this I had to do some research on less convention ROP methods, and I came address ret2vDSO.


it pops argc into eax, pops a char pointer (argv[0]) into edx, dereferences that pointer/stores its contents into edx, and then finally it calls edx.

We need a pointer to a string, so I will use ///////.....bin/sh, since it will still call /bin/sh.


Stack layout:
| 0x0|  is defined as the first env_var |
| 0x0|  : 0x0b  ->  will be popped into eax |
| 0x1| : 0x3 -> will be popped into edx |
| .....|  |
| 0x3| :  pop_ebx_esi_ebp |
| 0x1000  byte long padding (minus two pops) (it will be ///////.....bin/sh) |
| 0xFF8| : 0x500 (hope to hit one of the /bin/sh strings) |
| padding|  |
| padding|  |
| 0x1000| : pop_edx_ecx |
| 0x1004| : 0 |
| 0x1008| : 0 |
| 0x100B| : syscall_addr |


itt turns out that the built in command exec in bash lets you modify the value of argv when executing. E.g.:

```bash
exec -a BBBB ./tiny_hard
```
