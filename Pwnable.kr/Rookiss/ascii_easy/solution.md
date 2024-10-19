

# Solve Process


My first thought was: "Oh! We know the address of libc! All we need is to call system with /bin/sh."

But wait... 0x5555e000 will always not be possible to input with printable ascii chars only. Maybe there are some functions within libc that are in our disposal? hopefully, system?


`gdb-peda$ print &system
$1 = (<text variable, no debug info> *) 0x3eed0 <system>`
 0x5555e000+0x3eed0= 0x5594CD0 fuck. It seems the author intentionally prevented us access to the system function

```bash
rop ascii_easy | grep "pop edi" | awk '{print $1}'  > pop_edi_addr.txt
```
first run this command, to see if we have some printable pop edi gadgets. 




