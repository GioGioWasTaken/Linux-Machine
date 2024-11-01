# The primitive is GOD
- Rememeber your primitives. All of them.
-  If you have a primitive, don't get lost in the other details of the binary file.

# Delve deep into the mechanisms of the assembly
- Always look for the exact meaning of the assembly.
  * Example: ret doesn't "return the `EIP` address" it returns where it THINKS the `EIP` address is(ret = jmp [ESP]). Meaning, an `EBP` overwrite is an `EIP` overwrite. 
- "I could solve this if I had X" - check if you can make X with your current primitives.

# "I have no idea what this even does... How do I approach this"

- Worse thing you can do is freeze. Think of very very simple inputs, that produce likely unintended results. Slowly understand what's happening. Rely on discompiled code. Rely on LLMs, rely on everything. Your goal is to understand what the hell this awful piece of code does, and then break it.


# "This doesn't make any sense"

- Go slow. Check *everything*.
  * Sometimes, the decompiled code will have mistakes that make it unintelligible, and they sometimes won't be obvious. Go to the assembly.
      + For example, a for loop identified as a while loop.
      + sometimes, you renamed a variable the wrong way and you're misleading yourself
  * Make sure you trace everything to its root.


# Templates

## Pwntools template

```python
from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "[Enter Name]"
REMOTE = "nc [IP] [PORT]"
libc_name="[ENTER NAME]"

e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)
libc=e.libc # So long as i'm not running against the remote target, use the local libc


context.binary = e


ru  = lambda *x, **y: p.recvuntil(*x, **y)
rl  = lambda *x, **y: p.recvline(*x, **y)
rc  = lambda *x, **y: p.recv(*x, **y)
sla = lambda *x, **y: p.sendlineafter(*x, **y)
sa  = lambda *x, **y: p.sendafter(*x, **y)
sl  = lambda *x, **y: p.sendline(*x, **y)
sn  = lambda *x, **y: p.send(*x, **y)

def main():
    if(len(sys.argv) <2):
        print("Running locally")
        p = process(f"./{binary_name}")
    else:
        if(sys.argv[1] == "remote"):
            ip, port = REMOTE.replace("nc ", "").split(" ")
            port = int(port)
            p = remote(ip, port)
            libc = ELF(f"./{libc_name}")

            # or if using ssh:
            # s = ssh(user='',host='pwnable.kr',port=2222,password='guest') 
            # p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(f"./{binary_name}", gdbscript="b *", aslr=False)
        else:
            p = process(f"./{binary_name}")
main()



```
## GDB

in `.gdbinit` I have
`source run.gdb`, Which will be a file created in every binary exploitation project.

`run.gdb` will contain every other file i'd like sourced in my gdb sessions
